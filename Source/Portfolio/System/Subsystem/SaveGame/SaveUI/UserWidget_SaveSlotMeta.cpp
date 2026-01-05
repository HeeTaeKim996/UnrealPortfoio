


#include "System/Subsystem/SaveGame/SaveUI/UserWidget_SaveSlotMeta.h"
#include "Components/TextBlock.h"
#include "../SaveData/SaveDataLog.h"
#include "Components/Button.h"
#include "../SaveDataManager.h"

UUserWidget_SaveSlotMeta::UUserWidget_SaveSlotMeta()
	: Super()
{

}

void UUserWidget_SaveSlotMeta::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	UTempSaveSlotObject* TempObject = Cast<UTempSaveSlotObject>(ListItemObject);
	if (TempObject)
	{
		SaveSlotObject = TempObject;

		Text_SlotName->SetText(FText::FromString(TempObject->SaveSlotMeta.SlotName));
#if 0
		UE_LOG(LogTemp, Warning, TEXT("UserWidget_SaveSlotMeta : [%s]"),
			*TempObject->SaveSlotMeta->SlotName);
#endif

	}
	if (Button_CurrentSwitch)
	{
		Button_CurrentSwitch->OnClicked.AddUniqueDynamic(this, &UUserWidget_SaveSlotMeta::OnCurrentSwitchButtonClicked);
	}
}

void UUserWidget_SaveSlotMeta::OnCurrentSwitchButtonClicked()
{
	if (SaveSlotObject)
	{
		USaveDataManager::Get(this)->SwitchCurrentMainData(SaveSlotObject->SaveSlotMeta.SlotName);
	}
}
