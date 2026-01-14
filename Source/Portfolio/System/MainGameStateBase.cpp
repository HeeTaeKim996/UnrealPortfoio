


#include "System/MainGameStateBase.h"
#include "SUQS/Public/SuqsProgression.h"
#include "Serialization/Archive.h"
#include "SUQS/Public/SuqsGameStateComponent.h"

AMainGameStateBase::AMainGameStateBase()
	: Super()
{

	SuqsGameStateComponent = CreateDefaultSubobject<USuqsGameStateComponent>(TEXT("SuqsGameStateComponent"));

}

void AMainGameStateBase::Initialize_SuqsGameStateComponent()
{
	MainProgression = SuqsGameStateComponent->GetServerProgression();

	MainProgression->InitWithQuestDataTables(TempTables);
	

	TArray<uint8> BinaryData;
	FString SaveFilePath = FPaths::Combine(
		FPaths::ProjectSavedDir(),
		TEXT("Save"),
		TEXT("SuqsProgression.sav")
	);

	if (FFileHelper::LoadFileToArray(BinaryData, *SaveFilePath) == false) return;

	FMemoryReader Ar(BinaryData, true);
	
	MainProgression->Serialize(Ar);

}


void AMainGameStateBase::TempSaveSuqsData()
{
	TArray<uint8> BinaryData;

	FMemoryWriter Ar(BinaryData, true);

	MainProgression->Serialize(Ar);
	
	FString SaveFilePath = FPaths::Combine(
		FPaths::ProjectSavedDir(),
		TEXT("Save"),
		TEXT("SuqsProgression.sav")
	);
	FFileHelper::SaveArrayToFile(BinaryData, *SaveFilePath);
}

USuqsGameStateComponent* AMainGameStateBase::GetSuqsGameStateComponent()
{
	return SuqsGameStateComponent;
}
