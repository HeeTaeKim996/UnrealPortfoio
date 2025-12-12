// Copyright 2023, Robert Lewicki, All rights reserved.

#include "AnimNotifyState_MeleeTrace.h"

#include "Animation/AnimSequenceBase.h"
#include "Components/SkeletalMeshComponent.h"

#include "MeleeTraceCommon.h"
#include "MeleeTraceComponent.h"
#include "MeleeTraceDebug.h"
#include "MeleeTraceShape.h"

#if UE_VERSION_OLDER_THAN(5, 0, 0)
void UAnimNotifyState_MeleeTrace::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float TotalDuration)
#else
void UAnimNotifyState_MeleeTrace::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float TotalDuration, const FAnimNotifyEventReference& EventReference)
#endif
{
#if UE_VERSION_OLDER_THAN(5, 0, 0)
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
#else
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
#endif
	if (const AActor* OwnerActor = MeshComp->GetOwner())
	{
		if (UMeleeTraceComponent* MeleeTraceComponent = OwnerActor->FindComponentByClass<UMeleeTraceComponent>())
		{
			for (FMeleeTraceSmallInfo& SmallInfo : MeleeTraceInfo.MeleeTraceInfos)
			{
				if (!ensure(SmallInfo.TraceShape->IsValidLowLevelFast()))
				{
					UE_LOG(LogMeleeTrace, Error,
						TEXT("Invalid trace shape defined in a Meleetrace anim notify for animation [%s]."),
						*Animation->GetName());
				}
			}
			
			MeleeTraceComponent->StartTraceWithContext(MeleeTraceInfo, this);
		}
#if WITH_EDITOR // ※ Only called in editor. not in game play
		else if (bShouldDrawDebugInEditor)
		{
			PreviousFrameSamples.Reset();
			PreviousFrameSamples.Reserve(MeleeTraceInfo.MeleeTraceInfos.Num());
			DebugMeshComponents.Reset();
			DebugMeshComponents.Reserve(MeleeTraceInfo.MeleeTraceInfos.Num());

			for (FMeleeTraceSmallInfo& SmallInfo : MeleeTraceInfo.MeleeTraceInfos)
			{
				bool bFoundMesh = false;
				if (MeshComp->DoesSocketExist(SmallInfo.SocketName))
				{
					DebugMeshComponents.Add(MeshComp);
					bFoundMesh = true;
				}
				else
				{
					TArray<USceneComponent*> ChildrenComponents;
					MeshComp->GetChildrenComponents(true, ChildrenComponents);

					for (USceneComponent* ChildComponent : ChildrenComponents)
					{
						if (UMeshComponent* typedMeshComponent = Cast<UMeshComponent>(ChildComponent))
						{
							if (typedMeshComponent->DoesSocketExist(SmallInfo.SocketName))
							{
								DebugMeshComponents.Add(typedMeshComponent);
								bFoundMesh = true;
								break;
							}
						}
					}
				}

				if (bFoundMesh == false) return;

				PreviousFrameSamples.Add(DebugMeshComponents.Last()->GetSocketLocation(SmallInfo.SocketName));
			}	
		}
#endif
	}
}


#if UE_VERSION_OLDER_THAN(5, 0, 0)
void UAnimNotifyState_MeleeTrace::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
#else
void UAnimNotifyState_MeleeTrace::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
#endif
{
#if UE_VERSION_OLDER_THAN(5, 0, 0)
	Super::NotifyEnd(MeshComp, Animation);
#else
	Super::NotifyEnd(MeshComp, Animation, EventReference);
#endif

	if (const AActor* OwnerActor = MeshComp->GetOwner())
	{
		if (UMeleeTraceComponent* MeleeTraceComponent = OwnerActor->FindComponentByClass<UMeleeTraceComponent>())
		{
			MeleeTraceComponent->EndTraceWithContext(this);
		}
	}
#if WITH_EDITOR
	DebugMeshComponents.Reset();
#endif
}



void UAnimNotifyState_MeleeTrace::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

#if WITH_EDITOR
	if (DebugMeshComponents.Num() == MeleeTraceInfo.MeleeTraceInfos.Num()  && bShouldDrawDebugInEditor)
	{
		const UWorld* World = MeshComp->GetWorld();
		if (World == nullptr) return;


		for (int Index = 0; Index < DebugMeshComponents.Num(); Index++)
		{
			if (DebugMeshComponents[Index].IsValid() == false) continue;

			FCollisionShape CollisionShape;
			if (MeleeTraceInfo.MeleeTraceInfos[Index].TraceShape)
			{
				CollisionShape = MeleeTraceInfo.MeleeTraceInfos[Index].TraceShape->CreateCollisionShape();
			}

			FName SocketName = MeleeTraceInfo.MeleeTraceInfos[Index].SocketName;
			const FVector CurrentFrameSample = DebugMeshComponents[Index]->GetSocketLocation(SocketName);
			const FQuat Rotation = DebugMeshComponents[Index]
				->GetSocketQuaternion(SocketName);

			//UMeleeTraceComponent::GetTraceSamples(DebugMeshComponent.Get(),
				//MeleeTraceInfo.TraceDensity, MeleeTraceInfo.StartSocketName, MeleeTraceInfo.EndSocketName, Samples);

			if (PreviousFrameSamples[Index].Equals(CurrentFrameSample))
			{
				PreviousFrameSamples[Index] += FVector::UpVector * UE_KINDA_SMALL_NUMBER;
			}

			MeleeTrace::DrawDebugTrace(World, CollisionShape, FTransform(Rotation, PreviousFrameSamples[Index]),
				FTransform(Rotation, CurrentFrameSample), EDrawDebugTrace::ForDuration, false, {},
				DebugDrawDuration);


			PreviousFrameSamples[Index] = CurrentFrameSample;
		}
	}
