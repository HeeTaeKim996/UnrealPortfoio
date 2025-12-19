// Copyright Epic Games, Inc. All Rights Reserved.

#include "Portfolio.h"
#include "Modules/ModuleManager.h"
#include "ETC/R1LogChannels.h"

//IMPLEMENT_PRIMARY_GAME_MODULE( FDefaultGameModuleImpl, Portfolio, "Portfolio" );


class PortfolioModule : public FDefaultGameModuleImpl
{
	virtual void StartupModule() override
	{
		UE_LOG(LogR1, Log, TEXT("Testing StartupModule && Custom LogChannels"));
	}
	virtual void ShutdownModule() override
	{

	}
};

IMPLEMENT_PRIMARY_GAME_MODULE(PortfolioModule, Portfolio, "Portfolio");