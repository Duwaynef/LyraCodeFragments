// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSTeamCreationComponent.h"
#include "GameFramework/PlayerState.h"
#include "Player/LyraPlayerState.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"

class ALyraPlayerState;
class APlayerController;

void UFPSTeamCreationComponent::ServerChooseTeamForPlayer(ALyraPlayerState* PS)
{
	
	if (PS->IsOnlyASpectator())
	{
		PS->SetGenericTeamId(FGenericTeamId::NoTeam);
	}
	else
	{
		uint32 ID = 2;
		FGenericTeamId TeamID = ID;
		if (PS->IsABot())
		{
			TeamID = ID;
		}
		else
		{
			ID = 1;
			TeamID = ID;
		}
		TeamID = IntegerToGenericTeamId(TeamID);
		PS->SetGenericTeamId(TeamID);
	}
	// Super::ServerChooseTeamForPlayer(PS);
}
