

#pragma once


#define DebugMessage(x) if(GEngine){ GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Cyan, x); }

#define COS_45 0.70710678f
#define COS_30 0.8660254f

#define PARRY_SUCCEED_TIME 0.2

#define BLOCK_SUCCEED_COS COS_45