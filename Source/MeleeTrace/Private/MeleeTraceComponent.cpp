// Copyright 2023, Robert Lewicki, All rights reserved.

#include "MeleeTraceComponent.h"

#include "Components/MeshComponent.h"
#include "Engine/HitResult.h"
#include "Engine/World.h"

#include "MeleeTraceSettings.h"
#include "MeleeTraceShape.h"
#include <functional>

#ifdef ENABLE_DRAW_DEBUG
#include "MeleeTraceDebug.h"

#define MIN_FRAME 0.02

static TAutoConsoleVariable<bool> CVarMeleeTraceShouldDrawDebug(TEXT("MeleeTrace.ShouldDrawDebug"),
	false,
	TEXT("when set to true or 1 will draw debug drawings of meleetraces. Set to false or 0 to disable."));
static TAutoConsoleVariable<float> CVarMeleeTraceDrawDebugDuration(TEXT("MeleeTrace.DrawDebugDuration"),
	1.f,
	TEXT("Defines how long debug drawings will be visible in the viewport."));
// ※ Delcared in MeleeTraceEditorSettings.h
#endif


UMeleeTraceComponent::UMeleeTraceComponent() // ※ AActorComponent Doesnt Need To Call Super (Automatically Called)
{
	PrimaryComponentTick.bCanEverTick = true;

	//TraceChannel = GetDefault<UMeleeTraceSettings>()->MeleeTraceCollisionChannel;
}

void UMeleeTraceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TRACE_CPUPROFILER_EVENT_SCOPE(UMeleeTraceComponent::TickComponent);

#ifdef ENABLE_DRAW_DEBUG
	const bool bShouldDrawDebug = CVarMeleeTraceShouldDrawDebug.GetValueOnGameThread();
	const float DrawDebugDuration = CVarMeleeTraceDrawDebugDuration.GetValueOnGameThread();
