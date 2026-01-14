#pragma once
#include "CoreMinimal.h"

SUQS_API DECLARE_LOG_CATEGORY_EXTERN(LogSUQS, Verbose, Verbose);


#define LogMsg(x)													\
do {																\
	if (GEngine)													\
	{																\
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Cyan, x); \
	}																\
	UE_LOG(LogSUQS, Warning, TEXT("%s"), x);						\
} while (0)		