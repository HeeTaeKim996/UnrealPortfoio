


#include "System/Subsystem/SaveGame/SaveUI/UserWidget_SaveData.h"
#include "../SaveDataManager.h"
#include "../SaveData/SaveDataLog.h"
#include "Components/Button.h"
#include "Components/ListView.h"
#include "UserWidget_SaveSlotMeta.h"
#include "Components/TextBlock.h"

UUserWidget_SaveData::UUserWidget_SaveData()
	: Super()
{
	
}

void UUserWidget_SaveData::NativeConstruct()
{
	Super::NativeConstruct();

	if (Button_Exit)
	{
		Button_Exit->OnClicked.AddDynamic(this, &UUserWidget_SaveData::OnExitButtonClicked);
	}
	if (Button_SaveCurrent)
	{
		Button_SaveCurrent->OnClicked.AddDynamic(this, &UUserWidget_SaveData::OnSaveCurrentButtonClicked);
	}
	if (Button_SaveAppendary)
	{
		Button_SaveAppendary->OnClicked.AddDynamic(this, &UUserWidget_SaveData::OnSaveAppendaryButtonClicked);
	}

	UpdateListView();
}

void UUserWidget_SaveData::UpdateListView()
{
	if (ListView_Datas == nullptr) return;

	const TArray<FSaveSlotMeta>& SaveSlotMetas = USaveDataManager::Get(this)->GetSaveDatas();

	TempObjects.Reset();

	TempObjects.Reserve(SaveSlotMetas.Num());
	for (int i = 0; i < SaveSlotMetas.Num(); i++)
	{
		UTempSaveSlotObject* TempObject = NewObject<UTempSaveSlotObject>(this);
		TempObject->SaveSlotMeta = SaveSlotMetas[i];
		
		TempObjects.Add(TempObject);
	}

	ListView_Datas->ClearListItems();
	ListView_Datas->SetListItems(TempObjects);

}

void UUserWidget_SaveData::OnExitButtonClicked()
{
	// TODO
}

void UUserWidget_SaveData::OnSaveCurrentButtonClicked()
{
	USaveDataManager::Get(this)->SaveCurrent();
}

void UUserWidget_SaveData::OnSaveAppendaryButtonClicked()
{
	USaveDataManager::Get(this)->SaveAppendary();
	UpdateListView();
}