#endif

	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(GetOwner()); // ※ No Need To My Project. But Keep Alive

	TArray<FHitResult> HitResults;
	for (FActiveMeleeTraceInfo& ActiveMeleeTrace : ActiveMeleeTraces)
	{
		for(FMeleeTraceSocketShapeInfo& SocketShapeInfo : ActiveMeleeTrace.SocketShapeInfos)
		{ 
			const FQuat SampleRotation = SocketShapeInfo.SourceMeshComponent->
				GetSocketRotation(SocketShapeInfo.SocketName).Quaternion();

			FVector PrevLocation = SocketShapeInfo.PreviousFrameSampleLocation;
			SocketShapeInfo.PreviousFrameSampleLocation = SocketShapeInfo.SourceMeshComponent->GetSocketLocation(SocketShapeInfo.SocketName);
			if (PrevLocation.Equals(SocketShapeInfo.PreviousFrameSampleLocation))
			{
				PrevLocation += FVector::UpVector * UE_KINDA_SMALL_NUMBER; 
			}
			const FVector& CurrLocation = SocketShapeInfo.PreviousFrameSampleLocation;


			FQuat PrevRotation = SocketShapeInfo.PrevRotation;
			SocketShapeInfo.PrevRotation = (SocketShapeInfo.RotationOffset * SampleRotation).GetNormalized();
			const FQuat& CurrRotation = SocketShapeInfo.PrevRotation;


			double CurrentFrameTime = GetWorld()->TimeSeconds;
			double PrevFrameTime = SocketShapeInfo.PreviousFrameTime;
			SocketShapeInfo.PreviousFrameTime = CurrentFrameTime;

			auto AddressTwoPoint = [&](const FVector& Start, const FVector& End, const FQuat& Rot, double StartTime, double EndTime) -> void
				{
					const bool bHit = GetWorld()->SweepMultiByChannel(HitResults, Start, End,
						Rot, TraceChannel, SocketShapeInfo.TraceCollisionShape, CollisionQueryParams);
#ifdef ENABLE_DRAW_DEBUG
					if (bShouldDrawDebug)
					{
						MeleeTrace::DrawDebugTrace(this, SocketShapeInfo.TraceCollisionShape,
							FTransform(Rot, Start),
							FTransform(Rot, End), EDrawDebugTrace::Type::ForDuration,
							bHit, HitResults, DrawDebugDuration);
					}
#endif

					if (!bHit) return;


					for (const FHitResult& HitResult : HitResults)
					{
						if (!ActiveMeleeTrace.HitActors.Contains(HitResult.GetActor()))
						{
							ActiveMeleeTrace.HitActors.Add(HitResult.GetActor());

							FMeleeHitInfo HitInfo;
							HitInfo.ThisComponent = this;
							HitInfo.HitResult = HitResult;
							HitInfo.HitBoneName = HitResult.BoneName;
							HitInfo.TraceHandle = ActiveMeleeTrace.TraceHandle;
							HitInfo.Ability = ActiveMeleeTrace.Ability;
							HitInfo.Protocol = SocketShapeInfo.Protocol;
							HitInfo.HitTime = StartTime + (EndTime - StartTime) * HitResult.Time;

							OnTraceHit.Broadcast(MoveTemp(HitInfo));
						}
					}
				};	

			double DiffTime = CurrentFrameTime - PrevFrameTime;
			if (DiffTime <= MIN_FRAME)
			{
				AddressTwoPoint(PrevLocation, CurrLocation, PrevRotation, PrevFrameTime, CurrentFrameTime);
			}
			else
			{
				int SegmentCount = FMath::CeilToInt((DiffTime) / MIN_FRAME);
				double Interval = DiffTime / static_cast<double>(SegmentCount);

				FVector AddVec = (CurrLocation - PrevLocation) / static_cast<double>(SegmentCount);
				FVector StartPos = PrevLocation;
				FVector EndPos = PrevLocation + AddVec;

				double StartTime = PrevFrameTime;
				double EndTime = PrevFrameTime + Interval;
				
				double TValue = 0;
				double TInterval = 1.0 / static_cast<double>(SegmentCount);

				AddressTwoPoint(StartPos, EndPos, PrevRotation, StartTime, EndTime);
				while(--SegmentCount > 0)
				{
					StartPos += AddVec;
					EndPos += AddVec;

					StartTime += Interval;
					EndTime += Interval;
					TValue += TInterval;

					FQuat Rot = FQuat::Slerp(PrevRotation, CurrRotation, TValue);

					AddressTwoPoint(StartPos, EndPos, Rot, StartTime, EndTime);
				}
			}
		}
	}
}

void UMeleeTraceComponent::EndPlay(const EEndPlayReason::Type EndPlayReasion)
{
	Super::EndPlay(EndPlayReasion);

	for (auto& Pair : CachedMeleeTaces)
	{
		if (Pair.Value.ContextHash != MeleeTrace::INVALID_HASH)
		{
			MeleeTrace::ReleaseTraceHash(Pair.Value.ContextHash);
			
		}
	}
}

void UMeleeTraceComponent::StartTraceWithContext(const FMeleeTraceInfo& MeleeTraceInfo, UObject* Context)
{
	if (!ensureMsgf(Context, TEXT("Invalid Context object passed to [%s]."), StringCast<TCHAR>(__FUNCTION__).Get()))
	{	// ※ == assert
		return;
	}

	const uint32 ContextHash = GetContextHash(Context);

	uint32 TraceHash = MeleeTrace::GetTraceHash(ContextHash);
	if (TraceHash == MeleeTrace::INVALID_HASH)
	{
		TraceHash = MeleeTrace::CalculateNewTraceHashWithContext(ContextHash);
	}
	InternalStartTrace(MeleeTraceInfo, TraceHash, ContextHash);
}

