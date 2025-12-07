
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

	{ // TEMP
		AttributeSet->InitHealth(100);
		AttributeSet->InitMaxHealth(100);

		AttributeSet->InitBaseDamage(50);
	}

	


	RefreshHpBarRatio();


	MeleeTrace->OnTraceStart.AddDynamic(this, &ThisClass::HandleTraceStarted);
	MeleeTrace->OnTraceEnd.AddDynamic(this, &ThisClass::HandleTraceEnded);
	MeleeTrace->OnTraceHit.AddDynamic(this, &ThisClass::HandleTraceHit);

	CharacterASC->Delegate_OnTagUpdated.BindUObject(this, &AR1Character::OnTagUpdated);

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
	if (CharacterASC->HasMatchingGameplayTag(R1Tags::Ability_Dead)) return;

	CharacterASC->AddLooseGameplayTag(R1Tags::Ability_Dead); // ※ Will Be Replace by Invoking Ability
}


void AR1Character::HandleGameplayTagEvent(FGameplayTag EventTag)
{
	if(EventTag.MatchesTag(R1Tags::Event_Montage_End))
	{

	}
}

void AR1Character::HitReact(const FHitResult* HitResult, FGameplayTag ReactTag)
{
	AbilityCancel(UTagContainersManager::Get(this)->OnHitReact_CancelTags());

	FVector ReactDir = HitResult->Location - GetActorLocation();
	ReactDir.Z = 0;
	ReactDir.Normalize();

	float Cos = DesiredVec.Dot(ReactDir);
	float Sin = DesiredVec.Cross(ReactDir).Z; // Prelude Two Vectors are span of x,y
	
	if (Cos > COS_45)
	{
		ActivateAbility(R1Tags::Ability_Action_HitReact_Base_Fwd);
	}
	else if (Cos > -COS_45)
	{
		if (Sin > 0)
		{
			ActivateAbility(R1Tags::Ability_Action_HitReact_Base_Right);
		}
		else
		{
			ActivateAbility(R1Tags::Ability_Action_HitReact_Base_Left);
		}
	}
	else
	{
		ActivateAbility(R1Tags::Ability_Action_HitReact_Base_Bwd);
	}
}

void AR1Character::Die(const FHitResult* HitResult, FGameplayTag ReactDieTag)
{
	DebugMessage(TEXT("DieCheck"));
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
		FString::Printf(TEXT("R1Character.cpp : Ability : [%s]"), *HitInfo.Ability.GetTagName().ToString() ));
#endif

	//GAS_OnAttackSucceed.Broadcast(HitInfo);
}















void AR1Character::InitializeCharacterAbilities()
{
	UR1AbilitySystemComponent* ASC = Cast<UR1AbilitySystemComponent>(CharacterASC);
	if (ASC == nullptr) return;

	ASC->AddCharacterAbilities(StartupAbilities);

	if (BaseAbilities.HitReact_Fwd != nullptr)
	{
		ASC->AddCharacterAbility(BaseAbilities.HitReact_Fwd);
	}
	if (BaseAbilities.HitReact_Right != nullptr)
	{
		ASC->AddCharacterAbility(BaseAbilities.HitReact_Right);
	}
	if (BaseAbilities.HitReact_Left != nullptr)
	{
		ASC->AddCharacterAbility(BaseAbilities.HitReact_Left);
	}
	if (BaseAbilities.HitReact_Bwd != nullptr)
	{
		ASC->AddCharacterAbility(BaseAbilities.HitReact_Bwd);
	}

}

void AR1Character::AbilityCancel(FGameplayTagContainer CancelTags)
{
	CharacterASC->CancelAbilities(&CancelTags, nullptr, nullptr); 

	//CharacterASC->CancelAbilityByTag(CancelTags.First());
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
}
