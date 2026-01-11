

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "QuestActorSubsystem.generated.h"

class USuqsProgression;
class UQuestActorComponent;

UCLASS()
class SUQS_API UQuestActorSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
protected:
	TMap<FName, TArray<UQuestActorComponent*>> QuestActorComponentsByQuest;
	TWeakObjectPtr<USuqsProgression> Progression;

public:
	void SetProgression(USuqsProgression* InProg);

	void RegisterQuestActorComponent(UQuestActorComponent* QuestActorComponent);
	void UnregisterQuestActorComponent(UQuestActorComponent* QuestActorComponent);

	UQuestActorComponent* GetQuestActorComponent(const FName& QuestID, const FName& TaskID, bool bOnlyEnabled);

	bool GetQuestActorComponents(const FName& QuestID, const FName& TaskID, bool bOnlyEnabled, TArray<UQuestActorComponent*>& OutQuestActorComponents);
};
