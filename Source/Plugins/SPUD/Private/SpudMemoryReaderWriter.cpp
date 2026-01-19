#include "SpudMemoryReaderWriter.h"
#include "UObject/Object.h"


FArchive& FSpudMemoryWriter::operator<<(UObject*& Obj)
{
	// Save only Path. not entire Data
	FString SavedString(Obj->GetPathName()); // EX) /Game/Maps/MainMap.MainMap:PersistentLevel.MyActor_12.StaticMeshComponent0
	*this << SavedString;
	return *this;
}

FArchive& FSpudMemoryReader::operator<<(UObject*& Obj)
{
	FString LoadedString;
	*this << LoadedString;
	Obj = FindObject<UObject>(nullptr, *LoadedString, false);
	if (Obj == nullptr)
	{
		Obj = LoadObject<UObject>(nullptr, *LoadedString);
	}

	return *this;
}
















































































































/*
#if 0
FArchive& FSpudMemoryWriter::operator<<(UObject*& Obj)
{
	// save out the fully qualified object name
	FString SavedString(Obj->GetPathName());
	*this << SavedString;
	return *this;

}

FArchive& FSpudMemoryReader::operator<<(UObject*& Obj)
{
	// load the path name to the object
	FString LoadedString;
	*this << LoadedString;
	// look up the object by fully qualified pathname
	Obj = FindObject<UObject>(nullptr, *LoadedString, false);
	// If we couldn't find it, and we want to load it, do that
	if (!Obj)
	{
		Obj = LoadObject<UObject>(nullptr, *LoadedString);
	}
	return *this;
}
#endif
*/