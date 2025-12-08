


#include "AbilitySystem/Attributes/R1AttributeSet.h"
#include "GameplayEffectExtension.h"
#include "System/R1GameplayTags.h"
#include "R1Define.h"

UR1AttributeSet::UR1AttributeSet()
{

}

void UR1AttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	const FGameplayAttribute& ModifiedAttr = Data.EvaluatedData.Attribute;
	if (ModifiedAttr == GetHealthAttribute())
	{
		float Magnitude = Data.EvaluatedData.Magnitude;
		if (Magnitude < 0) // Damage
		{

		}

		const FGameplayEffectSpec& Spec = Data.EffectSpec;

		
		DebugMessage(TEXT("R1AttributeSet : OnHealth Check"));
	}
	if (ModifiedAttr == GetImpactedAttribute())
	{
		DebugMessage(TEXT("R1AttributeSet : OnImpacted Check"));
	}


	DebugMessage(TEXT("R1AttributeSet : OnPostGame	playEffectExecute Check"));
}
