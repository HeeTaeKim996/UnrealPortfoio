

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AN_Footstep.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_API UAN_Footstep : public UAnimNotify
{
	GENERATED_BODY()
public:
	UAN_Footstep();

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
		const FAnimNotifyEventReference& EventReference) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsRightPlam;
};
