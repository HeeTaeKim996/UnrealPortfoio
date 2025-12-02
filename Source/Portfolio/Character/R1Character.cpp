
#include "Character/R1Character.h"
#include "Components/CapsuleComponent.h"
#include "Character/R1CharacterMovementComponent.h"
#include "AbilitySystem/ASC/CharacterASC.h"
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

	

	AddCharacterAbilities();

	AttributeSet->InitHealth(100);
	AttributeSet->InitMaxHealth(100);


	RefreshHpBarRatio();


	MeleeTrace->OnTraceStart.AddDynamic(this, &ThisClass::HandleTraceStarted);
	MeleeTrace->OnTraceEnd.AddDynamic(this, &ThisClass::HandleTraceEnded);
	MeleeTrace->OnTraceHit.AddDynamic(this, &ThisClass::HandleTraceHit);

	AbilitySystemComponent->Delegate_OnTagUpdated.BindUObject(this, &AR1Character::OnTagUpdated);

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
	if (AbilitySystemComponent->HasMatchingGameplayTag(R1Tags::State_Dead)) return;

	AbilitySystemComponent->AddLooseGameplayTag(R1Tags::State_Dead);
}

void AR1Character::ToLoco()
{
	bUseDesiredVec = true;

	// ※ Player can override to play reserved Action
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
#if 0
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Cyan, 
		FString::Printf(TEXT("R1Character.cpp : Ability : [%s]"), *HitInfo.Ability.GetTagName().ToString() ));
#endif

	//GAS_OnAttackSucceed.Broadcast(HitInfo);
}















void AR1Character::AddCharacterAbilities()
{
	UR1AbilitySystemComponent* ASC = Cast<UR1AbilitySystemComponent>(AbilitySystemComponent);
	if (ASC == nullptr) return;

	ASC->AddCharacterAbilities(StartupAbilities);
}



void AR1Character::AbilityCancel(FAbilityCancelInfo CancelInfo)
{
	GAS_OnAbilityCancel.Broadcast(CancelInfo);
}





void AR1Character::AddState(FGameplayTag NewState)
{
	AbilitySystemComponent->AddLooseGameplayTag(NewState);
}

bool AR1Character::IsInState(FGameplayTag StateTag) const
{
	return AbilitySystemComponent->HasMatchingGameplayTag(StateTag);
}

bool AR1Character::IsInAnyState(const FGameplayTagContainer& StateTags)
{
	return AbilitySystemComponent->HasAnyMatchingGameplayTags(StateTags);
}

bool AR1Character::IsInAllStates(const FGameplayTagContainer& StateTags)
{
	return AbilitySystemComponent->HasAllMatchingGameplayTags(StateTags);
}

void AR1Character::OnTagUpdated(const FGameplayTag& Tag, bool TagExists)
{
}
