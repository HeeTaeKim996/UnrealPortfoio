
#include "Player/R1PlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "Kismet/KismetMathLibrary.h"

#include "InputMappingContext.h"

#include "InputAction.h"
#include "System/R1AssetManager.h"
#include "Data/R1InputData.h"
#include "System/R1GameplayTags.h"
#include "Character/R1Player.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "Interface/R1HighlightInterface.h"
#include "Character/R1Monster.h"

#include "UI/MainUserWidget.h"
#include "Data/Data_UserWidget.h"
#include "AbilitySystem/R1AbilitySystemComponent.h"
#include "System/Subsystem/TagContainersManager.h"
#include "Player/R1PlayerState.h"
#include "Structures/PlayerUpperBodyState.h"
#include "Environment/TimeOfDay/TimeOfDay.h"
#include "Kismet/GameplayStatics.h"

AR1PlayerController::AR1PlayerController(const FObjectInitializer& objectInitializer)
	: Super(objectInitializer)
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	CursorPos = FVector::ZeroVector;
	cursorPushedTime = 0.f;


	InputToAbilityMap.Add(R1Tags::Input_Action_BaseAttack,
		R1Tags::Ability_Action_Attack_BaseAttack_TestAttack);
	InputToAbilityMap.Add(R1Tags::Input_Action_Block, R1Tags::Ability_Mode_Blocking);
	InputToAbilityMap.Add(R1Tags::Input_Action_Skill_1, R1Tags::Ability_Action_Attack_Skill_CooldownAttack);
}

void AR1PlayerController::BeginPlay()
{
	Super::BeginPlay();

#if 0 // Obsolate_BlueprintAssign
	UEnhancedInputLocalPlayerSubsystem* Subsystem
		= ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem)
	{
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}
#endif
	if (const UR1InputData* InputData = UR1AssetManager::GetAssetByName<UR1InputData>(R1Tags::Asset_IMC_Base))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem
			= ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputData->InputMappingContext, 0);
		}
	}

	R1Player = Cast<AR1Player>(GetPawn());

	UData_UserWidget* Data_UserWidgets =
		UR1AssetManager::GetAssetByName<UData_UserWidget>(R1Tags::Asset_UserWidget_UserWidgets);

	ensureAlwaysMsgf(Data_UserWidgets, TEXT("Data_UserWidgets is NOT assigend in PDA"));

	TSubclassOf<UUserWidget> MainUIClass = Data_UserWidgets->MainUserWidgetClass;
	// TSubclassOf : Holds Class Type.		TObjectPtr : Holds Class Instance

	if (MainUIClass)
	{
		MainUI = Cast<UMainUserWidget>(CreateWidget<UUserWidget>(this, MainUIClass));
		if (MainUI)
		{
			MainUI->AddToViewport();

		}
	}

	SetInputModeGameOnly(); // Must Invoke After MainUI setted
}

void AR1PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

#if 0 // Obsolate_BlueprintAssign
	auto* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	if (EnhancedInputComponent)
	{
		EnhancedInputComponent->BindAction(TestAction, ETriggerEvent::Triggered, this, &ThisClass::Input_Test);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::Input_Move);
		EnhancedInputComponent->BindAction(TurnAction, ETriggerEvent::Triggered, this, &ThisClass::Input_Turn);
	}
