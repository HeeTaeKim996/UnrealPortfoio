


#include "System/Menu/MenuPlayerController.h"
#include "System/R1GameplayTags.h"
#include "System/R1AssetManager.h"
#include "MenuUserWidget.h"
#include "Data/Data_UserWidget.h"

AMenuPlayerController::AMenuPlayerController()
	: Super()
{
}

void AMenuPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UData_UserWidget* Data_UserWidgets = UR1AssetManager::GetAssetByName<UData_UserWidget>(R1Tags::Asset_UserWidget_UserWidgets);

	TSubclassOf<UMenuUserWidget> MenuUserWidgetClass = Data_UserWidgets->MenuUserWidgetClass;
	if (MenuUserWidgetClass)
	{
		MenuUI = CreateWidget<UMenuUserWidget>(this, MenuUserWidgetClass);
		if (MenuUI)
		{
			MenuUI->AddToViewport();
		}
	}

}

void AMenuPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
}

void AMenuPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
}
