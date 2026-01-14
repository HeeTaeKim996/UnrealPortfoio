


#include "UI/UserWidget_FieldHPBar.h"
#include "Components/ProgressBar.h"
#include "MainLogger.h"

UUserWidget_FieldHPBar::UUserWidget_FieldHPBar(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void UUserWidget_FieldHPBar::NativeConstruct()
{
	Super::NativeConstruct();
}

void UUserWidget_FieldHPBar::SetHpRatio(float Ratio)
{
	HpBar->SetPercent(Ratio);

	{
		FString Msg = FString::Printf(TEXT("UserWidget_FieldHPBar.cpp : [%f]."), Ratio);
		MsgLog(FString("UserWidget_FieldHPBar.cpp"), Msg);
	}

}
