


#include "AbilitySystem/Abilities/Action/Attack/AttackAbility_Test.h"
#include "Player/R1PlayerController.h"
#include "Character/R1Player.h"
#include "Structures/TraceHitInfo.h"

#if 1 // Temp
#include "Kismet/GameplayStatics.h"
#endif

void UAttacAbilityTask_Test::Activate()
{
	Super::Activate();

	AR1PlayerController* PlayerController = Cast<AR1PlayerController>(GetWorld()->GetFirstPlayerController());
	if (PlayerController == nullptr) return;
	FVector CursorPos = PlayerController->GetCursorPos();


	AR1Player* PlayerCh = Cast<AR1Player>(GetAvatarActor());
	if (PlayerCh == nullptr) return;

	FVector Dir = CursorPos - PlayerCh->GetActorLocation();
	Dir.Z = 0;
	Dir.Normalize();
	PlayerCh->SetDesiredVec(Dir);
}

void UAttacAbilityTask_Test::TickTask(float DeltaTime)
{
	Super::TickTask(DeltaTime);
}

void UAttacAbilityTask_Test::OnDestroy(bool bInOwnerFinished)
{
	Super::OnDestroy(bInOwnerFinished);
}

bool UAttacAbilityTask_Test::AttackSucceed(const FMeleeHitInfo& MeleeHitInfo, const FTraceHitInfo& TraceHitInfo)
{
	if (Super::AttackSucceed(MeleeHitInfo, TraceHitInfo) == false) return false;

	return true;
}


















UAttackAbility_Test::UAttackAbility_Test()
	: Super()
{

}

bool UAttackAbility_Test::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	if (Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags) == false)
	{
		return false;
	}
	return true;
}

void UAttackAbility_Test::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	UAttacAbilityTask_Test* Task = UAbilityTask::NewAbilityTask<UAttacAbilityTask_Test>(this);
	Task->ReadyForActivation();

}

void UAttackAbility_Test::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
