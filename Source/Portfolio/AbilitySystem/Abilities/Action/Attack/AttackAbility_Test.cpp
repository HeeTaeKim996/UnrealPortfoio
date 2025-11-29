


#include "AbilitySystem/Abilities/Action/Attack/AttackAbility_Test.h"
#include "Player/R1PlayerController.h"
#include "Character/R1Player.h"

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


	PlayerCh->AddState(R1Tags::State_Action_Attack); // TEMP
}

void UAttacAbilityTask_Test::TickTask(float DeltaTime)
{
	Super::TickTask(DeltaTime);
}

void UAttacAbilityTask_Test::OnDestroy(bool bInOwnerFinished)
{
	Super::OnDestroy(bInOwnerFinished);
}

void UAttacAbilityTask_Test::OnTraceHit(FMeleeHitInfo MeleeHitInfo)
{
	UR1GameplayAbility* R1Ability = Cast<UR1GameplayAbility>(Ability);
	if (!R1Ability) return;

	if (R1Ability->AbilityTags.HasTag(MeleeHitInfo.Ability) == false) return;

	AActor* HitActor = MeleeHitInfo.HitActor;
	AR1Character* HItCharacter = Cast<AR1Character>(HitActor);
	if (HItCharacter == nullptr) return;

	HItCharacter->OnDamage(20, Cast<AR1Character>(GetAvatarActor()));
}
















UAttackAbility_Test::UAttackAbility_Test(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

	{ // TEMP
		ActivationBlockedTags.AddTag(R1Tags::State_Action_Attack);
		ActivationBlockedTags.AddTag(R1Tags::State_Dead);
	}
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

	AR1Character* R1Character = Cast<AR1Character>(ActorInfo->AvatarActor.Get());
	if (R1Character == nullptr)
	{
		EndAbilityCancel();
		return;
	}

	UAttacAbilityTask_Test* Task = UAbilityTask::NewAbilityTask<UAttacAbilityTask_Test>(this);
	Task->ReadyForActivation();
}

void UAttackAbility_Test::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
