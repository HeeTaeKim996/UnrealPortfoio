


#include "Character/R1Monster.h"
#include "Character/R1Player.h"
#include "AbilitySystem/R1AbilitySystemComponent.h"
#include "AbilitySystem/Attributes/R1MonsterSet.h"

AR1Monster::AR1Monster()
	: Super()
{
	GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -88.f), FRotator(0, -90, 0));

	MeleeTrace->SetTraceChannel(ECC_GameTraceChannel14);

	AbilitySystemComponent = CreateDefaultSubobject<UR1AbilitySystemComponent>("AbilitySystemComponent");
	AttributeSet = CreateDefaultSubobject<UR1MonsterSet>("MonsterSet");
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

	AbilitySystemComponent->InitAbilityActorInfo(this, this);
}

