

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/ActionAbility.h"
#include "Components/AudioComponent.h"
#include "Structures/SoundInfo.h"
#include "AttackAbility.generated.h"

struct FMeleeHitInfo;
class UGameplayEffect;
struct FTraceHitInfo;

USTRUCT(BlueprintType)
struct PORTFOLIO_API FAttackInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<UGameplayEffect> GE;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float AttackCoefficient;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float Impact;
};




UCLASS()
class PORTFOLIO_API UAttackAbilityTask : public UActionAbilityTask
{
	GENERATED_BODY()
public:
	virtual void Activate() override;
	virtual void TickTask(float DeltaTime) override;
	virtual void OnDestroy(bool bInOwnerFinished) override;

private:
	UFUNCTION()
	void OnAttackSucceed(const FMeleeHitInfo& MeleeHitInfo, const FTraceHitInfo& TraceHitInfo);
	
	UFUNCTION()
	void OnDelegate_GAMultiDelegate(const FGameplayTag& InTag);

protected:
	virtual bool AttackSucceed(const FMeleeHitInfo& MeleeHitInfo, const FTraceHitInfo& TraceHitInfo);
};



UCLASS()
class PORTFOLIO_API UAttackAbility : public UActionAbility
{
	GENERATED_BODY()
public:
	UAttackAbility();

protected:
	bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr,
		OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<FAttackInfo> AttackInfos;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
	FSoundInfo SoundInfo;

	UPROPERTY()
	TObjectPtr<UAudioComponent> AttackSoundComponent;
};
