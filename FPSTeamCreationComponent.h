// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Teams/LyraTeamCreationComponent.h"
#include "FPSTeamCreationComponent.generated.h"

/**
 * 
 */
UCLASS()
class LYRAGAME_API UFPSTeamCreationComponent : public ULyraTeamCreationComponent
{
	GENERATED_BODY()

#if WITH_SERVER_CODE

protected:
	virtual void ServerChooseTeamForPlayer(ALyraPlayerState* PS) override;

#endif
	
	
};
