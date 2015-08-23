// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "FlappyBird.h"
#include "FlappyBirdGameMode.h"
#include "FlappyBirdCharacter.h"

AFlappyBirdGameMode::AFlappyBirdGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// set default pawn class to our character
	DefaultPawnClass = AFlappyBirdCharacter::StaticClass();	
}
