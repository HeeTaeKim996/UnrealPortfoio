


#include "AbilitySystem/Abilities/Ability_Attack.h"
#include "Player/R1PlayerController.h"
#include "Character/R1Player.h"
#include "System/R1GameplayTags.h"
#include "Character/R1Player.h"
#include "Abilities/Tasks/AbilityTask.h"



void UAbilityTask_Attack::Initialize(UR1GameplayAbility* InAbility, AR1Character* InCharacter, 
	UAnimMontage* InMontage)
{
	Super::Initialize(InAbility, InCharacter);

	AttackMontage = InMontage;
}

void UAbilityTask_Attack::Activate()
{
	Super::Activate();

	if (!WeakCharacter.IsValid()) return;

	
	AR1PlayerController* PlayerController = Cast<AR1PlayerController>(GetWorld()->GetFirstPlayerController());
	if (PlayerController == nullptr) return;
	FVector CursorPos = PlayerController->GetCursorPos();

	
	AR1Player* PlayerCh = Cast<AR1Player>(WeakCharacter.Get());
	if (PlayerCh == nullptr) return;

	FVector Dir = CursorPos - PlayerCh->GetActorLocation();
	Dir.Z = 0;
	Dir.Normalize();
	PlayerCh->SetDesiredVec(Dir);

	if (AttackMontage == nullptr) return;
	PlayerCh->PlayAnimMontage(AttackMontage);

	PlayerCh->SetCreatureState(ECreatureState::Acting);
}

void UAbilityTask_Attack::TickTask(float DeltaTime)
{
	Super::TickTask(DeltaTime);
}

void UAbilityTask_Attack::OnDestroy(bool bInOwnerFinished)
{
	Super::OnDestroy(bInOwnerFinished);
}

bool UAbilityTask_Attack::TraceHit(FMeleeHitInfo MeleeHitInfo)
{
	if (Super::TraceHit(MeleeHitInfo) == false) return false;

	if (WeakAbility.IsValid() == false) return false;

	UR1GameplayAbility* R1Ability = WeakAbility.Get();
	if (R1Ability->AbilityTags.HasTag(MeleeHitInfo.Ability) == false) return false;

	AActor* HitActor = MeleeHitInfo.HitActor;
	AR1Character* HItCharacter = Cast<AR1Character>(HitActor);
	if (HItCharacter == nullptr) return false;

	HItCharacter->OnDamage(20, WeakCharacter.Get());

	return true;
}

bool UAbilityTask_Attack::AbilitySuccess(FAbilitySuccessInfo InTag)
{
	if (Super::AbilitySuccess(InTag) == false) return false;

	

	AR1Character* R1Character = WeakCharacter.Get();
	if (R1Character)
	{
		R1Character->ToLoco();
	}

	ClearAbility();

	return true;
}





















UAbility_Attack::UAbility_Attack(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	
}

bool UAbility_Attack::CanActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags,
	const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	if (Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags) == false)
	{
		return false;
	}

	return true;
}

void UAbility_Attack::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	AR1Character* R1Character = Cast<AR1Character>(ActorInfo->AvatarActor.Get());
	if (R1Character == nullptr) return;

	UAbilityTask_Attack* Task = UAbilityTask::NewAbilityTask<UAbilityTask_Attack>(this);
	Task->Initialize(this, R1Character, AttackMontage);
	Task->ReadyForActivation();
	
	
}

void UAbility_Attack::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);


	AActor* Owner = ActorInfo->AvatarActor.Get();
	if (Owner == nullptr) return;

	AR1Player* Player = Cast<AR1Player>(Owner);
	if (Player == nullptr) return;

	if (bWasCancelled)
	{
		
	}
	else
	{
		Player->ToLoco();
	}
}

