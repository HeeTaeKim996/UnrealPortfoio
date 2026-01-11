

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "QuestActorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SUQS_API UQuestActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UQuestActorComponent();

protected:
	virtual void BeginPlay() override;

public:
	bool IsQuesetComponentActive();

	const FName& GetQuestID() const { return QuestID; }
	const FName& GetTaskID() const { return TaskID; }
	const uint8 GetSequenceIndex() const { return SequenceIndex; }


	void SetIsCurrent(bool bNeewIsCurrent);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	FName QuestID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	FName TaskID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	uint8 SequenceIndex = 0;
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	bool bEnabled = true;

protected:
	UPROPERTY()
	bool bIsCurrent = false;
};
