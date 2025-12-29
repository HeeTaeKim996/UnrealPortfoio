


#include "Character/FieldMonster.h"
#include "Components/WidgetComponent.h"
#include "UI/UserWidget_FieldHPBar.h"
#include "AbilitySystem/Attributes/R1AttributeSet.h"
#include "System/Subsystem/FieldMonsterManager/FieldMonsterManager.h"
#include "AI/FieldMonster/FieldMonsterController.h"
#include "BrainComponent.h"

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

void AFieldMonster::BeginPlay()
{
	Super::BeginPlay();

	if (StreamingLevel.IsNull())
	{
		const FString Msg = FString::Printf(TEXT("FieldMonster[%s]'s Streaming Level is Not assigned"), *GetName());

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, Msg);
		UE_LOG(LogTemp, Warning, TEXT("%s"), *Msg);
	}
	else
	{
#if 1
		const FSoftObjectPath& LevelPath_Debug = StreamingLevel.ToSoftObjectPath();

		const FString Msg = FString::Printf(TEXT("FieldMonster.cpp : LevelAsset [%s]"),
			*LevelPath_Debug.GetLongPackageName());

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, Msg);
		UE_LOG(LogTemp, Warning, TEXT("%s"), *Msg);

		const FString CurrWorldMsg = FString::Printf(TEXT("FieldMonster.cpp : CurrentLevel [%s]"),
			*GetLevel()->GetOutermost()->GetName());

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, CurrWorldMsg);
		UE_LOG(LogTemp, Warning, TEXT("%s"), *CurrWorldMsg);
#endif
		LandLevelName = GetLevel()->GetOutermost()->GetFName();

		const FSoftObjectPath& Path = StreamingLevel.ToSoftObjectPath();
		LevelStreamingName = Path.GetLongPackageFName();

		UFieldMonsterManager::Get(this)->RegisterFieldMonster(LandLevelName, LevelStreamingName, this);
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



void AFieldMonster::Sleep()
{
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
	SetActorEnableCollision(false);
	if (AFieldMonsterController* FAICon = Cast<AFieldMonsterController>(GetController()))
	{
		FAICon->GetBrainComponent()->StopLogic(TEXT("Sleep"));
	}

	bIsSleeping = true;
}

void AFieldMonster::Wakeup()
{
	SetActorHiddenInGame(false);
	SetActorTickEnabled(true);
	SetActorEnableCollision(true);
	if (AFieldMonsterController* FAICon = Cast<AFieldMonsterController>(GetController()))
	{
		FAICon->GetBrainComponent()->RestartLogic();
	}

	bIsSleeping = false;
}

void AFieldMonster::DoWork()
{
	bIsWorking = true;
}
void AFieldMonster::LeaveWork()
{
	bIsWorking = false;

	UFieldMonsterManager* FieldMonsterManager = UFieldMonsterManager::Get(this);
	if (FieldMonsterManager == nullptr) return;

	FieldMonsterManager->OnLeaveWork(LevelStreamingName, this);
}