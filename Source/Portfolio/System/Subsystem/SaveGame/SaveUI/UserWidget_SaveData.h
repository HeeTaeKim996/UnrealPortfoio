

#pragma once

#include "CoreMinimal.h"
#include "UI/R1UserWidget.h"
#include "UserWidget_SaveData.generated.h"

class UButton;
class UListView;
class UUserWidget_SaveSlotMeta;
class UTempSaveSlotObject;

UCLASS()
class PORTFOLIO_API UUserWidget_SaveData : public UR1UserWidget
{
	GENERATED_BODY()
public:
	UUserWidget_SaveData();

protected:
	virtual void NativeConstruct() override;
	
private:
	void UpdateListView();

	UFUNCTION()
	void OnExitButtonClicked();

	UFUNCTION()
	void OnSaveCurrentButtonClicked();

	UFUNCTION()
	void OnSaveAppendaryButtonClicked();

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Button_SaveCurrent;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Button_SaveAppendary;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Button_Exit;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UListView> ListView_Datas;


protected:
	UPROPERTY()
	TArray<UTempSaveSlotObject*> TempObjects;
};
