// Copyright 2023, Robert Lewicki, All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "CollisionShape.h"
#include "MeleeTraceCommon.h"
#include "GameplayTagContainer.h"
#include "ActiveMeleeTraceInfo.generated.h"

class AActor;
class UMeshComponent;


USTRUCT(BlueprintType)
struct MELEETRACE_API FMeleeTraceInstanceHandle
{
	GENERATED_BODY()

	FMeleeTraceInstanceHandle() = default;
	FMeleeTraceInstanceHandle(uint32 InTraceHash) : TraceHash(InTraceHash) {}

	UPROPERTY()
	uint32 TraceHash = TNumericLimits<uint32>::Max();

	bool operator==(const FMeleeTraceInstanceHandle& Other) const { return TraceHash == Other.TraceHash; }
};

USTRUCT()
struct MELEETRACE_API FMeleeTraceSocketShapeInfo
{
	GENERATED_BODY()

	FQuat RotationOffset; // ※ Socket's Quaternion * RotationOffset -> World Quat
	FCollisionShape TraceCollisionShape;
	TWeakObjectPtr<UMeshComponent> SourceMeshComponent;
	FVector PreviousFrameSampleLocation;
	double PreviousFrameTime;
	FQuat PrevRotation;

	FName SocketName;
	uint8 Protocol;
};

USTRUCT()
struct MELEETRACE_API FActiveMeleeTraceInfo
{
	GENERATED_BODY()

	FMeleeTraceInstanceHandle TraceHandle;

	TArray<FMeleeTraceSocketShapeInfo> SocketShapeInfos;
	

	TSet<TWeakObjectPtr<AActor>> HitActors; // ※ Prevent repeated hits
	FGameplayTag Ability;
	
	uint32 ContextHash = MeleeTrace::INVALID_HASH;
};















































































/*
#if 0
USTRUCT(BlueprintType)
struct MELEETRACE_API FMeleeTraceInstanceHandle
{
	GENERATED_BODY()

	FMeleeTraceInstanceHandle() = default;
	FMeleeTraceInstanceHandle(uint32 InTraceHash) : TraceHash(InTraceHash) {};
	
	UPROPERTY()
	uint32 TraceHash = TNumericLimits<uint32>::Max();

	bool operator==(const FMeleeTraceInstanceHandle& Other) const { return TraceHash == Other.TraceHash; }
};

USTRUCT()
struct MELEETRACE_API FActiveMeleeTraceInfo
{
	GENERATED_BODY()

	FMeleeTraceInstanceHandle TraceHandle;
	int32 TraceDensity = 1;
	FQuat RotationOffset;
	FCollisionShape TraceCollisionShape;
	TWeakObjectPtr<UMeshComponent> SourceMeshComponent;
	TSet<TWeakObjectPtr<AActor>> HitActors;
	TArray<FVector> PreviousFrameSampleLocations;
	FName StartSocketName;
	FName EndSocketName;
};
#endif
*/