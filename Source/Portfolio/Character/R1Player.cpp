


#include "Character/R1Player.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Animation/PlayerAnimInstance.h"
#include "Character/R1Monster.h"
#include "UI/MainUserWidget.h"
#include "Player/R1PlayerController.h"
#include "AbilitySystem/R1AbilitySystemComponent.h"
#include "Player/R1PlayerState.h"
#include "AbilitySystem/Attributes/R1AttributeSet.h"
#include "AbilitySystem/ASC/PlayerASC.h"
#include "System/Subsystem/TagContainersManager.h"
#include "System/R1AssetManager.h"
#include "AbilitySystem/Abilities/BaseAttackAbility.h"
#include "Structures/TraceHitInfo.h"
#include "Data/GE/Data_InitializeGEs.h"

AR1Player::AR1Player() : Super()
{
	PrimaryActorTick.bCanEverTick = true;


	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

#if 0 // Obsolate. Replaced By Desired Rotation
	CharMovement = GetCharacterMovement();
	CharMovement->bOrientRotationToMovement = true;
	CharMovement->RotationRate = FRotator(0.f, 640.f, 0.f);
#endif

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetCapsuleComponent());
	SpringArm->TargetArmLength = 800.f;
	SpringArm->SetRelativeRotation(FRotator(-60.f, 0, 0));
	SpringArm->bDoCollisionTest = false; // IgnoreCollision ( Top Down )


	{ // ※ Prevent Screen Rotation
		SpringArm->bUsePawnControlRotation = false;
		SpringArm->bInheritPitch = false;
		SpringArm->bInheritYaw = false;
		SpringArm->bInheritRoll = false;
	}


	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	Camera->bUsePawnControlRotation = false; // ※ camera does not rotate relative to arm

	PlayerMesh = GetMesh();


#if 0 // Can Address Collision State In Cpp. But Addressing It in ProjectSettings is Recommanded
	UCapsuleComponent* Capsule = GetCapsuleComponent();
	Capsule->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Capsule->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
#endif

	MeleeTrace->SetTraceChannel(ECC_GameTraceChannel3);
}

void AR1Player::BeginPlay()
{
	Super::BeginPlay();

	PlayerAnim = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnBeginOverlap);

	DeflectInfos.Reserve(DeflectMax);
	FDeflectInfo DummyInfo;
	double CurrentTime = GetWorld()->TimeSeconds;
	DummyInfo.Start = CurrentTime;
	DummyInfo.End = CurrentTime;
	DummyInfo.ParrySuccedableTime = 0;
	DeflectInfos.Add(DummyInfo);

	CharacterASC->RegisterGameplayTagEvent(R1Tags::Ability_Mode_Blocking, EGameplayTagEventType::NewOrRemoved)
		.AddUObject(this, &AR1Player::OnBlockTagChanged);
	CharacterASC->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetStaminaAttribute())
		.AddUObject(this, &AR1Player::RefreshStaminaBarRatio);
	CharacterASC->RegisterGameplayTagEvent(R1Tags::Ability_Mode_Sprint, EGameplayTagEventType::NewOrRemoved)
		.AddUObject(this, &AR1Player::OnSprintTagChanged);
	CharacterASC->RegisterGameplayTagEvent(R1Tags::Ability_MotionState_UpperSplit, EGameplayTagEventType::NewOrRemoved)
		.AddUObject(this, &AR1Player::OnUpperSplitTagChanged);
	CharacterASC->RegisterGameplayTagEvent(R1Tags::Ability_MotionState_UpperAngleSplit,
		EGameplayTagEventType::NewOrRemoved).AddUObject(this, &AR1Player::OnUpperAngleSplitTagChanged);
	CharacterASC->RegisterGameplayTagEvent(R1Tags::Ability_MotionState_None, EGameplayTagEventType::NewOrRemoved)
		.AddUObject(this, &AR1Player::OnMotionNoneTagChanged);

	AR1PlayerController* R1PC = Cast<AR1PlayerController>(GetController());
	CharacterASC->RegisterGameplayTagEvent(R1Tags::Ability_Cooldown_AssignLocation_First,
		EGameplayTagEventType::NewOrRemoved).AddUObject(R1PC, &AR1PlayerController::OnFirstSkillTagChanged);

	UData_InitializeGEs* InitializeGes = UR1AssetManager::GetAssetByName<UData_InitializeGEs>(R1Tags::Asset_GE_Initializer_GEs);

	TSubclassOf<UGameplayEffect> GE_InitializePlayerSet = InitializeGes->FindGEByTag(R1Tags::Asset_GE_InitializePlayerSet);
	ensureAlwaysMsgf(GE_InitializePlayerSet, TEXT("Initialize GE is Not assigned"));

	FGameplayEffectContextHandle Context = CharacterASC->MakeEffectContext();
	FGameplayEffectSpecHandle SpecHandle = CharacterASC->MakeOutgoingSpec(GE_InitializePlayerSet, 1.f, Context);
	CharacterASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
}