#endif

	if (const UR1InputData* InputData = UR1AssetManager::GetAssetByName<UR1InputData>(R1Tags::Asset_IMC_Base))
	{
		auto* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

		const UInputAction* MoveAction = InputData->FindInputActionByTag(R1Tags::Input_Action_Move);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::Input_Move);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Canceled, this, &ThisClass::OnMoveReleased);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &ThisClass::OnMoveReleased);

		const UInputAction* WheelAction = InputData->FindInputActionByTag(R1Tags::Input_Action_Wheel);
		EnhancedInputComponent->BindAction(WheelAction, ETriggerEvent::Started, this, &ThisClass::OnWheelStarted);
		EnhancedInputComponent->BindAction(WheelAction, ETriggerEvent::Triggered, this, &ThisClass::OnWheelTriggered);
		EnhancedInputComponent->BindAction(WheelAction, ETriggerEvent::Completed, this, &ThisClass::OnWheelReleased);
		EnhancedInputComponent->BindAction(WheelAction, ETriggerEvent::Canceled, this, &ThisClass::OnWheelReleased);

		const UInputAction* BaseAttackAction = InputData->FindInputActionByTag(R1Tags::Input_Action_BaseAttack);
		EnhancedInputComponent->BindAction(BaseAttackAction, ETriggerEvent::Started, this, &ThisClass::OnBaseAttackKeyStarted);
		EnhancedInputComponent->BindAction(BaseAttackAction, ETriggerEvent::Triggered, this, &ThisClass::OnBaseAttackKeyTriggered);
		EnhancedInputComponent->BindAction(BaseAttackAction, ETriggerEvent::Completed, this, &ThisClass::OnBaseAttackKeyReleased);
		EnhancedInputComponent->BindAction(BaseAttackAction, ETriggerEvent::Canceled, this, &ThisClass::OnBaseAttackKeyReleased);

		const UInputAction* BlockAction = InputData->FindInputActionByTag(R1Tags::Input_Action_Block);
		EnhancedInputComponent->BindAction(BlockAction, ETriggerEvent::Started, this, &ThisClass::OnBlockKeyStarted);
		EnhancedInputComponent->BindAction(BlockAction, ETriggerEvent::Triggered, this, &ThisClass::OnBlockKeyTriggered);
		EnhancedInputComponent->BindAction(BlockAction, ETriggerEvent::Completed, this, &ThisClass::OnBlockKeyReleased);
		EnhancedInputComponent->BindAction(BlockAction, ETriggerEvent::Canceled, this, &ThisClass::OnBlockKeyReleased);

		const UInputAction* DodgeAction = InputData->FindInputActionByTag(R1Tags::Input_Action_Dodge);
		EnhancedInputComponent->BindAction(DodgeAction, ETriggerEvent::Started, this, &ThisClass::OnDodgeKeyStarted);
		EnhancedInputComponent->BindAction(DodgeAction, ETriggerEvent::Triggered, this, &ThisClass::OnDodgeKeyTriggered);
		EnhancedInputComponent->BindAction(DodgeAction, ETriggerEvent::Completed, this, &ThisClass::OnDodgeKeyReleased);
		EnhancedInputComponent->BindAction(DodgeAction, ETriggerEvent::Canceled, this, &ThisClass::OnDodgeKeyReleased);

		const UInputAction* ToggleMenuAction = InputData->FindInputActionByTag(R1Tags::Input_ETC_ToggleMenu);
		EnhancedInputComponent->BindAction(ToggleMenuAction, ETriggerEvent::Started, this,
			&ThisClass::OnToggleMenuStarted);
	}
}

void AR1PlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	if (bGameOnlyMode == true)
	{
		TickCursorTrace();
		ChaseTargetAndAttack();
		UpdatePlyaerRotation();
	}
}

void AR1PlayerController::UpdatePlyaerRotation()
{
	if (!R1Player->IsInAnyState(UTagContainersManager::Get(this)->BaseAbilityBlockTgs())
		&& R1Player->GetPlayerMotionState() == EPlayerMotionState::Split_Angle)
	{
		FVector LookDirection = CursorPos - R1Player->GetActorLocation();
		LookDirection.Z = 0;
		LookDirection.Normalize();
		R1Player->SetDesiredVec(LookDirection);
	}

	if (bIsFirstSkillable == false)
	{
		float Remaining;
		float Duration;
		FGameplayTagContainer CooldownTags;
		CooldownTags.AddTagFast(R1Tags::Ability_Cooldown_AssignLocation_First);
		if (GetPlayerState<AR1PlayerState>()->GetCooldownRemainingForTags(CooldownTags, Remaining, Duration) == true)
		{
			MainUI->UpdateFirstSkillCooldownBar(Remaining / Duration);
		}
	}
}

