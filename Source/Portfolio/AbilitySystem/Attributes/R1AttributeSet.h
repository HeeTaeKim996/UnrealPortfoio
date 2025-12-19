

#pragma once

#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "R1AttributeSet.generated.h"


struct FGameplayEffectModCallbackData;

// Making Function Macro's Macro
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName)			\
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName)	\
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName)				\
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName)				\
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)				

UCLASS()
class PORTFOLIO_API UR1AttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UR1AttributeSet();



public:
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	


private:
	void OnDamage(const FGameplayEffectModCallbackData& Data);
	void OnStaminaUpdate(const FGameplayEffectModCallbackData& Data);


public:
	ATTRIBUTE_ACCESSORS(ThisClass, Health);
	ATTRIBUTE_ACCESSORS(ThisClass, MaxHealth);
	ATTRIBUTE_ACCESSORS(ThisClass, Stamina);
	ATTRIBUTE_ACCESSORS(ThisClass, MaxStamina);
	ATTRIBUTE_ACCESSORS(ThisClass, AttackPower);
	ATTRIBUTE_ACCESSORS(ThisClass, BaseDefense);
	ATTRIBUTE_ACCESSORS(ThisClass, MetaImpact);
	ATTRIBUTE_ACCESSORS(ThisClass, MetaDamage);

public:
	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData Health;
	
	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData MaxHealth;



	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData Stamina;

	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData MaxStamina;



	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData AttackPower;


	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData BaseDefense;

	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData MetaImpact;

	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData MetaDamage;
};