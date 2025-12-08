

#pragma once

#include "UObject/NoExportTypes.h"
#include "FNameContainer.generated.h"


UCLASS()
class PORTFOLIO_API UFNameContainer : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	FName Name;
};
