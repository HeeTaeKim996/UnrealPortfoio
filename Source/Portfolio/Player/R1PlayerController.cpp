
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
#include "Data/Data_MainUserWidget.h"
#include "AbilitySystem/R1AbilitySystemComponent.h"
#include "System/Subsystem/TagContainersManager.h"

AR1PlayerController::AR1PlayerController(const FObjectInitializer& objectInitializer)
	: Super(objectInitializer)
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	CursorPos = FVector::ZeroVector;
	cursorPushedTime = 0.f;
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

	UData_MainUserWidget* Data_MainUserWidget =
		UR1AssetManager::GetAssetByName<UData_MainUserWidget>(R1Tags::Asset_UserWidget_MainUserWidget);

	TSubclassOf<UUserWidget> MainUIClass = Data_MainUserWidget->MainUserWidget;
	// TSubclassOf : Holds Class Type.		TObjectPtr : Holds Class Instance

	if (MainUIClass)
	{
		MainUI = Cast<UMainUserWidget>(CreateWidget<UUserWidget>(this, MainUIClass));
		if (MainUI)
		{
			MainUI->AddToViewport();
		}
	}

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

		const UInputAction* Action1 = InputData->FindInputActionByTag(R1Tags::Input_Action_Move);
		EnhancedInputComponent->BindAction(Action1, ETriggerEvent::Triggered, this, &ThisClass::Input_Move);
		EnhancedInputComponent->BindAction(Action1, ETriggerEvent::Canceled, this, &ThisClass::OnMoveReleased);
		EnhancedInputComponent->BindAction(Action1, ETriggerEvent::Completed, this, &ThisClass::OnMoveReleased);

		const UInputAction* WheelAction = InputData->FindInputActionByTag(R1Tags::Input_Action_Wheel);
		EnhancedInputComponent->BindAction(WheelAction, ETriggerEvent::Started, this, &ThisClass::OnWheelStarted);
		EnhancedInputComponent->BindAction(WheelAction, ETriggerEvent::Triggered, this, &ThisClass::OnWheelTriggered);
		EnhancedInputComponent->BindAction(WheelAction, ETriggerEvent::Completed, this, &ThisClass::OnWheelReleased);
		EnhancedInputComponent->BindAction(WheelAction, ETriggerEvent::Canceled, this, &ThisClass::OnWheelReleased);

		const UInputAction* LeftMouseAction = InputData->FindInputActionByTag(R1Tags::Input_Action_BaseAttack);
		EnhancedInputComponent->BindAction(LeftMouseAction, ETriggerEvent::Started, this, &ThisClass::OnLeftMouseStarted);
		EnhancedInputComponent->BindAction(LeftMouseAction, ETriggerEvent::Triggered, this, &ThisClass::OnLeftMouseTriggered);
		EnhancedInputComponent->BindAction(LeftMouseAction, ETriggerEvent::Completed, this, &ThisClass::OnLeftMouseReleased);
		EnhancedInputComponent->BindAction(LeftMouseAction, ETriggerEvent::Canceled, this, &ThisClass::OnLeftMouseReleased);

		const UInputAction* RightMouseAction = InputData->FindInputActionByTag(R1Tags::Input_Action_Block);
		EnhancedInputComponent->BindAction(RightMouseAction, ETriggerEvent::Started, this, &ThisClass::OnRightMouseStarted);
		EnhancedInputComponent->BindAction(RightMouseAction, ETriggerEvent::Triggered, this, &ThisClass::OnRightMouseTriggered);
		EnhancedInputComponent->BindAction(RightMouseAction, ETriggerEvent::Completed, this, &ThisClass::OnRightMouseReleased);
		EnhancedInputComponent->BindAction(RightMouseAction, ETriggerEvent::Canceled, this, &ThisClass::OnRightMouseReleased);
	}
}

