


#include "AbilitySystem/Abilities/Monster/FieldMonster/Kronos/KronosAbility_SweepAttack.h"
#include "Character/FieldMonster/FieldMonster_Kronos.h"
#include "Character/R1Character.h"
#include "Character/R1Monster.h"
#include "Structures/TraceHitInfo.h"

void UKronosAbility_SweepAttackTask::Activate()
{
	Super::Activate();
	bTickingTask = true;

	AFieldMonster_Kronos* Kronos = Cast<AFieldMonster_Kronos>(GetAvatarActor());
	if (Kronos == nullptr) return;



}

void UKronosAbility_SweepAttackTask::TickTask(float DeltaTime)
{
	Super::TickTask(DeltaTime);

	if (WeakTarget.IsValid())
	{
		AR1Character* TargetCharacter = WeakTarget.Get();
		FVector TargetLocation = TargetCharacter->GetActorLocation();

		AR1Monster* OwnMonster = Cast<AR1Monster>(GetAvatarActor());
		FVector DesiredVec = TargetLocation - OwnMonster->GetActorLocation();
		DesiredVec.Z = 0;
		DesiredVec.Normalize();

		OwnMonster->SetDesiredVec(DesiredVec);
	}
}

void UKronosAbility_SweepAttackTask::OnDestroy(bool bInOwnerFinished)
{
	Super::OnDestroy(bInOwnerFinished);
}

bool UKronosAbility_SweepAttackTask::AttackSucceed(const FMeleeHitInfo& MeleeHitInfo, const FTraceHitInfo& TraceHitInfo)
{
	if (Super::AttackSucceed(MeleeHitInfo, TraceHitInfo) == false) return false;


	return true;
}











UKronosAbility_SweepAttack::UKronosAbility_SweepAttack()
	: Super()
{
}

bool UKronosAbility_SweepAttack::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	if (Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags) == false)
	{
		return false;
	}
	return true;
}

void UKronosAbility_SweepAttack::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	UKronosAbility_SweepAttackTask* Task = UAbilityTask::NewAbilityTask<UKronosAbility_SweepAttackTask>(this);
	Task->ReadyForActivation();
}

void UKronosAbility_SweepAttack::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
