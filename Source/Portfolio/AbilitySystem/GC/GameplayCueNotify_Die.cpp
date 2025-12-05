


#include "AbilitySystem/GC/GameplayCueNotify_Die.h"
#include "Character/R1Character.h"
#include "System/R1GameplayTags.h"

UGameplayCueNotify_Die::UGameplayCueNotify_Die()
	: Super()
{

}

void UGameplayCueNotify_Die::HandleGameplayCue(AActor* MyTarget, EGameplayCueEvent::Type EventType, 
	const FGameplayCueParameters& Parameters)
{
	Super::HandleGameplayCue(MyTarget, EventType, Parameters);

	if (EventType != EGameplayCueEvent::Executed || MyTarget == nullptr) return;

	const FHitResult* HitResult = Parameters.EffectContext.GetHitResult();

	AR1Character* OwnerCharacter = Cast<AR1Character>(MyTarget);
	if (OwnerCharacter == nullptr) return;

	OwnerCharacter->Die(HitResult, R1Tags::State_Action_Die_Normal); // TODO : Split Category ?
}