#endif
}













































































/*
#if 0
#if UE_VERSION_OLDER_THAN(5, 0, 0)
void UAnimNotifyState_MeleeTrace::NotifyBegin(
	USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
#else
void UAnimNotifyState_MeleeTrace::NotifyBegin(USkeletalMeshComponent* MeshComp,
	UAnimSequenceBase* Animation,
	float TotalDuration,
	const FAnimNotifyEventReference& EventReference)
#endif
{
#if UE_VERSION_OLDER_THAN(5, 0, 0)
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
#else
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
#endif

	if (const AActor* OwnerActor = MeshComp->GetOwner())
	{
		if (UMeleeTraceComponent* MeleeTraceComponent = OwnerActor->FindComponentByClass<UMeleeTraceComponent>())
		{
			if (!ensure(MeleeTraceInfo.TraceShape->IsValidLowLevelFast()))
			{
				UE_LOG(LogMeleeTrace,
					Error,
					TEXT("Invalid trace shape defined in a MeleeTrace anim notify for animation %s"),
					*Animation->GetName());
			}

			MeleeTraceComponent->StartTraceWithContext(MeleeTraceInfo, this);
		}
#if WITH_EDITOR
		else if (bShouldDrawDebugInEditor)
		{
			if (MeshComp->DoesSocketExist(MeleeTraceInfo.StartSocketName)
				&& MeshComp->DoesSocketExist(MeleeTraceInfo.EndSocketName))
			{
				DebugMeshComponent = MeshComp;
			}
			else
			{
				TArray<USceneComponent*> ChildrenComponents;
				MeshComp->GetChildrenComponents(true, ChildrenComponents);
				for (USceneComponent* ChildComponent : ChildrenComponents)
				{
					if (auto* TypedMeshComponent = Cast<UMeshComponent>(ChildComponent))
					{
						if (TypedMeshComponent->DoesSocketExist(MeleeTraceInfo.StartSocketName)
							&& TypedMeshComponent->DoesSocketExist(MeleeTraceInfo.EndSocketName))
						{
							DebugMeshComponent = TypedMeshComponent;
						}
					}
				}
			}
		}
#endif
	}
}

#if UE_VERSION_OLDER_THAN(5, 0, 0)
void UAnimNotifyState_MeleeTrace::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
#else
void UAnimNotifyState_MeleeTrace::NotifyEnd(USkeletalMeshComponent* MeshComp,
	UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
#endif
{
#if UE_VERSION_OLDER_THAN(5, 0, 0)
	Super::NotifyEnd(MeshComp, Animation);
#else
	Super::NotifyEnd(MeshComp, Animation, EventReference);
#endif

	if (const AActor* OwnerActor = MeshComp->GetOwner())
	{
		if (UMeleeTraceComponent* MeleeTraceComponent = OwnerActor->FindComponentByClass<UMeleeTraceComponent>())
		{
			MeleeTraceComponent->EndTraceWithContext(this);
		}
	}

#if WITH_EDITOR
	DebugMeshComponent.Reset();
	PreviousFrameSamples.Reset();
#endif
}

void UAnimNotifyState_MeleeTrace::NotifyTick(USkeletalMeshComponent* MeshComp,
	UAnimSequenceBase* Animation,
	float FrameDeltaTime,
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

#if WITH_EDITOR
	if (DebugMeshComponent.IsValid() && bShouldDrawDebugInEditor)
	{
		const UWorld* World = MeshComp->GetWorld();
		FCollisionShape CollisionShape;
		if (MeleeTraceInfo.TraceShape)
		{
			CollisionShape = MeleeTraceInfo.TraceShape->CreateCollisionShape();
		}

		TArray<FVector> Samples;
		const FQuat Rotation = DebugMeshComponent->GetSocketQuaternion(MeleeTraceInfo.StartSocketName);
		UMeleeTraceComponent::GetTraceSamples(DebugMeshComponent.Get(),
			MeleeTraceInfo.TraceDensity,
			MeleeTraceInfo.StartSocketName,
			MeleeTraceInfo.EndSocketName,
			Samples);
		if (PreviousFrameSamples.Num() == Samples.Num())
		{
			for (int32 Index = 0; Index < Samples.Num(); Index++)
			{
				MeleeTrace::DrawDebugTrace(World,
					CollisionShape,
					FTransform(Rotation, PreviousFrameSamples[Index]),
					FTransform(Rotation, Samples[Index]),
					EDrawDebugTrace::ForDuration,
					false,
					{},
					DebugDrawDuration);
			}
		}

		PreviousFrameSamples = MoveTemp(Samples);
	}
#endif
}
#endif
*/