


#include "AbilitySystem/Abilities/ModeAbility/ModeAbility_Sprint.h"
#include "Character/R1Player.h"
#include "AbilitySystem/ASC/PlayerASC.h"

UModeAbility_Sprint::UModeAbility_Sprint()
	: Super()
{
	AbilityTags.AddTagFast(R1Tags::Ability_Mode_Sprint);
	ActivationOwnedTags.AddTagFast(R1Tags::Ability_Mode_Sprint);
}

void UModeAbility_Sprint::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, 
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	if (AR1Player* R1Player = Cast<AR1Player>(ActorInfo->AvatarActor))
	{
		if (UPlayerASC* PlayerASC = Cast<UPlayerASC>(ActorInfo->AbilitySystemComponent))
		{
			PlayerASC->ApplyNotPlayerStaminable();
		}
	}
}
