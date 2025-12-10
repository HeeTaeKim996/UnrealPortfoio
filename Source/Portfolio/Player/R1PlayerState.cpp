


#include "Player/R1PlayerState.h"
#include "AbilitySystem/ASC/PlayerASC.h"
#include "AbilitySystem/Attributes/R1AttributeSet.h"

AR1PlayerState::AR1PlayerState(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	ASC = CreateDefaultSubobject<UPlayerASC>("AbilitySystemComponent");
	ASC->SetIsReplicated(false); // Singple Play
	ASC->SetReplicationMode(EGameplayEffectReplicationMode::Full); // SinglePlay

	PlayerSet = CreateDefaultSubobject<UR1AttributeSet>("PlayerSet");
}

UAbilitySystemComponent* AR1PlayerState::GetAbilitySystemComponent() const
{
	return ASC;
}

UR1AbilitySystemComponent* AR1PlayerState::GetR1AbilitySystemComponent() const
{
	return ASC;
}

UR1AttributeSet* AR1PlayerState::GetR1PlayerSet() const
{
	return PlayerSet;
}



bool AR1PlayerState::GetCooldownRemainingForTags(FGameplayTagContainer CooldownTags, float& TimeRemaining,
	float& CooldownDuration)
{
	if (CooldownTags.Num() > 0)
	{
		TimeRemaining = 0.f;
		CooldownDuration = 0.f;

		FGameplayEffectQuery const Query = FGameplayEffectQuery::MakeQuery_MatchAnyOwningTags(CooldownTags);
		TArray<TPair<float, float>> DurationAndTimeRemaining = ASC
			->GetActiveEffectsTimeRemainingAndDuration(Query);
		if (ASC &&  DurationAndTimeRemaining.Num() > 0)
		{
			int BestIdx = 0;
			float LongestTime = DurationAndTimeRemaining[0].Key;
			for (int Idx = 1; Idx < DurationAndTimeRemaining.Num(); Idx++)
			{
				if (DurationAndTimeRemaining[Idx].Key > LongestTime)
				{
					LongestTime = DurationAndTimeRemaining[Idx].Key;
					BestIdx = Idx;
				}
			}

			TimeRemaining = DurationAndTimeRemaining[BestIdx].Key;
			CooldownDuration = DurationAndTimeRemaining[BestIdx].Value;

			return true;
		}
	}

	return false;
}
