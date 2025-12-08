


#include "AbilitySystem/GC/GC_HitReaction.h"
#include "Character/R1Character.h"
#include "GameplayCueManager.h"

UGC_HitReaction::UGC_HitReaction()
	: Super()
{
	//GameplayCueTag = R1Tags::GameplayCue_HitReact_HitReaction;
}

void UGC_HitReaction::HandleGameplayCue(AActor* Target, EGameplayCueEvent::Type EventType,
	const FGameplayCueParameters& Parameters)
{
	Super::HandleGameplayCue(Target, EventType, Parameters);
	if (EventType != EGameplayCueEvent::Executed || Target == nullptr) return;


	const FHitResult* HitResult = Parameters.EffectContext.GetHitResult();

	AR1Character* OwnerCharacter = Cast<AR1Character>(Target);
	if (OwnerCharacter == nullptr) return;

	//OwnerCharacter->HitReact(HitResult, R1Tags::Ability_Action_HitReact);

	DebugMessage(TEXT("GC_HitReaction : Check"));

}

