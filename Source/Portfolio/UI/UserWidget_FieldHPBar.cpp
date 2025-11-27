


#include "UI/UserWidget_FieldHPBar.h"
#include "Components/ProgressBar.h"

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

	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Cyan,
		FString::Printf(TEXT("UserWidget_FieldHPBar.cpp : [%f]."), Ratio));
}
