


#include "Data/GE/Data_InitializeGEs.h"
#include "GameplayEffect.h"

TSubclassOf<UGameplayEffect> UData_InitializeGEs::FindGEByTag(const FGameplayTag& InputTag) const
{
	for (const FInitializeGe& Ge : InitializeGes)
	{
		if (Ge.GE && Ge.InputTag == InputTag)
		{
			return Ge.GE;
		}
	}

	ensureAlwaysMsgf(false, TEXT("Can't Find Matching GE from here"));
	return nullptr;
}
