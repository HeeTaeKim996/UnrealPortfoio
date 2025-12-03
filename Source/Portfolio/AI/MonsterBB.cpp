


#include "AI/MonsterBB.h"
#include "Character/R1Character.h"

UMonsterBB::UMonsterBB()
	: Super()
{
#if 0
	BlackboardKey.SelectedKeyName = "TargetCharacter";
	BlackboardKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UMonsterBB, BlackboardKey), AR1Character::StaticClass());
#endif

}