void AR1PlayerController::TickCursorTrace()
{
	if (bWheelPressed) return;

	FHitResult OutCursorHit;
	if (GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, OutCursorHit) == false) return;
	// (1) : == LayerMask, 
	// (2) : True(MeshBaseDetect) -> Precision ↑ Efficientcy ↓ | False(ColliderBaseDetect) -> Precision ↓ Efficiency ↑

	CursorPos = OutCursorHit.Location;

	AActor* LocalHighlightActor = Cast<AActor>(OutCursorHit.GetActor());
	IR1HighlightInterface* LocalHighlight = Cast<IR1HighlightInterface>(LocalHighlightActor);
	if (LocalHighlight == nullptr)
	{
		if (Highlighted)
		{
			Highlighted->UnHighlight();
		}
		Highlighted = nullptr;
	}
	else
	{
		if (Highlighted)
		{
			if (Highlighted != LocalHighlight)
			{
				Highlighted->UnHighlight();
				LocalHighlight->Highlight();
			}
		}
		else
		{
			LocalHighlight->Highlight();
		}

		Highlighted = TScriptInterface<IR1HighlightInterface>(LocalHighlightActor); // Need Actor To Convert TSCriptInterface
	}

}

void AR1PlayerController::ChaseTargetAndAttack()
{
#if 0 // Obsolate
	if (TargetMonster == nullptr) return;

	ECreatureState currState = GetCreatureState();
	if (currState != ECreatureState::Loco) return;

	FVector Direction = TargetMonster->GetActorLocation() - R1Player->GetActorLocation();
	if (Direction.Length() < 250.f)
	{
		if (R1Player->AttackMontage && GetCreatureState() == ECreatureState::Loco)
		{
			FRotator Rotator = UKismetMathLibrary::FindLookAtRotation(R1Player->GetActorLocation(),
				TargetMonster->GetActorLocation());
			R1Player->SetActorRotation(Rotator);

			R1Player->PlayAnimMontage(R1Player->AttackMontage);
			SetCreatureState(ECreatureState::Acting);

			TargetMonster->OnDamage(10, R1Player); // TEMP
		}
	}
	else
	{
		FVector WorldDirection = Direction.GetSafeNormal();
		R1Player->AddMovementInput(WorldDirection, 1.f, false);
		R1Player->SetDesiredVec(WorldDirection);
	}
#endif
}

void AR1PlayerController::Input_Move(const FInputActionValue& InputValue)
{
	if (R1Player->IsInAnyState(UTagContainersManager::Get(this)->BaseAbilityBlockTgs()))
	{
		return;
	}
	bMovePressed = true;


	FVector2D MovementVector = InputValue.Get<FVector2D>();
	MovementVector.Normalize();
	if (R1Player->IsSprint() == false)
	{
		float MulRatio = 0.7f;
		GetPawn()->AddMovementInput(FVector::ForwardVector, MovementVector.X * MulRatio);
		GetPawn()->AddMovementInput(FVector::RightVector, MovementVector.Y * MulRatio);
	}
	else
	{
		GetPawn()->AddMovementInput(FVector::ForwardVector, MovementVector.X);
		GetPawn()->AddMovementInput(FVector::RightVector, MovementVector.Y);
	}

	if (R1Player->GetPlayerMotionState() != EPlayerMotionState::Split_Angle)
	{
		R1Player->SetDesiredVec(FVector(MovementVector.X, MovementVector.Y, 0));
	}




}

void AR1PlayerController::OnMoveReleased(const FInputActionValue& InputValue)
{
	bMovePressed = false;
}


void AR1PlayerController::OnWheelStarted()
{

}
void AR1PlayerController::OnWheelTriggered()
{

}
void AR1PlayerController::OnWheelReleased()
{
	if (bIsFirstSkillable == true)
	{
		R1Player->Input_ActivateAbility(InputToAbilityMap[R1Tags::Input_Action_Skill_1]);
	}
}




