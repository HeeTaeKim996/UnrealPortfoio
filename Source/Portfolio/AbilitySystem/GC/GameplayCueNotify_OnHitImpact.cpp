


#include "AbilitySystem/GC/GameplayCueNotify_OnHitImpact.h"
#include "System/R1GameplayTags.h"
#include "Character/R1Character.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"

UGameplayCueNotify_OnHitImpact::UGameplayCueNotify_OnHitImpact()
{
	GameplayCueTag = R1Tags::GameplayCue_HitReact_HitImpact;
}

void UGameplayCueNotify_OnHitImpact::HandleGameplayCue(AActor* Target, EGameplayCueEvent::Type EventType, 
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
