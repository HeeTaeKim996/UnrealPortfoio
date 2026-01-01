


#include "System/Subsystem/InventoryManager/Item/R1ItemInstance.h"


UR1ItemInstance::UR1ItemInstance()
	: Super()	
{

}


void UR1ItemInstance::Init(int InItemID)
{
	if (InItemID <= 0) return;

	ItemID = InItemID;
	ItemRarity = EItemRarity::Common;

}