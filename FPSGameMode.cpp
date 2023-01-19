// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSGameMode.h"
#include "Player/LyraPlayerState.h"
#include "System/LyraAssetManager.h"
#include "GameModes/LyraExperienceManagerComponent.h"
#include "GameModes/LyraExperienceDefinition.h"
#include "Character/LyraPawnExtensionComponent.h"
#include "LyraLogChannels.h"

const ULyraPawnData* AFPSGameMode::GetEnemyDataForController(const AController* InController)
{
	// See if pawn data is already set on the player state
	if (InController != nullptr)
	{
		if (const ALyraPlayerState* LyraPS = InController->GetPlayerState<ALyraPlayerState>())
		{
			if (const ULyraPawnData* PawnData = LyraPS->GetPawnData<ULyraPawnData>())
			{
				return PawnData;
			}
		}
	}

	// If not, fall back to the the default for the current experience
	check(GameState);
	ULyraExperienceManagerComponent* ExperienceComponent = GameState->FindComponentByClass<ULyraExperienceManagerComponent>();
	check(ExperienceComponent);

	if (ExperienceComponent->IsExperienceLoaded())
	{
		const ULyraExperienceDefinition* Experience = ExperienceComponent->GetCurrentExperienceChecked();
		if (InController->IsPlayerController())
		{
			if (Experience->DefaultPawnData != nullptr)
			{
				//UE_LOG(LogLyra, Error, TEXT("GetEnemyDataForController on FPSGameMode was called."));
				return Experience->DefaultPawnData;
			}
		}
		else
		{
			if (Experience->DefaultEnemyData != nullptr)
			{
				//UE_LOG(LogLyra, Error, TEXT("GetEnemyDataForController on FPSGameMode was called."));
				return Experience->DefaultEnemyData;
			}
		}


		// Experience is loaded and there's still no pawn data, fall back to the default for now
		return ULyraAssetManager::Get().GetDefaultPawnData();
	}

	// Experience not loaded yet, so there is no pawn data to be had
	return nullptr;
}

APawn* AFPSGameMode::SpawnDefaultPawnAtTransform_Implementation(AController* NewPlayer,
                                                                const FTransform& SpawnTransform)
{
	//UE_LOG(LogLyra, Warning, TEXT("SpawnDefaultPawn on FPSGameMode was called."));
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Instigator = GetInstigator();
	SpawnInfo.ObjectFlags |= RF_Transient;	// Never save the default player pawns into a map.
	SpawnInfo.bDeferConstruction = true;

	if (UClass* PawnClass = GetDefaultPawnClassForController(NewPlayer))
	{
		if (APawn* SpawnedPawn = GetWorld()->SpawnActor<APawn>(PawnClass, SpawnTransform, SpawnInfo))
		{
			if (ULyraPawnExtensionComponent* PawnExtComp = ULyraPawnExtensionComponent::FindPawnExtensionComponent(SpawnedPawn))
			{
				if (const ULyraPawnData* PawnData = GetEnemyDataForController(NewPlayer))
				//if (const ULyraPawnData* PawnData = GetPawnDataForController(NewPlayer))
				{
					//UE_LOG(LogLyra, Warning, TEXT("GetEnemyDataForController on FPSGameMode was called."));
					PawnExtComp->SetPawnData(PawnData);
				}
				else
				{
					UE_LOG(LogLyra, Error, TEXT("Game mode was unable to set PawnData on the spawned pawn [%s]."), *GetNameSafe(SpawnedPawn));
				}
			}

			SpawnedPawn->FinishSpawning(SpawnTransform);

			return SpawnedPawn;
		}
		else
		{
			UE_LOG(LogLyra, Error, TEXT("Game mode was unable to spawn Pawn of class [%s] at [%s]."), *GetNameSafe(PawnClass), *SpawnTransform.ToHumanReadableString());
		}
	}
	else
	{
		UE_LOG(LogLyra, Error, TEXT("Game mode was unable to spawn Pawn due to NULL pawn class."));
	}

	return nullptr;

  // super not needed in this case as we don't want to call the parents implmentation
	//return Super::SpawnDefaultPawnAtTransform_Implementation(NewPlayer, SpawnTransform);
  
}

