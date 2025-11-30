


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
#include "AbilitySystem/Attributes/R1PlayerSet.h"
#include "AbilitySystem/ASC/PlayerASC.h"
#include "System/Subsystem/TagContainersManager.h"


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

	
	

	// TEMP
	if (TestEffect && AbilitySystemComponent)
	{
		FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
		EffectContext.AddSourceObject(this);

		// Handle
		FGameplayEffectSpecHandle EffectSpecHandle = AbilitySystemComponent->MakeOutgoingSpec(TestEffect, 1, EffectContext);

		AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
	}
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
		AbilitySystemComponent = Cast<UCharacterASC>(PS->GetAbilitySystemComponent());
		AbilitySystemComponent->InitAbilityActorInfo(PS, this);

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
	 
#if 0 // Obsolate
	if (bSweep) // TEMP
	{
		TempSweep(DeltaTime);
	}
#endif
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


void AR1Player::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//GEngine->AddOnScreenDebugMessage(-1, 1.5f, FColor::Cyan, TEXT("@@OnBeginOverlap@@"));
}


void AR1Player::HandleTraceStarted(UMeleeTraceComponent* ThisComponent, 
	FMeleeTraceInstanceHandle TraceHandle)
{
	Super::HandleTraceStarted(ThisComponent, TraceHandle);
}

void AR1Player::HandleTraceEnded(UMeleeTraceComponent* ThisComponent, int32 HitCount, 
	FMeleeTraceInstanceHandle TraceHandle)
{
	Super::HandleTraceEnded(ThisComponent, HitCount, TraceHandle);
}

void AR1Player::HandleTraceHit(FMeleeHitInfo HitInfo)
{
	Super::HandleTraceHit(HitInfo);
}

void AR1Player::RefreshHpBarRatio()
{
	float Hp = AttributeSet->GetHealth();
	float MaxHp = AttributeSet->GetMaxHealth();

	float Ratio = Hp / MaxHp;
	Cast<AR1PlayerController>(GetController())->GetMainUI()->UpdatePlayerHealthBar(Ratio);
}

void AR1Player::Input_Action(FGameplayTag InActionState)
{
	if(IsInAnyState(UTagContainersManager::Get(this)->CantBaseActableTags())) return;
	
	FAbilityCancelInfo CancelInfo;
	CancelInfo.CancelTags = UTagContainersManager::Get(this)->OnActionCall_CancelingTags();
	CancelInfo.Cause = CancelCause::OnActionInvoked;
	AbilityCancel(CancelInfo);


	UPlayerASC* PlayerASC = Cast<UPlayerASC>(AbilitySystemComponent);
	PlayerASC->Action(InActionState);
}




