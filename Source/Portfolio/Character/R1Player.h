

#pragma once

#include "CoreMinimal.h"
#include "Character/R1Character.h"
#include "System/R1GameplayTags.h"
#include "R1Player.generated.h"

class UPlayerAnimInstance;
class UAnimMontage;

USTRUCT()
struct PORTFOLIO_API FDeflectInfo
{
	GENERATED_BODY()

	double Start;
	double End = -1;
	double ParrySuccedableTime;
};

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
	virtual void RefreshHpBarRatio(float NewHealth) override;

protected:
	virtual void OnTagUpdated(const FGameplayTag& Tag, bool TagExists) override;

public:
	void Input_Action(FGameplayTag InActionState);
	void Input_Block();
	
	void Input_Cancel(FGameplayTagContainer InCancelStates);
	

public:
	bool IsUpperLowerSplit() { return bUpperLowerSplit; }
	const TArray<FDeflectInfo>& GetDeflectInfos() { return DeflectInfos; }


private:
	void OnBlockTagChanged(const FGameplayTag CallbackTag, int NewCount);

protected:
	TArray<FDeflectInfo> DeflectInfos;
	int DeflectMax = 10;


private:
	bool bUpperLowerSplit = false;
	float SurplusAlertTime;

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
