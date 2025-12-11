
#include "Character/R1Character.h"
#include "Components/CapsuleComponent.h"
#include "Character/R1CharacterMovementComponent.h"
#include "AbilitySystem/ASC/CharacterASC.h"
#include "AbilitySystem/Attributes/R1AttributeSet.h"
#include "AbilitySystem/Abilities/R1GameplayAbility.h"
#include "System/Subsystem/TagContainersManager.h"


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



	InitializeCharacterAbilities();




	MeleeTrace->OnTraceStart.AddDynamic(this, &ThisClass::HandleTraceStarted);
	MeleeTrace->OnTraceEnd.AddDynamic(this, &ThisClass::HandleTraceEnded);
	MeleeTrace->OnTraceHit.AddDynamic(this, &ThisClass::HandleTraceHit);

	CharacterASC->Delegate_OnTagUpdated.BindUObject(this, &AR1Character::OnTagUpdated);
	CharacterASC->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetHealthAttribute())
		.AddUObject(this, &AR1Character::OnHealthChanged);
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



void AR1Character::OnDead(TObjectPtr<AR1Character> From)
{
	if (CharacterASC->HasMatchingGameplayTag(R1Tags::Ability_Dead)) return;

	CharacterASC->AddLooseGameplayTag(R1Tags::Ability_Dead); // ※ Will Be Replace by Invoking Ability
}


void AR1Character::HandleGameplayTagEvent(FGameplayTag EventTag)
{
	if (EventTag.MatchesTag(R1Tags::Event_Montage_End))
	{

	}
}





void AR1Character::OnHealthChanged(const FOnAttributeChangeData& Data)
{
	RefreshHpBarRatio(Data.NewValue);
}


UAbilitySystemComponent* AR1Character::GetAbilitySystemComponent() const
{
	return CharacterASC;
}

UR1AbilitySystemComponent* AR1Character::GetR1AbilitySystemComponent()
{
	return CharacterASC;
}

void AR1Character::InitAbilitySystem()
{

}

FGameplayAbilitySpecHandle AR1Character::ActivateAbility(FGameplayTag AbilityTag)
{
	return CharacterASC->ActivateAbility(AbilityTag);
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
		FString::Printf(TEXT("R1Character.cpp : Ability : [%s]"), *HitInfo.Ability.GetTagName().ToString()));
#endif

	//GAS_OnAttackSucceed.Broadcast(HitInfo);
}















void AR1Character::InitializeCharacterAbilities()
{
	UR1AbilitySystemComponent* ASC = Cast<UR1AbilitySystemComponent>(CharacterASC);
	if (ASC == nullptr) return;

	ASC->AddCharacterAbilities(StartupAbilities);

	if (BaseSettings.HitReactAbility != nullptr)
	{
		ASC->AddCharacterAbility(BaseSettings.HitReactAbility);
	}
	if (BaseSettings.KnockdownAbility != nullptr)
	{
		ASC->AddCharacterAbility(BaseSettings.KnockdownAbility);
	}
	if (BaseSettings.DeadAbility != nullptr)
	{
		ASC->AddCharacterAbility(BaseSettings.DeadAbility);
	}
	

}

void AR1Character::AbilityCancel(FGameplayTagContainer CancelTags)
{
	CharacterASC->CancelAbilities(&CancelTags, nullptr, nullptr);

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance)
	{
		AnimInstance->StopAllMontages(0.1f);
	}
}







void AR1Character::AddState(FGameplayTag NewState)
{
	CharacterASC->AddLooseGameplayTag(NewState);
}

bool AR1Character::IsInState(FGameplayTag StateTag) const
{
	return CharacterASC->HasMatchingGameplayTag(StateTag);
}

bool AR1Character::IsInAnyState(const FGameplayTagContainer& StateTags)
{
	return CharacterASC->HasAnyMatchingGameplayTags(StateTags);
}

bool AR1Character::IsInAllStates(const FGameplayTagContainer& StateTags)
{
	return CharacterASC->HasAllMatchingGameplayTags(StateTags);
}



void AR1Character::OnTagUpdated(const FGameplayTag& Tag, bool TagExists)
{


	if (Tag == R1Tags::Ability_Action_HitReact && TagExists == false)
	{
		int i = 0;
	}
	if (Tag == R1Tags::Ability_Action_HitReact && TagExists == true)
	{
		int i = 0;
	}
}
