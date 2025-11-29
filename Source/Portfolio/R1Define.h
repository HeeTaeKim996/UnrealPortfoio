

#pragma once


#define DebugMessage(x) if(GEngine){ GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Cyan, x); }