void AR1Player::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	InitAbilitySystem();
}

void AR1Player::InitAbilitySystem()
{
	Super::InitAbilitySystem();

	if (AR1PlayerState* PS = GetPlayerState<AR1PlayerState>())
	{
		CharacterASC = Cast<UCharacterASC>(PS->GetAbilitySystemComponent());
		CharacterASC->InitAbilityActorInfo(PS, this);

		AttributeSet = PS->GetR1PlayerSet();
	}
}

void AR1Player::EndPlay(const EEndPlayReason::Type EndPlayReasion)
{
	Super::EndPlay(EndPlayReasion);

}

void AR1Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsMotionStateAlert)
	{
		MotionAlertTime -= DeltaTime;
		if (MotionAlertTime <= 0)
		{
			bIsMotionStateAlert = false;
			MotionAlertTime = 0;
			MotionState = EPlayerMotionState::None;
		}
	}
}

void AR1Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AR1Player::HandleGameplayTagEvent(FGameplayTag EventTag)
{
	Super::HandleGameplayTagEvent(EventTag);
	if (EventTag.MatchesTag(R1Tags::Event_Montage_End))
	{

	}
}

void AR1Player::OnPlayerBaseAttackOn(FGameplayTag EventTag)
{
	Delegate_OnBaseAttackOn.ExecuteIfBound(EventTag);
}


void AR1Player::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//GEngine->AddOnScreenDebugMessage(-1, 1.5f, FColor::Cyan, TEXT("@@OnBeginOverlap@@"));
}





bool AR1Player::OnTraceHit(const FMeleeHitInfo& HitInfo)
{
	if (Super::OnTraceHit(HitInfo) == false) return false;

	FTraceHitInfo TraceHitInfo;

	AR1Monster* R1Monster = Cast<AR1Monster>(HitInfo.HitResult.GetActor());
	if (R1Monster)
	{
		TraceHitInfo.TraceHitResult = ETraceHitResult::Hit;

		Delegate_OnTraceHit.Broadcast(HitInfo, TraceHitInfo);
	}

	return true;
}

void AR1Player::RefreshHpBarRatio(float NewHealth)
{
	float MaxHp = AttributeSet->GetMaxHealth();

	float Ratio = NewHealth / MaxHp;
	Cast<AR1PlayerController>(GetController())->GetMainUI()->UpdatePlayerHealthBar(Ratio);
}

void AR1Player::RefreshStaminaBarRatio(const FOnAttributeChangeData& Data)
{
	float Ratio = Data.NewValue / AttributeSet->GetMaxStamina();

	Cast<AR1PlayerController>(GetController())->GetMainUI()->UpdatePlayerStaminaBar(Ratio);
}

void AR1Player::OnTagUpdated(const FGameplayTag& Tag, bool TagExists)
{
#if 0 // Obsolate
	if (Tag.MatchesTag(R1Tags::Ability_Mode_Blocking))
	{
		if (TagExists == true)
		{
			bUpperLowerSplit = true;
			SurplusAlertTime = -1.f;
		}
		else
		{
			SurplusAlertTime = 5.f;

			if (DeflectInfos.Num() > 1)
			{
				DeflectInfos[DeflectInfos.Num() - 1].End = GetWorld()->TimeSeconds;
			}
		}
	}
#endif
}


void AR1Player::Input_ActivateAbility(FGameplayTag AbilityTag)
{
	if (IsAbilityActivatable(AbilityTag) == false) return;

	AbilityCancel(UTagContainersManager::Get(this)->OnActionCall_BaseCancelingTags());

	UPlayerASC* PlayerASC = Cast<UPlayerASC>(CharacterASC);
	if (PlayerASC->ActivateAbility(AbilityTag).IsValid())
	{

	}
}

