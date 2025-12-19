


#include "Character/FieldMonster.h"
#include "Components/WidgetComponent.h"
#include "UI/UserWidget_FieldHPBar.h"
#include "AbilitySystem/Attributes/R1AttributeSet.h"

AFieldMonster::AFieldMonster()
	: Super()
{
	PrimaryActorTick.bCanEverTick = true;

	HpBarComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBar"));
	HpBarComponent->SetupAttachment(GetRootComponent());


	// ※ Assigning TSubclass at ContructorPhase by BP or AssetManager is Impossible (they didnt loaded yet)
	//    So Assigning by address is only option
	ConstructorHelpers::FClassFinder<UUserWidget> HealthBarWidgetClass(
		TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Data/StaticPaths/WBP_HpBar.WBP_HpBar_C'"));
	if (HealthBarWidgetClass.Succeeded())
	{
		HpBarComponent->SetWidgetClass(HealthBarWidgetClass.Class);
		HpBarComponent->SetWidgetSpace(EWidgetSpace::Screen);
		HpBarComponent->SetDrawAtDesiredSize(true);
		HpBarComponent->SetRelativeLocation(FVector(0, 0, 100));
	}

}

void AFieldMonster::RefreshHpBarRatio(float NewHealth)
{
	Super::RefreshHpBarRatio(NewHealth);

	if (!HpBarComponent) return;

	UUserWidget_FieldHPBar* HpBar = Cast<UUserWidget_FieldHPBar>(HpBarComponent->GetUserWidgetObject());
	
	float MaxHp = AttributeSet->GetMaxHealth();

	float Ratio = NewHealth / MaxHp;
	HpBar->SetHpRatio(Ratio);
}
