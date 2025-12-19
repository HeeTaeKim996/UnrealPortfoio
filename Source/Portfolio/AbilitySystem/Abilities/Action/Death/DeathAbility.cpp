


#include "AbilitySystem/Abilities/Action/Death/DeathAbility.h"
#include "Structures/FNameContainer.h"
#include "AbilitySystem/R1AbilitySystemComponent.h"
#include "Character/R1Character.h"
#include "System/R1GameplayTags.h"


void UDeathAbilityTask::Activate()
{
	Super::Activate();

	AR1Character* R1Character = Cast<AR1Character>(GetAvatarActor());
	if (R1Character)
	{
		R1Character->Delegate_GAMultiDelegate.AddDynamic(this, &UDeathAbilityTask::OnDeadStop);
	}
	
}

void UDeathAbilityTask::TickTask(float DeltaTime)
{
	Super::TickTask(DeltaTime);
}

void UDeathAbilityTask::OnDestroy(bool bInOwnerFinished)
{
	Super::OnDestroy(bInOwnerFinished);
	AR1Character* R1Character = Cast<AR1Character>(GetAvatarActor());
	if (R1Character)
	{
		R1Character->Delegate_GAMultiDelegate.RemoveDynamic(this, &UDeathAbilityTask::OnDeadStop);
	}
}

void UDeathAbilityTask::OnDeadStop(const FGameplayTag& InTag)
{
	if (InTag != R1Tags::Event_GAS_DeadStop) return;

	if (AR1Character* R1Character = Cast<AR1Character>(GetAvatarActor()))
	{
		if (UAnimInstance* Anim = R1Character->GetMesh()->GetAnimInstance())
		{
			Anim->Montage_Pause(Anim->GetCurrentActiveMontage());
		}
	}

	
}







UDeathAbility::UDeathAbility()
	: Super()
{
	ActivationOwnedTags.AddTagFast(R1Tags::Ability_Dead);

	FAbilityTriggerData TriggerData;
	TriggerData.TriggerSource = EGameplayAbilityTriggerSource::GameplayEvent;
	TriggerData.TriggerTag = R1Tags::Ability_Dead;

	AbilityTriggers.Add(TriggerData);
}

bool UDeathAbility::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, 
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, 
	const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	if (Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags) == false)
	{
		return false;
	}
	return true;
}

void UDeathAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, 
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	InSectionName = Cast<UFNameContainer>(TriggerEventData->OptionalObject)->Name;

	// ※ Before Activate ActionAbility, Set SectionName
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (bUseDeathPause)
	{
		UDeathAbilityTask* Task = UAbilityTask::NewAbilityTask<UDeathAbilityTask>(this);
		Task->ReadyForActivation();

		if (AR1Character* R1Character = Cast<AR1Character>(ActorInfo->AvatarActor))
		{
			if (UAnimInstance* Anim = R1Character->GetMesh()->GetAnimInstance())
			{
				FAnimMontageInstance* Inst = Anim->GetActiveInstanceForMontage(PlayingMontage);
				Inst->bEnableAutoBlendOut = false;
			}
		}
	}
}

void UDeathAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, 
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, 
	bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}



void UDeathAbility::OnMontageEnded(UAnimMontage* Montage, bool bInterruped)
{
	Super::OnMontageEnded(Montage, bInterruped);

	DebugMessage("DeathAbility.cpp : Temp Montage End Check");
	MontageStop();
}

void UDeathAbility::OnMontageBlendingOutStarted(UAnimMontage* AnimMontage, bool bInterrupted)
{
	Super::OnMontageEnded(AnimMontage, bInterrupted);

	UAnimInstance* Anim = GetActorInfo().GetAnimInstance();
	if (Anim)
	{
		Anim->Montage_Pause(AnimMontage);
	}
}
