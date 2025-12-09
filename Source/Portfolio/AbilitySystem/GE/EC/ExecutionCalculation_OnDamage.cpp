


#include "AbilitySystem/GE/EC/ExecutionCalculation_OnDamage.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/Attributes/R1AttributeSet.h"
#include "System/R1GameplayTags.h"

UExecutionCalculation_OnDamage::UExecutionCalculation_OnDamage()
{
	/*	- Binding Attribute's ~ to .h's ~Property && Initialize.h's ~Def Initialize 
		- (3) : GE's Invoker(Source) / Target. (4) : bUse Snapshot ( at GE Applying Point. NOT this GEEC Invoke point )
	*/
	DEFINE_ATTRIBUTE_CAPTUREDEF(UR1AttributeSet, AttackPower, Source, true);

	DEFINE_ATTRIBUTE_CAPTUREDEF(UR1AttributeSet, MetaDamage, Target, false);
	DEFINE_ATTRIBUTE_CAPTUREDEF(UR1AttributeSet, MetaImpact, Target, false);

	RelevantAttributesToCapture.Add(AttackPowerDef); // Declare this GEEC Require ~Def
	RelevantAttributesToCapture.Add(MetaDamageDef);
	RelevantAttributesToCapture.Add(MetaImpactDef);
}

void UExecutionCalculation_OnDamage::Execute_Implementation
(const FGameplayEffectCustomExecutionParameters& ExecutionParams, 
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();
	FAggregatorEvaluateParameters EvalParams;
	EvalParams.SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	EvalParams.TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	float AttackPower = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(AttackPowerDef, EvalParams, AttackPower);


	float Impact = 80.f;
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(MetaImpactProperty,
		EGameplayModOp::Override, Impact));


	
	// TODO : Modify Final Damage ?
	const float FinalDamage = AttackPower;



	// ※ PROTOCOL : Setting MetaDamage Must be in Final Sequence
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(MetaDamageProperty, EGameplayModOp::Override,
		FinalDamage));
}
