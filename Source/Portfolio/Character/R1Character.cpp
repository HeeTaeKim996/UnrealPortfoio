
#include "Character/R1Character.h"
#include "Components/CapsuleComponent.h"
#include "Character/R1CharacterMovementComponent.h"
#include "AbilitySystem/R1AbilitySystemComponent.h"
#include "AbilitySystem/Attributes/R1AttributeSet.h"
#include "AbilitySystem/Abilities/R1GameplayAbility.h"

AR1Character::AR1Character(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UR1CharacterMovementComponent>(CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = true;

	UMeshComponent* CharacterMesh = GetMesh();
	CharacterMesh->SetRelativeLocationAndRotation(FVector(0, 0, -88.f), FRotator(0, -90.f, 0));

	MeleeTrace = CreateDefaultSubobject<UMeleeTraceComponent>(TEXT("MeleeTrace"));
}


void AR1Character::BeginPlay()
{
	Super::BeginPlay();

	RefreshHpBarRatio();

	AddCharacterAbilities();

	MeleeTrace->OnTraceStart.AddDynamic(this, &ThisClass::HandleTraceStarted);
	MeleeTrace->OnTraceEnd.AddDynamic(this, &ThisClass::HandleTraceEnded);
	MeleeTrace->OnTraceHit.AddDynamic(this, &ThisClass::HandleTraceHit);
}

void AR1Character::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	MeleeTrace->OnTraceStart.RemoveDynamic(this, &ThisClass::HandleTraceStarted);
	MeleeTrace->OnTraceEnd.RemoveDynamic(this, &ThisClass::HandleTraceEnded);
	MeleeTrace->OnTraceHit.RemoveDynamic(this, &ThisClass::HandleTraceHit);
}

void AR1Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bUseDesiredVec)
	{
		float Alpha = FMath::Clamp(DeltaTime * 8.f, 0.f, 1.f);
		FQuat SlerpQuat = FQuat::Slerp(GetActorRotation().Quaternion(), DesiredVec.Rotation().Quaternion(), Alpha);
		SetActorRotation(SlerpQuat);
	}
	
}

void AR1Character::Highlight()
{
	bHighlighted = true;
}

void AR1Character::UnHighlight()
{
	bHighlighted = false;
}

void AR1Character::OnDamage(int Damage, TObjectPtr<AR1Character> From)
{
	float Hp = AttributeSet->GetHealth();
	float MaxHp = AttributeSet->GetMaxHealth();

	Hp = FMath::Clamp(Hp - Damage, 0, MaxHp);
	AttributeSet->SetHealth(Hp);
	if (Hp == 0)
	{
		OnDead(From);
	}

	RefreshHpBarRatio();
	//DebugMessage(FString::Printf(TEXT("HP : %d"), Hp))
}

void AR1Character::OnDead(TObjectPtr<AR1Character> From)
{
	if (CreatureState == ECreatureState::Dead) return;

	CreatureState = ECreatureState::Dead;
	
}

void AR1Character::ToLoco()
{
	CreatureState = ECreatureState::Loco;
	bUseDesiredVec = true;
}


void AR1Character::HandleGameplayTagEvent(FGameplayTag EventTag)
{
	if(EventTag.MatchesTag(R1Tags::Event_Montage_End))
	{
		
	}
}

UAbilitySystemComponent* AR1Character::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AR1Character::InitAbilitySystem()
{

}

void AR1Character::ActivateAbility(FGameplayTag AbilityTag)
{
	AbilitySystemComponent->ActivateAbility(AbilityTag);
}


void AR1Character::HandleTraceStarted(UMeleeTraceComponent* ThisComponent, FMeleeTraceInstanceHandle TraceHandle)
{

}

void AR1Character::HandleTraceEnded(UMeleeTraceComponent* ThisComponent, int32 HitCount, 
	FMeleeTraceInstanceHandle TraceHandle)
{

}

void AR1Character::HandleTraceHit(FMeleeHitInfo HitInfo)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Cyan, 
		FString::Printf(TEXT("R1Character.cpp : Ability : [%s]"), *HitInfo.Ability.GetTagName().ToString() ));

	GAS_OnTraceHit.Broadcast(HitInfo);
}















void AR1Character::AddCharacterAbilities()
{
	UR1AbilitySystemComponent* ASC = Cast<UR1AbilitySystemComponent>(AbilitySystemComponent);
	if (ASC == nullptr) return;

	ASC->AddCharacterAbilities(StartupAbilities);
}

void AR1Character::EndAbilitySuccess(FGameplayTag InTag)
{
	GAS_OnAbilitySuccess.Broadcast(InTag);
}

void AR1Character::CancelAbility(FGameplayTag InTag)
{
	GAS_OnAbilityCancel.Broadcast(InTag);
}

void AR1Character::CancelAbilities()
{
	UR1AbilitySystemComponent* ASC = Cast<UR1AbilitySystemComponent>(AbilitySystemComponent);
	if (ASC == nullptr) return;

	ASC->CancelAbilities();
}

