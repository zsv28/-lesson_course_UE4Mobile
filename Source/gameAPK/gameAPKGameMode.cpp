// Copyright Epic Games, Inc. All Rights Reserved.

#include "gameAPKGameMode.h"
#include "gameAPKPawn.h"

AgameAPKGameMode::AgameAPKGameMode()
{
	// set default pawn class to our character class
	DefaultPawnClass = AgameAPKPawn::StaticClass();
}

