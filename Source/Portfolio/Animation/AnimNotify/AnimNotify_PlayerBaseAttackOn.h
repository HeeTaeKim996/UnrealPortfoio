

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "System/R1GameplayTags.h"
#include "AnimNotify_PlayerBaseAttackOn.generated.h"


UCLASS()
class PORTFOLIO_API UAnimNotify_PlayerBaseAttackOn : public UAnimNotify
{
	GENERATED_BODY()
public:
	UAnimNotify_PlayerBaseAttackOn();
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
		const FAnimNotifyEventReference& EventReference) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag AbilityTag;
};
