

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "System/R1GameplayTags.h"
#include "AnimNotify_SendGamePlayEvent.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_API UAnimNotify_SendGamePlayEvent : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	UAnimNotify_SendGamePlayEvent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
		const FAnimNotifyEventReference& EventReference) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag GameplayEventTag;
};