void UMeleeTraceComponent::EndTraceWithContext(const UObject* Context)
{
#if 0 // ※ Obsolate. even if Context Destroyed, Context != nullptr. And Object Destroyed And This Func call Could Happen
	if (!ensureMsgf(Context, TEXT("Invalid Context object passed to [%s]."), StringCast<TCHAR>(__FUNCTION__).Get()))
	{
		return;
	}
#endif
	if (IsValid(Context) == false) return;

	const uint32 ContextHash = GetContextHash(Context);
	const uint32 TraceHash = MeleeTrace::GetTraceHash(ContextHash);
	InternalEndTrace(TraceHash);

	//MeleeTrace::ReleaseTraceHash(ContextHash); // Obsolate. Reuse It. so No More Need it here
}

FMeleeTraceInstanceHandle UMeleeTraceComponent::StartTrace(const FMeleeTraceInfo& MeleeTraceInfo)
{
	FMeleeTraceInstanceHandle InstanceHandle;
	InstanceHandle.TraceHash = MeleeTrace::CalculateNewTraceHash();
	InternalStartTrace(MeleeTraceInfo, InstanceHandle.TraceHash, MeleeTrace::INVALID_HASH);
	return InstanceHandle;
}

void UMeleeTraceComponent::EndTrace(FMeleeTraceInstanceHandle MeleeTraceInstanceHandle)
{
	InternalEndTrace(MeleeTraceInstanceHandle.TraceHash);
}

void UMeleeTraceComponent::ForceEndAllTraces()
{
	for (const FActiveMeleeTraceInfo& ActiveMeleeTrace : ActiveMeleeTraces)
	{
		OnTraceEnd.Broadcast(this, ActiveMeleeTrace.HitActors.Num(), ActiveMeleeTrace.TraceHandle);
	}
	ActiveMeleeTraces.Reset();
}



TArray<AActor*> UMeleeTraceComponent::GetActorsHitByTraceWithContext(const UObject* Context) const
{
	const uint32 ContextHash = GetContextHash(Context);
	const uint32 TraceHash = MeleeTrace::GetTraceHash(ContextHash);
	TArray<AActor*> HitActors = InternalGetActorsHitByTrace(TraceHash);
	return MoveTemp(HitActors);
}

TArray<AActor*> UMeleeTraceComponent::GetActorsHitByTrace(const FMeleeTraceInstanceHandle& Handle) const
{
	TArray<AActor*> HitActors = InternalGetActorsHitByTrace(Handle.TraceHash);
	return MoveTemp(HitActors);
}

void UMeleeTraceComponent::InvalidateMeleeTraceHandle(FMeleeTraceInstanceHandle& Handle)
{
	Handle.TraceHash = MeleeTrace::INVALID_HASH;
}

bool UMeleeTraceComponent::IsMeleeTraceHandleValid(const FMeleeTraceInstanceHandle& Handle)
{
	return Handle.TraceHash != MeleeTrace::INVALID_HASH;
}

//void UMeleeTraceComponent::GetTraceSamples(const UMeshComponent* MeshComponent, int32 TraceDensity, 
//	const FName& StartSocketName, const FName& EndSocketName, TArray<FVector>& OutSamples)
//{
//	OutSamples.Reset(TraceDensity + 1);
//	const FVector StartSampleLocation = MeshComponent->GetSocketLocation(StartSocketName);
//	const FVector EndSampleLocation = MeshComponent->GetSocketLocation(EndSocketName);
//	
//	float fDensity = static_cast<float>(TraceDensity);
//	for (int32 Index = 0; Index <= TraceDensity; Index++)
//	{
//		const float Alpha = static_cast<float>(Index) / fDensity;
//		const FVector Sample = FMath::Lerp(StartSampleLocation, EndSampleLocation, Alpha);
//		OutSamples.Add(Sample);
//	}
//}

