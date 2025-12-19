// Copyright 2023, Robert Lewicki, All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "MeleeTraceInfo.generated.h"

class UMeleeTraceShape;

USTRUCT(BlueprintType)
struct MELEETRACE_API FMeleeTraceSmallInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "General")
	FName SocketName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Instanced, Category = "General") // ※ Instanced : Similar With DeppCopy. ※ I Dont Understand WHy This Need Deep COpy. It Works Only For Transfering Base Info
		TObjectPtr<UMeleeTraceShape> TraceShape;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gemeral")
	uint8 Protocol = 0;
};

USTRUCT(BlueprintType)
struct MELEETRACE_API FMeleeTraceInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "General")
	TArray<FMeleeTraceSmallInfo> MeleeTraceInfos;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gemeral")
	FGameplayTag Ability;
};












































































/*
#if 0
USTRUCT(BlueprintType)
struct MELEETRACE_API FMeleeTraceInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "General")
	FName StartSocketName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "General")
	FName EndSocketName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Instanced, Category = "General")
	TObjectPtr<UMeleeTraceShape> TraceShape;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "General")
	int32 TraceDensity = 5;
};
#endif
*/