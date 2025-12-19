


#include "AbilitySystem/Attributes/R1AttributeSet.h"
#include "GameplayEffectExtension.h"
#include "System/R1GameplayTags.h"
#include "R1Define.h"
#include "Character/R1Character.h"
#include "AbilitySystem/R1AbilitySystemComponent.h"
#include "System/Subsystem/TagContainersManager.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Structures/FNameContainer.h"

UR1AttributeSet::UR1AttributeSet()
{

}

void UR1AttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	if (Attribute == GetHealthAttribute())
	{
		//NewValue = FMath::Clamp(NewValue, 0, GetMaxHealth());
	}

}

void UR1AttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	const FGameplayAttribute& ModifiedAttr = Data.EvaluatedData.Attribute;
	if (ModifiedAttr == GetMetaDamageAttribute())
	{
		OnDamage(Data);
	}
	else if (ModifiedAttr == GetStaminaAttribute())
	{
		OnStaminaUpdate(Data);
	}

}

void UR1AttributeSet::OnDamage(const FGameplayEffectModCallbackData& Data)
{
	float Damage = Data.EvaluatedData.Magnitude;
	SetMetaDamage(0);

	float Impact = GetMetaImpact();
	SetMetaImpact(0);

	float HealthValue = FMath::Clamp(GetHealth() - Damage, 0, GetMaxHealth());
	SetHealth(HealthValue);

	FGameplayEffectContextHandle ContextHandle = Data.EffectSpec.GetContext();
	const FHitResult* HitResult = ContextHandle.GetHitResult();

	AR1Character* OwnerCharacter = Cast<AR1Character>(Data.Target.GetAvatarActor());
	ensureAlwaysMsgf(OwnerCharacter, TEXT("Owner Character is null"));

	UR1AbilitySystemComponent* ASC = OwnerCharacter->GetR1AbilitySystemComponent();
	ensureAlwaysMsgf(ASC, TEXT("ASC Is null"));

	AR1Character* SourceCharacter = Cast<AR1Character>(ContextHandle.GetInstigator());
	// ※ SoureCharacter can be null
	
	
	FVector ReactDir = HitResult->Location - OwnerCharacter->GetActorLocation();
	ReactDir.Z = 0;
	ReactDir.Normalize();

	FVector DesiredVec = OwnerCharacter->GetDesiredVec();
	DesiredVec.Z = 0;
	DesiredVec.Normalize();

	float Cos = DesiredVec.Dot(ReactDir);
	float Sin = DesiredVec.Cross(ReactDir).Z; // Prelude Two Vectors are span of x,y . not z

#if 0
	DebugMessage(FString::Printf(TEXT("[%f, %f] , [%f, %f], %f, %f"),
		DesiredVec.X, DesiredVec.Y,
		ReactDir.X, ReactDir.Y,
		Cos, Sin));
#endif

	UFNameContainer* FNameContainer = NewObject<UFNameContainer>();

	if (HealthValue == 0)
	{
		if (Cos > COS_45)
		{
			FNameContainer->Name = "Death_Fwd";
		}
		else if (Cos > -COS_45)
		{
			if (Sin > 0)
			{
				FNameContainer->Name = "Death_Right";
			}
			else
			{
				FNameContainer->Name = "Death_Left";
			}
		}
		else
		{
			FNameContainer->Name = "Death_Bwd";
		}

		ASC->CancelAbilities(&UTagContainersManager::Get(this)->OnHitReact_CancelTags(), nullptr, nullptr);

		FGameplayEventData EventData;
		EventData.OptionalObject = FNameContainer;
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(ASC->GetAvatarActor(),
			R1Tags::Ability_Dead, EventData);

	}
	else
	{
		if (Impact < 30)
		{


		}
		else if (Impact < 70)
		{
			if (Cos > COS_45)
			{
				FNameContainer->Name = "Hit_Fwd";
			}
			else if (Cos > -COS_45)
			{
				if (Sin > 0)
				{
					FNameContainer->Name = "Hit_Right";
				}
				else
				{
					FNameContainer->Name = "Hit_Left";
				}
			}
			else
			{
				FNameContainer->Name = "Hit_Bwd";
			}
			ASC->CancelAbilities(&UTagContainersManager::Get(this)->OnHitReact_CancelTags(), nullptr, nullptr);


			FGameplayEventData EventData;
			EventData.OptionalObject = FNameContainer;
			UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(ASC->GetAvatarActor(),
				R1Tags::Ability_Action_HitReact_Base, EventData);
		}
		else
		{
			if (Cos > 0)
			{
				FNameContainer->Name = "KD_Fwd";
				OwnerCharacter->SetDesiredVec(ReactDir);
			}
			else
			{
				FNameContainer->Name = "KD_Fwd";
				OwnerCharacter->SetDesiredVec(ReactDir);
			}
			
			ASC->CancelAbilities(&UTagContainersManager::Get(this)->OnHitReact_CancelTags(), nullptr, nullptr);

			FGameplayEventData EventData;
			EventData.OptionalObject = FNameContainer;
			UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(ASC->GetAvatarActor(),
				R1Tags::Ability_Action_HitReact_Knockdown, EventData);
		}		
	}
}

void UR1AttributeSet::OnStaminaUpdate(const FGameplayEffectModCallbackData& Data)
{
	SetStamina(FMath::Clamp(GetStamina(), 0, GetMaxStamina()));

}