void UMeleeTraceComponent::InternalStartTrace(const FMeleeTraceInfo& MeleeTraceInfo, uint32 TraceHash, uint32 ContextHash)
{
	AActor* Owner = GetOwner();
	check(Owner);


	if (auto* Found = CachedMeleeTaces.Find(TraceHash))
	{
		for (FMeleeTraceSocketShapeInfo& SocketShape : Found->SocketShapeInfos)
		{
			if (!SocketShape.SourceMeshComponent.IsValid()) continue;

			SocketShape.PreviousFrameSampleLocation = SocketShape.SourceMeshComponent->GetSocketLocation(SocketShape.SocketName);

			const FQuat SampleRotation = SocketShape.SourceMeshComponent->GetSocketRotation(SocketShape.SocketName).Quaternion();
			SocketShape.PrevRotation = (SocketShape.RotationOffset * SampleRotation).GetNormalized();

			SocketShape.PreviousFrameTime = GetWorld()->TimeSeconds;
		}
		ActiveMeleeTraces.Add(*Found);

		return;
	}


	TArray<UActorComponent*> MeshComponents;
	TArray<AActor*> ActorsToCheck = { Owner };
	TArray<AActor*> AttachedActors;

	Owner->GetAttachedActors(AttachedActors);
	ActorsToCheck.Append(AttachedActors);

	for (const AActor* Actor : ActorsToCheck)
	{
		TArray<UActorComponent*> ActorMeshComponents;
		Actor->GetComponents(UMeshComponent::StaticClass(), ActorMeshComponents);
		MeshComponents.Append(ActorMeshComponents);
	}

	
	FActiveMeleeTraceInfo& NewMeleeTraceInfo = ActiveMeleeTraces.AddDefaulted_GetRef(); // AddDefaulted_GetRef : Add and return Ref
	NewMeleeTraceInfo.TraceHandle = FMeleeTraceInstanceHandle(TraceHash);
	NewMeleeTraceInfo.ContextHash = ContextHash;
	NewMeleeTraceInfo.Ability = MeleeTraceInfo.Ability;

	for (const FMeleeTraceSmallInfo& MeleeInfo : MeleeTraceInfo.MeleeTraceInfos)
	{
		bool foundMesh = false;

		for (UActorComponent* MeshComponent : MeshComponents)
		{
			UMeshComponent* TypedMeshComponent = Cast<UMeshComponent>(MeshComponent);
			check(TypedMeshComponent);
			if (TypedMeshComponent->DoesSocketExist(MeleeInfo.SocketName))
			{
				FMeleeTraceSocketShapeInfo newSocketShapeInfo;
				


				newSocketShapeInfo.SocketName = MeleeInfo.SocketName;
				newSocketShapeInfo.Protocol = MeleeInfo.Protocol;

				if (ensureMsgf(MeleeInfo.TraceShape->IsValidLowLevelFast(),
					TEXT("[%s] : Invalid trace shape definition"), *GetNameSafe(GetOwner())))
				{
					newSocketShapeInfo.RotationOffset = MeleeInfo.TraceShape->GetRotationOffset();
					newSocketShapeInfo.TraceCollisionShape = MeleeInfo.TraceShape->CreateCollisionShape();
				}
				else
				{
					newSocketShapeInfo.RotationOffset = FQuat::Identity;
					newSocketShapeInfo.TraceCollisionShape = FCollisionShape();
				}
				newSocketShapeInfo.SourceMeshComponent = TypedMeshComponent;

				newSocketShapeInfo.PreviousFrameSampleLocation = newSocketShapeInfo.SourceMeshComponent
					->GetSocketLocation(newSocketShapeInfo.SocketName);

				const FQuat SampleRotation = newSocketShapeInfo.SourceMeshComponent->GetSocketRotation(newSocketShapeInfo.SocketName).Quaternion();
				newSocketShapeInfo.PrevRotation = (newSocketShapeInfo.RotationOffset * SampleRotation).GetNormalized();

				newSocketShapeInfo.PreviousFrameTime = GetWorld()->TimeSeconds;

				
				NewMeleeTraceInfo.SocketShapeInfos.Add(newSocketShapeInfo);

				foundMesh = true;
				break;
			}
		}


		if (foundMesh == false)
		{
			ensureAlwaysMsgf(false, TEXT("None of the USkeletalMeshComponents contain socket with name : [%s]"),
				*MeleeInfo.SocketName.ToString());
		}
	}
	CachedMeleeTaces.Add(TraceHash, NewMeleeTraceInfo);
	OnTraceStart.Broadcast(this, NewMeleeTraceInfo.TraceHandle);
}

