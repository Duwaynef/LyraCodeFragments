// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/LyraPawnData.h"
#include "GameModes/LyraGameMode.h"
#include "FPSGameMode.generated.h"

// class AController;
class ULyraPawnData;

/**
 * 
 */
UCLASS()
class LYRAGAME_API AFPSGameMode : public ALyraGameMode
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable, Category = "Lyra|Pawn")
	const ULyraPawnData* GetEnemyDataForController(const AController* InController);
	
	virtual APawn* SpawnDefaultPawnAtTransform_Implementation(AController* NewPlayer, const FTransform& SpawnTransform) override;
  
};
