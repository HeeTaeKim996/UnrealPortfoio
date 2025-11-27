

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "GameplayTagContainer.h"
#include "AnimNotify_EndAbility.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_API UAnimNotify_EndAbility : public UAnimNotify
{
	GENERATED_BODY()

public:
	UAnimNotify_EndAbility(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
		const FAnimNotifyEventReference& EventReference) override;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWRite)
	FGameplayTag Ability = FGameplayTag::EmptyTag;
};