void UMeleeTraceComponent::InternalEndTrace(uint32 TraceHash)
{
	if (!ensureAlwaysMsgf(TraceHash != MeleeTrace::INVALID_HASH, TEXT("Invalid TraceHash used to end trace")))
	{
		return;
	}

	const int32 FoundIndex = ActiveMeleeTraces.IndexOfByPredicate(
		[TraceHash](const FActiveMeleeTraceInfo& ActiveMeleeTraceInfo)
		{
			return TraceHash == ActiveMeleeTraceInfo.TraceHandle.TraceHash;
		}
	);

	if (ensureAlwaysMsgf(FoundIndex != INDEX_NONE,
		TEXT("Attempting to end trace with hash : [%u] but no trace with hash exists"), TraceHash))
	{
		OnTraceEnd.Broadcast(this, ActiveMeleeTraces[FoundIndex].HitActors.Num(),
			ActiveMeleeTraces[FoundIndex].TraceHandle);
		ActiveMeleeTraces.RemoveAtSwap(FoundIndex);
	}
}

TArray<AActor*> UMeleeTraceComponent::InternalGetActorsHitByTrace(uint32 TraceHash) const
{
	const int32 TraceIndex = ActiveMeleeTraces.IndexOfByPredicate(
		[TraceHash](const FActiveMeleeTraceInfo& TraceInfo)
		{
			return TraceInfo.TraceHandle.TraceHash == TraceHash;
		}
	);

	if (TraceIndex == INDEX_NONE) return {};

	TArray<AActor*> OutHitActors;
	for (TWeakObjectPtr<AActor> HitActor : ActiveMeleeTraces[TraceIndex].HitActors)
	{
		if (HitActor.IsValid())
		{
			OutHitActors.Add(HitActor.Get());
		}
	}
	return MoveTemp(OutHitActors);
}

uint32 UMeleeTraceComponent::GetContextHash(const UObject* Context) const
{
	return MeleeTrace::CombineHashes(Context->GetUniqueID(), GetUniqueID());
}















































