void AR1Player::Input_Block()
{
	if (IsInState(R1Tags::Ability_Mode_Blocking)) return;
	if (IsAbilityActivatable(R1Tags::Ability_Mode_Blocking) == false) return;

	AbilityCancel(UTagContainersManager::Get(this)->OnActionCall_BaseCancelingTags());

	UPlayerASC* PlayerASC = Cast<UPlayerASC>(CharacterASC);
	FGameplayAbilitySpecHandle SpecHandle = PlayerASC->ActivateAbility(R1Tags::Ability_Mode_Blocking);

	if (SpecHandle.IsValid())
	{
		if (DeflectInfos.Num() == DeflectMax)
		{
			DeflectInfos.RemoveAt(0);
		}
		FDeflectInfo DeflectInfo;
		double Current = GetWorld()->TimeSeconds;
		DeflectInfo.Start = Current;

		int Cumulative = 0;
		for (const FDeflectInfo& Defl : DeflectInfos)
		{
			if (Defl.Start > Current - 0.8)
			{
				Cumulative++;
			}
		}
		double ParrySuccedableTime = 0.2 - Cumulative * 0.6;
		if (ParrySuccedableTime < 0) ParrySuccedableTime = 0;

		DeflectInfo.ParrySuccedableTime = ParrySuccedableTime;
		DeflectInfos.Push(DeflectInfo);
	}
}





void AR1Player::Input_Cancel(FGameplayTagContainer InCancelStates)
{
	AbilityCancel(InCancelStates);
}

bool AR1Player::IsAbilityActivatable(const FGameplayTag& InActionTag)
{
	if (GAState == EGAState::BaseAttackCancellable && IsInState(R1Tags::Ability_Action_Attack_BaseAttack)
		&& InActionTag.MatchesTag(R1Tags::Ability_Action_Attack_BaseAttack) == false)
	{
		return true;
	}
	else if (GAState == EGAState::ActionContinuable && IsInState(R1Tags::Ability_Action))
	{
		return true;
	}
	else if(IsInAnyState(UTagContainersManager::Get(this)->BaseAbilityBlockTgs()))
	{
		return false;
	}


	return true;
}

void AR1Player::FinishMotionAlert()
{
	bIsMotionStateAlert = false;
	MotionAlertTime = 0;
}

void AR1Player::StartMotionAlert()
{
	bIsMotionStateAlert = true;
	MotionAlertTime = 5.f;
}

void AR1Player::OnBlockTagChanged(const FGameplayTag CallbackTag, int NewCount)
{
	DeflectInfos[DeflectInfos.Num() - 1].End = GetWorld()->TimeSeconds;
}

void AR1Player::OnSprintTagChanged(const FGameplayTag CallbackTag, int NewCount)
{
	if (NewCount >= 1)
	{
		bIsSprint = true;
		if (bIsMotionStateAlert)
		{
			FinishMotionAlert();
		}
		MotionState = EPlayerMotionState::None;
	}
	else
	{
		bIsSprint = false;
	}
}

void AR1Player::OnUpperSplitTagChanged(const FGameplayTag CallbackTag, int NewCount)
{
	if (NewCount >= 0)
	{
		if (bIsMotionStateAlert)
		{
			FinishMotionAlert();
		}
		MotionState = EPlayerMotionState::Split;
	}
	else
	{
		MotionState = EPlayerMotionState::None;
	}
}

void AR1Player::OnUpperAngleSplitTagChanged(const FGameplayTag CallbackTag, int NewCount)
{
	if (NewCount >= 0)
	{
		if (bIsMotionStateAlert)
		{
			FinishMotionAlert();
		}
		MotionState = EPlayerMotionState::Split_Angle;
	}
	else
	{
		StartMotionAlert();
	}
}

void AR1Player::OnMotionNoneTagChanged(const FGameplayTag CallbackTag, int NewCount)
{
	if (NewCount >= 0)
	{
		if (bIsMotionStateAlert)
		{
			FinishMotionAlert();
		}
		MotionState = EPlayerMotionState::None;
	}
}




