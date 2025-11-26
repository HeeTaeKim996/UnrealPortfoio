


#include "AI/Kronos/BTTaskNode_Kronos_Attack.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/R1AIController.h"
#include "Character/FieldMonster/FieldMonster_Kronos.h"
#include "Character/R1Player.h"

UBTTaskNode_Kronos_Attack::UBTTaskNode_Kronos_Attack()
	: Super()
{
	bNotifyTick = true;
	bNotifyTaskFinished = true;
}

EBTNodeResult::Type UBTTaskNode_Kronos_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, 
	uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AFieldMonster_Kronos* Kronos = Cast<AFieldMonster_Kronos>(OwnerComp.GetAIOwner()->GetPawn());

	Kronos->PlayAnimMontage(AttackMontage);
	Kronos->GetMesh()->GetAnimInstance()->OnMontageEnded.AddDynamic(this, 
		&UBTTaskNode_Kronos_Attack::OnMontageEnded);

	bMontageEnded = false;

	return EBTNodeResult::InProgress;
}

void UBTTaskNode_Kronos_Attack::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, 
	EBTNodeResult::Type TaskResult)
{
	Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult);

	AFieldMonster_Kronos* Kronos = Cast<AFieldMonster_Kronos>(OwnerComp.GetAIOwner()->GetPawn());
	Kronos->GetMesh()->GetAnimInstance()->OnMontageEnded.RemoveDynamic(this,
		&UBTTaskNode_Kronos_Attack::OnMontageEnded);
}

void UBTTaskNode_Kronos_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, 
	float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (bMontageEnded)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return;
	}

	AFieldMonster_Kronos* Kronos = Cast<AFieldMonster_Kronos>(OwnerComp.GetAIOwner()->GetPawn());

	AR1Player* PlayerCh = Cast<AR1Player>(OwnerComp.GetBlackboardComponent()
		->GetValueAsObject(TargetPlayer.SelectedKeyName));

	if (PlayerCh)
	{
		FVector AimVec = PlayerCh->GetActorLocation() - Kronos->GetActorLocation();
		AimVec.Z = 0;
		AimVec.Normalize();
		FQuat AimQuat = AimVec.Rotation().Quaternion();

		float Alpha = FMath::Clamp(DeltaSeconds * 8.f, 0.f, 1.f);
		FQuat SlerpQuat = FQuat::Slerp(Kronos->GetActorRotation().Quaternion(), AimQuat, Alpha);
		Kronos->SetActorRotation(SlerpQuat);

	}
}

void UBTTaskNode_Kronos_Attack::OnMontageEnded(UAnimMontage* EndMontage, bool bInterruped)
{
	bMontageEnded = true;
}
