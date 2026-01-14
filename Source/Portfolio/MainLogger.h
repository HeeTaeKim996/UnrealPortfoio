

#pragma once

PORTFOLIO_API DECLARE_LOG_CATEGORY_EXTERN(MainLog, Verbose, Verbose)

#define MsgBoth(Caller, Msg)											\
do{																		\
	if (GEngine)														\
	{																	\
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Cyan, Msg);	\
	}																	\
																		\
	FString LogMsg = Caller + " :: " + Msg;								\
	UE_LOG(MainLog, Warning, TEXT("%s"), *LogMsg);						\
} while(0)			

#define MsgLog(Caller, Msg)												\
do {																	\
	FString LogMsg = Caller + " :: " + Msg;								\
	UE_LOG(MainLog, Warning, TEXT("%s"), *LogMsg);						\
} while(0)