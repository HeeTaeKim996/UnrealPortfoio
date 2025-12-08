


#include "Character/R1Monster.h"
#include "Character/R1Player.h"
#include "AbilitySystem/ASC/MonsterASC.h"
#include "AbilitySystem/Attributes/R1AttributeSet.h"

AR1Monster::AR1Monster()
	: Super()
{
	GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -88.f), FRotator(0, -90, 0));

	MeleeTrace->SetTraceChannel(ECC_GameTraceChannel14);

	CharacterASC = CreateDefaultSubobject<UMonsterASC>("AbilitySystemComponent");
	CharacterASC->SetIsReplicated(false); // Singple Play
	CharacterASC->SetReplicationMode(EGameplayEffectReplicationMode::Full); // SinglePlay

	AttributeSet = CreateDefaultSubobject<UR1AttributeSet>("MonsterSet");
}
	

void AR1Monster::BeginPlay()
{
	Super::BeginPlay();


	InitAbilitySystem();
}

void AR1Monster::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AR1Monster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

#if 0
	{
		FGameplayTagContainer TempTags;
		CharacterASC->GetOwnedGameplayTags(TempTags);

		for (FGameplayTag Tag : TempTags)
		{
			DebugMessage(Tag.ToString());
		}

		DebugMessage(TEXT(" "));
	}
#endif
}

void AR1Monster::Highlight()
{
	Super::Highlight();

	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(250);
}

void AR1Monster::UnHighlight()
{
	Super::UnHighlight();
	
	GetMesh()->SetRenderCustomDepth(false);
}

UAbilitySystemComponent* AR1Monster::GetAbilitySystemComponent() const
{
	return Super::GetAbilitySystemComponent();
}

void AR1Monster::InitAbilitySystem()
{
	Super::InitAbilitySystem();

	CharacterASC->InitAbilityActorInfo(this, this);
}

void AR1Monster::HandleTraceHit(FMeleeHitInfo HitInfo)
{
	Super::HandleTraceHit(HitInfo);

	double HitTime = HitInfo.HitTime;

	AActor* HitActor = HitInfo.HitResult.GetActor();
	if (AR1Player* R1Player = Cast<AR1Player>(HitActor))
	{
		const TArray<FDeflectInfo>& DeflectInfos = R1Player->GetDeflectInfos();
		for (int i = DeflectInfos.Num() - 1; i >= 0; i--)
		{
			const FDeflectInfo& DeflectInfo = DeflectInfos[i];
			if (HitTime >= DeflectInfo.Start)
			{
				if (HitTime < DeflectInfo.End || DeflectInfo.End == -1)
				{
					FVector PlayerForward = R1Player->GetDesiredVec();
					PlayerForward.Z = 0;
					PlayerForward.Normalize();

					FVector PlayerToMonster = GetActorLocation() - R1Player->GetActorLocation();
					PlayerToMonster.Z = 0;
					PlayerToMonster.Normalize();

					float Dot = PlayerForward.Dot(PlayerToMonster);


					if (Dot > BLOCK_SUCCEED_COS)
					{
						if (HitTime < DeflectInfo.Start + DeflectInfo.ParrySuccedableTime)
						{
							DebugMessage(TEXT("R1Monster : Parry Succeed"));
						}
						else
						{
							DebugMessage(TEXT("R1Monster : Just Block Succeed"));
						}

						return;
					}

					break;
				}


			}

			if (DeflectInfo.End < HitTime) break;
		}

		DebugMessage(TEXT("R1Monster : Player Hit"));
		GAS_OnAttackSucceed.Broadcast(HitInfo);
		return;
	}
	if (AR1Monster* R1Monster = Cast<AR1Monster>(HitActor))
	{
		// TODO : Address Other Character Hit (Not Player)
	}
	

	

	
}

