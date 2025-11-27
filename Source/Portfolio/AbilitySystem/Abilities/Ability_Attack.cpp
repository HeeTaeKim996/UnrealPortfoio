


#include "AbilitySystem/Abilities/Ability_Attack.h"
#include "Player/R1PlayerController.h"
#include "Character/R1Player.h"
#include "System/R1GameplayTags.h"

UAbility_Attack::UAbility_Attack(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	AbilityTags.AddTag(R1Tags::Ability_Attack_Test);
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

	// Do Something
	AR1PlayerController* PlayerController = Cast<AR1PlayerController>(GetWorld()->GetFirstPlayerController());
	if (PlayerController == nullptr) return;
	FVector CursorPos = PlayerController->GetCursorPos();

	AActor* Owner = ActorInfo->AvatarActor.Get();
	if (Owner == nullptr) return;

	AR1Player* PlayerCh = Cast<AR1Player>(Owner);
	if (PlayerCh == nullptr) return;

	FVector Dir = CursorPos - PlayerCh->GetActorLocation();
	Dir.Z = 0;
	Dir.Normalize();
	PlayerCh->SetDesiredVec(Dir);

	if (AttackMontage == nullptr) return;
	PlayerCh->PlayAnimMontage(AttackMontage);

	PlayerCh->SetCreatureState(ECreatureState::Acting);
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

