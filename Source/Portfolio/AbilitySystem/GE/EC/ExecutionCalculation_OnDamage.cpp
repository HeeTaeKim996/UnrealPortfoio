


#include "AbilitySystem/GE/EC/ExecutionCalculation_OnDamage.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/Attributes/R1AttributeSet.h"
#include "System/R1GameplayTags.h"

UExecutionCalculation_OnDamage::UExecutionCalculation_OnDamage()
{
	DEFINE_ATTRIBUTE_CAPTUREDEF(UR1AttributeSet, Health, Target, false); 
	/*	- Binding Attribute's ~ to .h's ~Property && Initialize.h's ~Def Initialize 
		- (3) : GE's Invoker(Source) / Target. (4) : bUse Snapshot ( at GE Applying Point. NOT this GEEC Invoke point )
	*/
	DEFINE_ATTRIBUTE_CAPTUREDEF(UR1AttributeSet, BaseDamage, Source, true);

	RelevantAttributesToCapture.Add(HealthDef); // Declare this GEEC Require ~Def
	RelevantAttributesToCapture.Add(BaseDamageDef);
}

void UExecutionCalculation_OnDamage::Execute_Implementation
(const FGameplayEffectCustomExecutionParameters& ExecutionParams, 
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	FAggregatorEvaluateParameters EvalParams;
	EvalParams.SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	EvalParams.TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	float Health = 0.f;
	float BaseDamage = 0.f;

	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(HealthDef, EvalParams, Health);
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(BaseDamageDef, EvalParams, BaseDamage);


	// TODO : Modify Final Damage ?
	const float FinalDamage = BaseDamage;

	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(HealthProperty, EGameplayModOp::Additive, -FinalDamage));

	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Cyan, TEXT("Execution Check"));
}
