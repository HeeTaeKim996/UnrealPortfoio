

#pragma once


UENUM(BlueprintType)
enum class ECreatureState : uint8
{
	None,
	Loco,
	Acting,
	Dead
};


#define DebugMessage(x) if(GEngine){ GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Cyan, x); }