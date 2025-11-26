
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
}


void AR1Character::BeginPlay()
{
	Super::BeginPlay();

	RefreshHpBarRatio();

	AddCharacterAbilities();
}

void AR1Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	float Alpha = FMath::Clamp(DeltaTime * 8.f, 0.f, 1.f);
	FQuat SlerpQuat = FQuat::Slerp(GetActorRotation().Quaternion(), DesiredVec.Rotation().Quaternion(), Alpha);
	SetActorRotation(SlerpQuat);
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


void AR1Character::HandleGameplayTagEvent(FGameplayTag EventTag)
{
	if(EventTag.MatchesTag(R1Tags::Event_Montage_End))
	{
		CreatureState = ECreatureState::Loco;
	}
}

UAbilitySystemComponent* AR1Character::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AR1Character::InitAbilitySystem()
{

}

void AR1Character::HandleTraceHit(UMeleeTraceComponent* ThisComponent, AActor* HitActor, const FVector& HitLocation, 
	const FVector& HitNormal, FName HitBoneName, FMeleeTraceInstanceHandle TraceHandle, uint8 Protocol)
{

}

void AR1Character::HandleTraceStarted(UMeleeTraceComponent* ThisComponent, FMeleeTraceInstanceHandle TraceHandle)
{

}

void AR1Character::HandleTraceEnded(UMeleeTraceComponent* ThisComponent, int32 HitCount, 
	FMeleeTraceInstanceHandle TraceHandle)
{

}

void AR1Character::AddCharacterAbilities()
{
	UR1AbilitySystemComponent* ASC = Cast<UR1AbilitySystemComponent>(AbilitySystemComponent);
	if (ASC == nullptr) return;

	ASC->AddCharacterAbilities(StartupAbilities);
}

