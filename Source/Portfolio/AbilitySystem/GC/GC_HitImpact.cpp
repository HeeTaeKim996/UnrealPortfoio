


#include "AbilitySystem/GC/GC_HitImpact.h"
#include "System/R1GameplayTags.h"
#include "Character/R1Character.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"

UGC_HitImpact::UGC_HitImpact()
	: Super()
{
	GameplayCueTag = R1Tags::GameplayCue_HitReact_HitImpact;
}

void UGC_HitImpact::HandleGameplayCue(AActor* Target, EGameplayCueEvent::Type EventType, 
	const FGameplayCueParameters& Parameters)
{
	DebugMessage(TEXT("GC_HitImpact : Impact Check"));


	Super::HandleGameplayCue(Target, EventType, Parameters);
	if (EventType != EGameplayCueEvent::Executed || Target == nullptr) return;

	const FHitResult* HItResult = Parameters.EffectContext.GetHitResult();

	AR1Character* OwnerCharacter = Cast<AR1Character>(Target);
	if (OwnerCharacter == nullptr) return;

	UNiagaraSystem* HitFx = OwnerCharacter->GetHitFx();
	if (HitFx)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, HitFx, HItResult->Location, 
			HItResult->ImpactNormal.ToOrientationRotator(), FVector(1.f, 1.f, 1.f), true, true, 
			ENCPoolMethod::None, true);
	}
}
