

#pragma once

#include "CoreMinimal.h"
#include "Character/R1Character.h"
#include "System/R1GameplayTags.h"
#include "R1Player.generated.h"

class UPlayerAnimInstance;
class UAnimMontage;


/**
 * 
 */
UCLASS()
class PORTFOLIO_API AR1Player : public AR1Character
{
	GENERATED_BODY()
	
public:
	AR1Player();

protected:
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void InitAbilitySystem() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReasion) override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void HandleGameplayTagEvent(FGameplayTag EventTag) override;

private:
	UFUNCTION() // ※ Require UFUNCTION To Use ( Using Delegate Func )
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	virtual void HandleTraceStarted(UMeleeTraceComponent* ThisComponent, FMeleeTraceInstanceHandle TraceHandle) override;

	virtual void HandleTraceEnded(UMeleeTraceComponent* ThisComponent, int32 HitCount,
		FMeleeTraceInstanceHandle TraceHandle) override;

	virtual void HandleTraceHit(FMeleeHitInfo HitInfo) override;

protected:
	virtual void RefreshHpBarRatio() override;


protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UCameraComponent> Camera;

	UPROPERTY()
	TObjectPtr<UPlayerAnimInstance> PlayerAnim;

	UPROPERTY()
	TObjectPtr<UMeshComponent> PlayerMesh;

	UPROPERTY()
	TObjectPtr<UCharacterMovementComponent> CharMovement;


protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UGameplayEffect> TestEffect;
};
