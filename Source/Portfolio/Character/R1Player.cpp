


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
#include "AbilitySystem/R1AbilitySystemComponent.h"

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

	MeleeTrace = CreateDefaultSubobject<UMeleeTraceComponent>(TEXT("MeleeTrace"));
	MeleeTrace->SetTraceChannel(ECC_GameTraceChannel3);
}

void AR1Player::BeginPlay()
{
	Super::BeginPlay();

	PlayerAnim = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnBeginOverlap);

	SetCreatureState(ECreatureState::Loco);

	MeleeTrace->OnTraceHit.AddDynamic(this, &ThisClass::HandleTraceHit);
	MeleeTrace->OnTraceStart.AddDynamic(this, &ThisClass::HandleTraceStarted);
	MeleeTrace->OnTraceEnd.AddDynamic(this, &ThisClass::HandleTraceEnded);

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
		AbilitySystemComponent = Cast<UR1AbilitySystemComponent>(PS->GetAbilitySystemComponent());
		AbilitySystemComponent->InitAbilityActorInfo(PS, this);

		AttributeSet = PS->GetR1PlayerSet();
	}
}

void AR1Player::EndPlay(const EEndPlayReason::Type EndPlayReasion)
{
	Super::EndPlay(EndPlayReasion);

	MeleeTrace->OnTraceHit.RemoveDynamic(this, &ThisClass::HandleTraceHit);
	MeleeTrace->OnTraceStart.RemoveDynamic(this, &ThisClass::HandleTraceStarted);
	MeleeTrace->OnTraceEnd.RemoveDynamic(this, &ThisClass::HandleTraceEnded);
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

void AR1Player::HandleTraceHit(UMeleeTraceComponent* ThisComponent, AActor* HitActor, const FVector& HitLocation, const FVector& HitNormal, FName HitBoneName, FMeleeTraceInstanceHandle TraceHandle, uint8 Protocol)
{
	//DebugMessage(FString::Printf(TEXT("R1Player.cpp : Protocol IS [%d]"), static_cast<int>(Protocol)));

	AR1Monster* Monster = Cast<AR1Monster>(HitActor);
	if (Monster)
	{
		Monster->OnDamage(20, this);
	}
}

void AR1Player::HandleTraceStarted(UMeleeTraceComponent* ThisComponent, 
	FMeleeTraceInstanceHandle TraceHandle)
{
}

void AR1Player::HandleTraceEnded(UMeleeTraceComponent* ThisComponent, int32 HitCount, 
	FMeleeTraceInstanceHandle TraceHandle)
{
}

void AR1Player::RefreshHpBarRatio()
{
	float Hp = AttributeSet->GetHealth();
	float MaxHp = AttributeSet->GetMaxHealth();

	float Ratio = Hp / MaxHp;
	Cast<AR1PlayerController>(GetController())->GetMainUI()->UpdatePlayerHealthBar(Ratio);
}

void AR1Player::ActivateAbility(FGameplayTag AbilityTag)
{
	AbilitySystemComponent->ActivateAbility(AbilityTag);
}


