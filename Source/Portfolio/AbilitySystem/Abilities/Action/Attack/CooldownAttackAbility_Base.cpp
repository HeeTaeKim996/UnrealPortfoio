


#include "AbilitySystem/Abilities/Action/Attack/CooldownAttackAbility_Base.h"
#include "Player/R1PlayerController.h"
#include "Character/R1Player.h"
#include "Structures/TraceHitInfo.h"

void UCooldownAttackAbilityTask_Base::Activate()
{
	Super::Activate();

	AR1PlayerController* PlayerController = Cast<AR1PlayerController>(GetWorld()->GetFirstPlayerController());
	if (PlayerController == nullptr) return;
	FVector CursorPos = PlayerController->GetCursorPos();

	AR1Player* R1Player = Cast<AR1Player>(GetAvatarActor());
	if (R1Player == nullptr) return;

	FVector Dir = CursorPos - R1Player->GetActorLocation();
	Dir.Z = 0;
	Dir.Normalize();
	R1Player->SetDesiredVec(Dir);
}

void UCooldownAttackAbilityTask_Base::TickTask(float DeltaTime)
{
	Super::TickTask(DeltaTime);

}

void UCooldownAttackAbilityTask_Base::OnDestroy(bool bInOwnerFinished)
{
	Super::OnDestroy(bInOwnerFinished);

}

bool UCooldownAttackAbilityTask_Base::AttackSucceed(const FMeleeHitInfo& MeleeHitInfo, const FTraceHitInfo& TraceHitInfo)
{
	if (Super::AttackSucceed(MeleeHitInfo, TraceHitInfo) == false) return false;

	return true;
}








UCooldownAttackAbility_Base::UCooldownAttackAbility_Base()
	: Super()
{
	ActivationOwnedTags.AddTagFast(R1Tags::Ability_Action_Attack_Skill); // TEMP 
}

bool UCooldownAttackAbility_Base::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, 
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, 
	const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	if (Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags) == false)
	{
		return false;
	}
	return true;
}

void UCooldownAttackAbility_Base::ActivateAbility(const FGameplayAbilitySpecHandle Handle, 
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, 
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	UCooldownAttackAbilityTask_Base* Task = UAbilityTask::NewAbilityTask<UCooldownAttackAbilityTask_Base>(this);
	Task->ReadyForActivation();
}

void UCooldownAttackAbility_Base::EndAbility(const FGameplayAbilitySpecHandle Handle, 
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, 
	bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
