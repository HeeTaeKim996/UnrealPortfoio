


#include "AbilitySystem/Attributes/R1AttributeSet.h"
#include "GameplayEffectExtension.h"
#include "System/R1GameplayTags.h"

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
		
	}
}
