// Copyright 2023, Robert Lewicki, All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "Misc/EngineVersionComparison.h"

#include "MeleeTraceSettings.generated.h"

#if UE_VERSION_OLDER_THAN(5, 2, 0) // ※ Before And After From 5_2_0, Declaring ECollision Channel Differs
enum ECollisionChannel;
#else
enum ECollisionChannel : int;
#endif

UCLASS(Config = Game, DefaultToInstanced)
class MELEETRACE_API UMeleeTraceSettings : public UDeveloperSettings // ※ Editable at Project Settings
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Config, Category = "General")
	TEnumAsByte<ECollisionChannel> MeleeTraceCollisionChannel;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Config, Category = "Debug")
	FLinearColor TraceColor = FLinearColor::Red;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Config, Category = "Debug")
	FLinearColor TraceHitColor = FLinearColor::Green;
};








































































/*
#if 0
#if UE_VERSION_OLDER_THAN(5, 2, 0)
enum ECollisionChannel;
#else
enum ECollisionChannel : int;
#endif

UCLASS(Config=Game, DefaultToInstanced)
class MELEETRACE_API UMeleeTraceSettings : public UDeveloperSettings
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Config, Category = "General")
	TEnumAsByte<ECollisionChannel> MeleeTraceCollisionChannel;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Config, Category = "Debug")
	FLinearColor TraceColor = FLinearColor::Red;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Config, Category = "Debug")
	FLinearColor TraceHitColor = FLinearColor::Green;
};
#endif
*/