


#include "Data/R1InputData.h"

const UInputAction* UR1InputData::FindInputActionByTag(const FGameplayTag& InputTag) const
{
	for (const FR1InputAction& Action : InputActions)
	{
		if (Action.InputAction && Action.InputTag == InputTag)
		{
			return Action.InputAction;
		}
	}

	UE_LOG(LogTemp, Error, TEXT("Can't find InputAction for InputTag [%s]."), *InputTag.ToString());

	return nullptr;
}