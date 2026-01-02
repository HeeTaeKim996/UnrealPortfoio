

#pragma once

#include "CoreMinimal.h"
#include "UI/R1UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "../SaveStructures/SaveSlotMeta.h"
#include "UserWidget_SaveSlotMeta.generated.h"

class UButton;
class UTextBlock;

UCLASS()
class UTempSaveSlotObject : public UObject
{
	GENERATED_BODY()

public:
	FSaveSlotMeta SaveSlotMeta;
};


UCLASS()
class PORTFOLIO_API UUserWidget_SaveSlotMeta : public UR1UserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
public:
	UUserWidget_SaveSlotMeta();
public:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

protected:
	UFUNCTION()
	void OnCurrentSwitchButtonClicked();

public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Text_SlotName;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Button_CurrentSwitch;

protected:
	UPROPERTY()
	TObjectPtr<UTempSaveSlotObject> SaveSlotObject;
};
