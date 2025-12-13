


#include "AbilitySystem/ASC/PlayerASC.h"
#include "System/R1AssetManager.h"
#include "Data/GE/Data_InitializeGEs.h"



UPlayerASC::UPlayerASC()
	: Super()
{

}

void UPlayerASC::BeginPlay()
{
	Super::BeginPlay();

	LastComboTime = GetWorld()->TimeSeconds; // Dummy Data

	// TODO : Assign GE_PlayerStamina From AssetManager
	UData_InitializeGEs* InitializeGes =
		UR1AssetManager::GetAssetByName<UData_InitializeGEs>(R1Tags::Asset_GE_Initializer_GEs);


	GE_PlayerStamina = InitializeGes->FindGEByTag(R1Tags::Asset_GE_Initializer_PlayerStamina);
	ensureAlwaysMsgf(GE_PlayerStamina, TEXT("This GE is Not assigned"));

	GE_NoPlayerStaminable = InitializeGes->FindGEByTag(R1Tags::Asset_GE_Initializer_NoPlayerStaminable);
	ensureAlwaysMsgf(GE_NoPlayerStaminable, TEXT("This GE is Not assigned"));

	if (GE_PlayerStamina)
	{
		FGameplayEffectContextHandle EffectContext = MakeEffectContext();
		FGameplayEffectSpecHandle SpecHandle = MakeOutgoingSpec(GE_PlayerStamina, 1, EffectContext);
		FGameplayEffectSpec* Spec = SpecHandle.Data.Get();
		Spec->SetSetByCallerMagnitude(R1Tags::Data_SetByCaller_StaminaRegen, 0.15);
		ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
	}
}

FGameplayAbilitySpecHandle UPlayerASC::ActivateAbility(FGameplayTag InTag)
{
	if (InTag.MatchesTag(R1Tags::Ability_Action_Attack_BaseAttack))
	{
		double CurrentTime = GetWorld()->TimeSeconds;
		if (CurrentTime - LastComboTime < 0.3)
		{
			ComboCount++;
		}
		else
		{
			ComboCount = 1;
		}
	}
	else
	{
		ComboCount = 0;
	}

	return Super::ActivateAbility(InTag);
}

void UPlayerASC::ApplyNotPlayerStaminable()
{
	FGameplayEffectContextHandle EffectContext = MakeEffectContext();
	FGameplayEffectSpecHandle SpecHandle = MakeOutgoingSpec(GE_NoPlayerStaminable, 1, EffectContext);
	FGameplayEffectSpec* Spec = SpecHandle.Data.Get();
	ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
}