/*
#if 0
#ifdef ENABLE_DRAW_DEBUG
#include "MeleeTraceDebug.h"

static TAutoConsoleVariable<bool> CVarMeleeTraceShouldDrawDebug(TEXT("MeleeTrace.ShouldDrawDebug"),
	false,
	TEXT("When set to true or 1 will draw debug drawings of melee traces. Set to false or 0 to disable."));
static TAutoConsoleVariable<float> CVarMeleeTraceDrawDebugDuration(TEXT("MeleeTrace.DrawDebugDuration"),
	1.0f,
	TEXT("Defines how long debug drawings will be visible in the viewport."));
#endif

UMeleeTraceComponent::UMeleeTraceComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	TraceChannel = GetDefault<UMeleeTraceSettings>()->MeleeTraceCollisionChannel;
}

void UMeleeTraceComponent::TickComponent(float DeltaTime,
	ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TRACE_CPUPROFILER_EVENT_SCOPE(UMeleeTraceComponent::TickComponent);

#ifdef ENABLE_DRAW_DEBUG
	const bool bShouldDrawDebug = CVarMeleeTraceShouldDrawDebug.GetValueOnGameThread();
	const float DrawDebugDuration = CVarMeleeTraceDrawDebugDuration.GetValueOnGameThread();
#endif
	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(GetOwner());
	TArray<FHitResult> HitResults;
	for (FActiveMeleeTraceInfo& ActiveMeleeTrace : ActiveMeleeTraces)
	{
		TArray<FVector> NewSamples;
		GetTraceSamples(ActiveMeleeTrace.SourceMeshComponent.Get(),
			ActiveMeleeTrace.TraceDensity,
			ActiveMeleeTrace.StartSocketName,
			ActiveMeleeTrace.EndSocketName,
			NewSamples);
		const FQuat SamplesRotation = ActiveMeleeTrace.SourceMeshComponent->GetSocketRotation(
			ActiveMeleeTrace.StartSocketName).Quaternion();
		const FQuat OffsetRotation = ActiveMeleeTrace.RotationOffset * SamplesRotation;
		for (int32 Index = 0; Index < NewSamples.Num(); Index++)
		{
			HitResults.Reset();
			FVector PreviousSampleLocation = ActiveMeleeTrace.PreviousFrameSampleLocations[Index];
			if (PreviousSampleLocation.Equals(NewSamples[Index]))
			{
				PreviousSampleLocation += FVector::UpVector * UE_KINDA_SMALL_NUMBER;
			}
			const bool bHit = GetWorld()->SweepMultiByChannel(HitResults,
				PreviousSampleLocation,
				NewSamples[Index],
				OffsetRotation,
				TraceChannel,
				ActiveMeleeTrace.TraceCollisionShape,
				CollisionQueryParams);
#ifdef ENABLE_DRAW_DEBUG
			if (bShouldDrawDebug)
			{
				MeleeTrace::DrawDebugTrace(this,
					ActiveMeleeTrace.TraceCollisionShape,
					FTransform(OffsetRotation, ActiveMeleeTrace.PreviousFrameSampleLocations[Index]),
					FTransform(OffsetRotation, NewSamples[Index]),
					EDrawDebugTrace::Type::ForDuration,
					bHit,
					HitResults,
					DrawDebugDuration);
			}
#endif
			if (!bHit)
			{
				continue;
			}

			for (const FHitResult& HitResult : HitResults)
			{
				if (!ActiveMeleeTrace.HitActors.Contains(HitResult.GetActor()))
				{
					ActiveMeleeTrace.HitActors.Add(HitResult.GetActor());
					OnTraceHit.Broadcast(this,
						HitResult.GetActor(),
						HitResult.ImpactPoint,
						HitResult.ImpactNormal,
						HitResult.BoneName,
						ActiveMeleeTrace.TraceHandle);
				}
			}
		}

		ActiveMeleeTrace.PreviousFrameSampleLocations = MoveTemp(NewSamples);
	}
}

void UMeleeTraceComponent::StartTraceWithContext(const FMeleeTraceInfo& MeleeTraceInfo, const UObject* Context)
{
	if (!ensureMsgf(Context, TEXT("Invalid Context object passed to %s"), StringCast<TCHAR>(__FUNCTION__).Get()))
	{
		return;
	}

	const uint32 ContextHash = GetContextHash(Context);
	const uint32 TraceHash = MeleeTrace::CalculateNewTraceHashWithContext(ContextHash);
	InternalStartTrace(MeleeTraceInfo, TraceHash);
}

void UMeleeTraceComponent::EndTraceWithContext(const UObject* Context)
{
	if (!ensureMsgf(Context, TEXT("Invalid Context object passed to %s"), StringCast<TCHAR>(__FUNCTION__).Get()))
	{
		return;
	}

	const uint32 ContextHash = GetContextHash(Context);
	const uint32 TraceHash = MeleeTrace::GetTraceHash(ContextHash);
	InternalEndTrace(TraceHash);
	MeleeTrace::ReleaseTraceHash(ContextHash);
}

FMeleeTraceInstanceHandle UMeleeTraceComponent::StartTrace(const FMeleeTraceInfo& MeleeTraceInfo)
{
	FMeleeTraceInstanceHandle InstanceHandle;
	InstanceHandle.TraceHash = MeleeTrace::CalculateNewTraceHash();
	InternalStartTrace(MeleeTraceInfo, InstanceHandle.TraceHash);
	return InstanceHandle;
}

void UMeleeTraceComponent::EndTrace(FMeleeTraceInstanceHandle MeleeTraceInstanceHandle)
{
	InternalEndTrace(MeleeTraceInstanceHandle.TraceHash);
}

void UMeleeTraceComponent::ForceEndAllTraces()
{
	for (const FActiveMeleeTraceInfo& ActiveMeleeTrace : ActiveMeleeTraces)
	{
		OnTraceEnd.Broadcast(this, ActiveMeleeTrace.HitActors.Num(), ActiveMeleeTrace.TraceHandle);
	}

	ActiveMeleeTraces.Reset();
}

bool UMeleeTraceComponent::IsAnyTraceActive() const
{
	return ActiveMeleeTraces.Num() > 0;
}

void UMeleeTraceComponent::SetTraceChannel(ECollisionChannel NewTraceChannel)
{
	TraceChannel = NewTraceChannel;
}

ECollisionChannel UMeleeTraceComponent::GetTraceChannel() const
{
	return TraceChannel;
}

TArray<AActor*> UMeleeTraceComponent::GetActorsHitByTraceWithContext(const UObject* Context) const
{
	const uint32 ContextHash = GetContextHash(Context);
	const uint32 TraceHash = MeleeTrace::GetTraceHash(ContextHash);
	TArray<AActor*> HitActors = InternalGetActorsHitByTrace(TraceHash);
	return MoveTemp(HitActors);
}

TArray<AActor*> UMeleeTraceComponent::GetActorsHitByTrace(const FMeleeTraceInstanceHandle& Handle) const
{
	TArray<AActor*> HitActors = InternalGetActorsHitByTrace(Handle.TraceHash);
	return MoveTemp(HitActors);
}

void UMeleeTraceComponent::InvalidateMeleeTraceHandle(FMeleeTraceInstanceHandle& Handle)
{
	Handle.TraceHash = MeleeTrace::INVALID_HASH;
}

bool UMeleeTraceComponent::IsMeleeTraceHandleValid(const FMeleeTraceInstanceHandle& Handle)
{
	return Handle.TraceHash != MeleeTrace::INVALID_HASH;
}

void UMeleeTraceComponent::GetTraceSamples(const UMeshComponent* MeshComponent,
	int32 TraceDensity,
	const FName& StartSocketName,
	const FName& EndSocketName,
	TArray<FVector>& OutSamples)
{
	OutSamples.Reset(TraceDensity + 1);
	const FVector StartSampleLocation = MeshComponent->GetSocketLocation(StartSocketName);
	const FVector EndSampleLocation = MeshComponent->GetSocketLocation(EndSocketName);
	for (int32 Index = 0; Index <= TraceDensity; Index++)
	{
		const float Alpha = static_cast<float>(Index) / static_cast<float>(TraceDensity);
		const FVector Sample = FMath::Lerp(StartSampleLocation, EndSampleLocation, Alpha);
		OutSamples.Add(Sample);
	}
}

void UMeleeTraceComponent::InternalStartTrace(const FMeleeTraceInfo& MeleeTraceInfo, uint32 TraceHash)
{
	AActor* Owner = GetOwner();
	check(Owner);

	TArray<UActorComponent*> MeshComponents;
	TArray<AActor*> ActorsToCheck = { Owner };
	TArray<AActor*> AttachedActors;

	Owner->GetAttachedActors(AttachedActors);
	ActorsToCheck.Append(AttachedActors);

	for (const AActor* Actor : ActorsToCheck)
	{
		TArray<UActorComponent*> ActorMeshComponents;
		Actor->GetComponents(UMeshComponent::StaticClass(), ActorMeshComponents);
		MeshComponents.Append(ActorMeshComponents);
	}

	for (UActorComponent* MeshComponent : MeshComponents)
	{
		UMeshComponent* TypedMeshComponent = Cast<UMeshComponent>(MeshComponent);
		check(TypedMeshComponent);
		if (TypedMeshComponent->DoesSocketExist(MeleeTraceInfo.StartSocketName)
			&& TypedMeshComponent->DoesSocketExist(MeleeTraceInfo.EndSocketName))
		{
			FActiveMeleeTraceInfo& NewMeleeTraceInfo = ActiveMeleeTraces.AddDefaulted_GetRef();
			NewMeleeTraceInfo.TraceHandle = FMeleeTraceInstanceHandle(TraceHash);
			NewMeleeTraceInfo.TraceDensity = MeleeTraceInfo.TraceDensity;
			NewMeleeTraceInfo.StartSocketName = MeleeTraceInfo.StartSocketName;
			NewMeleeTraceInfo.EndSocketName = MeleeTraceInfo.EndSocketName;
			if (ensureMsgf(MeleeTraceInfo.TraceShape->IsValidLowLevelFast(),
				TEXT("%s: Invalid trace shape definition"),
				*GetNameSafe(GetOwner())))
			{
				NewMeleeTraceInfo.RotationOffset = MeleeTraceInfo.TraceShape->GetRotationOffset();
				NewMeleeTraceInfo.TraceCollisionShape = MeleeTraceInfo.TraceShape->CreateCollisionShape();
			}
			else
			{
				// This is a fallback in case of incorrect user settings
				NewMeleeTraceInfo.RotationOffset = FQuat::Identity;
				NewMeleeTraceInfo.TraceCollisionShape = FCollisionShape();
			}
			NewMeleeTraceInfo.SourceMeshComponent = TypedMeshComponent;
			GetTraceSamples(TypedMeshComponent,
				MeleeTraceInfo.TraceDensity,
				MeleeTraceInfo.StartSocketName,
				MeleeTraceInfo.EndSocketName,
				NewMeleeTraceInfo.PreviousFrameSampleLocations);
			OnTraceStart.Broadcast(this, NewMeleeTraceInfo.TraceHandle);
			return;
		}
	}

	ensureAlwaysMsgf(false,
		TEXT("None of the USkeletalMeshComponents contain sockets with names: %s and %s"),
		*MeleeTraceInfo.StartSocketName.ToString(),
		*MeleeTraceInfo.EndSocketName.ToString());
}

void UMeleeTraceComponent::InternalEndTrace(uint32 TraceHash)
{
	if (!ensureMsgf(TraceHash != MeleeTrace::INVALID_HASH, TEXT("Invalid TraceHash used to end trace")))
	{
		return;
	}

	const int32 FoundIndex = ActiveMeleeTraces.IndexOfByPredicate(
		[TraceHash](const FActiveMeleeTraceInfo& ActiveMeleeTraceInfo)
		{
			return TraceHash == ActiveMeleeTraceInfo.TraceHandle.TraceHash;
		});

	if (ensureAlwaysMsgf(FoundIndex != INDEX_NONE,
		TEXT("Attemping to end trace with hash: %u but no trace with hash exist"),
		TraceHash))
	{
		OnTraceEnd.Broadcast(
			this,
			ActiveMeleeTraces[FoundIndex].HitActors.Num(),
			ActiveMeleeTraces[FoundIndex].TraceHandle);
		ActiveMeleeTraces.RemoveAtSwap(FoundIndex);
	}
}

TArray<AActor*> UMeleeTraceComponent::InternalGetActorsHitByTrace(uint32 TraceHash) const
{
	const int32 TraceIndex = ActiveMeleeTraces.IndexOfByPredicate([TraceHash](const FActiveMeleeTraceInfo& TraceInfo)
	{
		return TraceInfo.TraceHandle.TraceHash == TraceHash;
	});

	if (TraceIndex == INDEX_NONE)
	{
		return {};
	}

	TArray<AActor*> OutHitActors;
	for (TWeakObjectPtr<AActor> HitActor : ActiveMeleeTraces[TraceIndex].HitActors)
	{
		if (HitActor.IsValid())
		{
			OutHitActors.Add(HitActor.Get());
		}
	}

	return MoveTemp(OutHitActors);
}

uint32 UMeleeTraceComponent::GetContextHash(const UObject* Context) const
{
	return MeleeTrace::CombineHashes(Context->GetUniqueID(), GetUniqueID());
}
#endif
*/