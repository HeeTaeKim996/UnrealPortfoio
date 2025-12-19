

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Anim_Crow.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_API UAnim_Crow : public UAnimInstance
{
	GENERATED_BODY()
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	void SetFly() { bIsFlying = true; }


protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float MoveSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool bIsFlying = false;
};
