


#include "AbilitySystem/Abilities/CharacterAbility.h"
#include "Character/R1Character.h"


void UCharacterAbilityTask::Activate()
{
	Super::Activate();
	AbilityTag = Ability->AbilityTags.First();

	AR1Character* R1Character = Cast<AR1Character>(GetAvatarActor());
	if (R1Character)
	{
		R1Character->GAS_OnAbilityCancel.AddDynamic(this, &UCharacterAbilityTask::OnAbilityCancel);
	}
}

void UCharacterAbilityTask::TickTask(float DeltaTime)
{
	Super::TickTask(DeltaTime);
}

void UCharacterAbilityTask::OnDestroy(bool bInOwnerFinished)
{
	Super::OnDestroy(bInOwnerFinished);


	AR1Character* R1Character = Cast<AR1Character>(GetAvatarActor());
	if (R1Character)
	{
		R1Character->GAS_OnAbilityCancel.RemoveDynamic(this, &UCharacterAbilityTask::OnAbilityCancel);
	}
}



void UCharacterAbilityTask::OnAbilityCancel(FAbilityCancelInfo CancelInfo)
{
	AbilityCancel(MoveTemp(CancelInfo));
}

bool UCharacterAbilityTask::AbilityCancel(FAbilityCancelInfo CancelInfo)
{
	if (CancelInfo.Cause == CancelCause::ShutDown)
	{
		CancelAbility();
		return false;
	}
	
	return true;
}