void AR1PlayerController::OnBaseAttackKeyStarted()
{
	//GEngine->AddOnScreenDebugMessage(-1, 1.5f, FColor::Cyan, TEXT("LeftMouseStart"));
}

void AR1PlayerController::OnBaseAttackKeyTriggered()
{

}

void AR1PlayerController::OnBaseAttackKeyReleased()
{
	//R1Player->ActivateAbility(R1Tags::Ability_Attack_Test);
	R1Player->Input_ActivateAbility(InputToAbilityMap[R1Tags::Input_Action_BaseAttack]);
}

void AR1PlayerController::OnBlockKeyStarted()
{
	R1Player->Input_Block();
}

void AR1PlayerController::OnBlockKeyTriggered()
{
	R1Player->Input_Block();

	//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Cyan, TEXT("R1PlayerController.cpp : Clicked Check"));
}

void AR1PlayerController::OnBlockKeyReleased()
{
	if (R1Player->IsInState(R1Tags::Ability_Mode_Blocking))
	{
		FGameplayTagContainer TagContainer;
		TagContainer.AddTagFast(R1Tags::Ability_Mode_Blocking);

		R1Player->AbilityCancel(TagContainer);
	}
}

void AR1PlayerController::OnDodgeKeyStarted()
{
	DodgePushedTime = 0.f;
}

void AR1PlayerController::OnDodgeKeyTriggered()
{

	DodgePushedTime += GetWorld()->GetDeltaSeconds();

	if (DodgePushedTime > 0.5f)
	{
		if (R1Player->IsInState(R1Tags::Ability_Mode_Sprint) == false)
		{
			R1Player->Input_ActivateAbility(R1Tags::Ability_Mode_Sprint);
		}
	}
}

void AR1PlayerController::OnDodgeKeyReleased()
{
	if (R1Player->IsInState(R1Tags::Ability_Mode_Sprint) == true)
	{
		FGameplayTagContainer TagContainer;
		TagContainer.AddTagFast(R1Tags::Ability_Mode_Sprint);
		R1Player->AbilityCancel(TagContainer);
	}
}

void AR1PlayerController::OnToggleMenuStarted()
{
	if (bGameOnlyMode == false) return;

	SetInputModeUIOnly();
}

void AR1PlayerController::SetInputModeGameOnly()
{
	FInputModeGameOnly Mode;
	Mode.SetConsumeCaptureMouseDown(false);
	SetInputMode(Mode);

	bGameOnlyMode = true;

	MainUI->CloseMenu();
}

void AR1PlayerController::SetInputModeUIOnly()
{
	FInputModeUIOnly Mode;
	Mode.SetWidgetToFocus(MainUI->TakeWidget());
	SetInputMode(Mode);

	bGameOnlyMode = false;

	MainUI->OpenMenu();
}

void AR1PlayerController::OnFirstSkillTagChanged(const FGameplayTag CallbackTag, int NewCount)
{
	if (NewCount == 0)
	{
		bIsFirstSkillable = true;
	}
	else
	{
		bIsFirstSkillable = false;
	}
}

void AR1PlayerController::TimeOfDay_SetTime(float SetTime)
{
	ATimeOfDay* TimeOfDay = Cast<ATimeOfDay>(UGameplayStatics::GetActorOfClass(GetWorld(), ATimeOfDay::StaticClass()));
	if (TimeOfDay)
	{
		TimeOfDay->SetTime(SetTime);
	}
}

void AR1PlayerController::TimeOfDay_SetDesiredTime(float DesiredTime)
{
	ATimeOfDay* TimeOfDay = Cast<ATimeOfDay>(UGameplayStatics::GetActorOfClass(GetWorld(), ATimeOfDay::StaticClass()));
	if (TimeOfDay)
	{
		TimeOfDay->SetDesiredTime(DesiredTime);
	}
}

