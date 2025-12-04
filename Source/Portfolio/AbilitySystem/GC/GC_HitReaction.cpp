


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


	AR1Character* OwnerCharacter = Cast<AR1Character>(Target);
	if (OwnerCharacter == nullptr) return;

	OwnerCharacter->HitReact(Parameters.EffectContext.GetHitResult(), R1Tags::State_Action_HitReact_Base) ;

}

