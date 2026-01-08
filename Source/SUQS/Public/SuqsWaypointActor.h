#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SuqsWaypointActor.generated.h"

class UWidgetComponent;
class USuqsWaypointComponent;




UCLASS(Abstract, Blueprintable, ClassGroup = (SUQS))
class SUQS_API ASuqsWaypointActorBase : public AActor
{
	GENERATED_BODY()
public:
	ASuqsWaypointActorBase();

protected:
	virtual void BeginPlay() override;

protected:
	UFUNCTION()
	virtual void OnWaypointVisibilityPotentiallyChanged(USuqsWaypointComponent* Waypoint);
	virtual void UpdateWaypointVisibility() const;

	UFUNCTION(BlueprintNativeEvent) // ※ BlueprintNativeEvent : if Function is assigned in BP, use that. otherwise, use below's _Implementation (cpp) function
	void UpdateWaypointWidget(bool bVisible) const;

	virtual void UpdateWaypointWidget_Implementation(bool bVisible) const {}

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, SaveGame)
	USuqsWaypointComponent* WaypointComponent;
};


UCLASS(Blueprintable, ClassGroup = (SUQS))
class SUQS_API ASuqsWaypointActor : public ASuqsWaypointActorBase
{
	GENERATED_BODY()
public:
	ASuqsWaypointActor();

protected:
	virtual void UpdateWaypointWidget_Implementation(bool bVisible) const override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UWidgetComponent* VisualWidget;
};








































































/*
#if 0
//*
// * Base class for waypoint actors which have a waypoint component, you can subclass this to add custom widgets or other functionality.
// * In multiplayer, waypoint components are only linked to the quest on the server. Only movement is
// * replicated.
// 
UCLASS(Abstract, Blueprintable, ClassGroup=(SUQS))
class SUQS_API ASuqsWaypointActorBase : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, SaveGame)
	USuqsWaypointComponent* WaypointComponent;

public:
	ASuqsWaypointActorBase();

protected:
	UFUNCTION()
	virtual void OnWaypointVisibilityPotentiallyChanged(USuqsWaypointComponent* Waypoint);
	virtual void BeginPlay() override;
	virtual void UpdateWaypointVisibility() const;

	UFUNCTION(BlueprintNativeEvent)
	void UpdateWaypointWidget(bool bVisible) const;

	virtual void UpdateWaypointWidget_Implementation(bool bVisible) const
	{
	}
};

/// Waypoint actor which brings together the waypoint component and a UMG visual
/// NOTE: if using a save/load system like SPUD you'll need a subclass with a post-restore hook to call UpdateWaypointVisibility()
UCLASS(Blueprintable, ClassGroup=(SUQS))
class SUQS_API ASuqsWaypointActor : public ASuqsWaypointActorBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UWidgetComponent* VisualWidget;

public:
	ASuqsWaypointActor();

protected:
	virtual void UpdateWaypointWidget_Implementation(bool bVisible) const override;
};
#endif
*/