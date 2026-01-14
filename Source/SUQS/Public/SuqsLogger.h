

#pragma once

SUQS_API DECLARE_LOG_CATEGORY_EXTERN(SUQSLog, Verbose, Verbose)


#define MsgBoth(Caller, Msg)											\
do {																	\
	if (GEngine)														\
	{																	\
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Cyan, Msg);	\
	}																	\
																		\
	FString LogMsg = Caller + " :: " + Msg;								\
	UE_LOG(SUQSLog, Warning, TEXT("%s"), *LogMsg);						\
} while(0)

#define MsgLog(Caller, Msg)								\
do {													\
	FString LogMsg = Caller + " :: " + Msg;				\
	UE_LOG(SUQSLog, Warning, TEXT("%s"), *LogMsg);		\
} while(0)