void AR1PlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	TickCursorTrace();
	ChaseTargetAndAttack();

	if (!R1Player->IsInAnyState(UTagContainersManager::Get(this)->CantBaseActableTags()) 
		&& R1Player->IsUpperLowerSplit())
	{
		FVector LookDirection = CursorPos - R1Player->GetActorLocation();
		LookDirection.Z = 0;
		LookDirection.Normalize();
		R1Player->SetDesiredVec(LookDirection);
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
	if (R1Player->IsInAnyState(UTagContainersManager::Get(this)->CantBaseActableTags())) return;
	bMovePressed = true;


	FVector2D MovementVector = InputValue.Get<FVector2D>();
	MovementVector.Normalize();
	GetPawn()->AddMovementInput(FVector::ForwardVector, MovementVector.X);
	GetPawn()->AddMovementInput(FVector::RightVector, MovementVector.Y);

	if (R1Player->IsUpperLowerSplit() == false)
	{
		R1Player->SetDesiredVec(FVector(MovementVector.X, MovementVector.Y, 0));
	}

#if 0 // Obsolate
	if (MovementVector.X != 0)
	{
#if 0 // Obsolate
		FVector Direction = FVector::ForwardVector * MovementVector.X;
		GetPawn()->AddActorWorldOffset(Direction * 50.f);
#endif
#if 0 // Obsolate
		FRotator Rotator = GetControlRotation();
		FVector Direction = UKismetMathLibrary::GetForwardVector(FRotator(0, Rotator.Yaw, 0));
		GetPawn()->AddMovementInput(Direction, MovementVector.X);
#endif

	}
	if (MovementVector.Y != 0)
	{
#if 0 // Obsolate
		FVector Direction = FVector::RightVector * MovementVector.Y;
		GetPawn()->AddActorWorldOffset(Direction * 50.f);
#endif
#if 0 // Obsolate
		FRotator Rotator = GetControlRotation();
		FVector Direction = UKismetMathLibrary::GetRightVector(FRotator(0, Rotator.Yaw, 0));
		GetPawn()->AddMovementInput(Direction, MovementVector.Y);
#endif

	}
#endif
}

void AR1PlayerController::OnMoveReleased(const FInputActionValue& InputValue)
{
	bMovePressed = false;
}

#if 0 // Obsolate
void AR1PlayerController::OnWheelStarted()
{
	bWheelPressed = true;

	if (R1Player->IsInAnyState(UTagContainersManager::Get(this)->CantBaseActableTags())) return;

	StopMovement(); // ※ NavigationSystem's Stop Movement
	if (Highlighted)
	{
		TargetMonster = Cast<AR1Monster>(Highlighted->_getUObject());
	}
	else
	{
		TargetMonster = nullptr;
	}
}

void AR1PlayerController::OnWheelTriggered()
{
	if (R1Player->IsInAnyState(UTagContainersManager::Get(this)->CantBaseActableTags())) return;
	if (TargetMonster) return; // ※ Obsolatable



	cursorPushedTime += GetWorld()->GetDeltaSeconds();

	if (R1Player)
	{
		FVector WorldDirection = CursorPos - R1Player->GetActorLocation();
		WorldDirection.Z = 0;
		WorldDirection.Normalize();

		R1Player->AddMovementInput(WorldDirection, 1.f, false);
		// (1) : dir, (2) : magnitude, (3) : if ture => even if (1) * (2) == 0, Make Move
		R1Player->SetDesiredVec(WorldDirection);
	}
}

void AR1PlayerController::OnWheelReleased()
{
	bWheelPressed = false;

	if (R1Player->IsInAnyState(UTagContainersManager::Get(this)->CantBaseActableTags())) return;

	if (cursorPushedTime <= ShortPressThreshold)
	{
		if (TargetMonster == nullptr)
		{
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, CursorPos); // == NavMesh.SetDestination
			// ※ Require NavMeshBoundVolume In Editor's Map

			UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, CursorPos, FRotator::ZeroRotator,
				FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
			// (1) : Where. Mainly this, (2) : SpawnedFX, (3) : T, (4) : R, (5) : S, (6) : bAutoDestroy, (7) : bAutoActive
			// (8) : PoolingSystemFlag, (9) : bPreCullCheck(FromCamera)
		}
	}
	cursorPushedTime = 0.f;
}
#endif


void AR1PlayerController::OnWheelStarted()
{

}
void AR1PlayerController::OnWheelTriggered()
{

}
void AR1PlayerController::OnWheelReleased()
{
	R1Player->Input_Action(R1Tags::Input_Action_Skill_1);
}




void AR1PlayerController::OnLeftMouseStarted()
{
	//GEngine->AddOnScreenDebugMessage(-1, 1.5f, FColor::Cyan, TEXT("LeftMouseStart"));
}

void AR1PlayerController::OnLeftMouseTriggered()
{

}

void AR1PlayerController::OnLeftMouseReleased()
{
	//R1Player->ActivateAbility(R1Tags::Ability_Attack_Test);
	R1Player->Input_Action(R1Tags::Input_Action_BaseAttack);
}

void AR1PlayerController::OnRightMouseStarted()
{
	R1Player->Input_Block();
}

void AR1PlayerController::OnRightMouseTriggered()
{
	R1Player->Input_Block();
}

void AR1PlayerController::OnRightMouseReleased()
{
	FGameplayTagContainer TagContainer;
	TagContainer.AddTagFast(R1Tags::Ability_Mode_Blocking);
	
	R1Player->AbilityCancel(TagContainer);
}

