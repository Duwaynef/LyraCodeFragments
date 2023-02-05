// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSRogueLike/BlueprintLibrary/MyBlueprintFunctionLibrary.h"
#include "GameModes/LyraGameMode.h"
#include "Components/GameStateComponent.h"
#include "Components/ActorComponent.h"
#include "FPSRogueLike/Gameplay/FPSGameMode.h"
#include "Engine/World.h"
#include "GameModes/LyraExperienceDefinition.h"
#include "Character/LyraPawnExtensionComponent.h"
#include "GameModes/LyraExperienceManagerComponent.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "AIController.h"
#include "Character/LyraPawnExtensionComponent.h"

void UMyBlueprintFunctionLibrary::GiveActorAbilityWithInputTag(AActor* TargetActor,
                                                               UAbilitySystemComponent* AbilitySystemComponent, FMyBlueprintFunctionLibrary_GameplayAbilityStruct AbilityStruct)
{
	check(AbilitySystemComponent);
	
	TArray<FGameplayAbilitySpecHandle> AbilityHandles;
	AbilitySystemComponent->GetAllAbilities(AbilityHandles);

	TArray<FString> AbilityHandleStrings;
	
	if(AbilityHandles.Num() > 0)
	{
		for (int i = 0; i < AbilityHandles.Num(); i++)
		{
			FString AbilityString = AbilitySystemComponent->FindAbilitySpecFromHandle(AbilityHandles[i])->Ability->GetName();
			AbilityHandleStrings.Add(AbilityString);
		}
	}
	
	if (!AbilitySystemComponent->IsOwnerActorAuthoritative())
	{
		// Must be authoritative to give or take ability sets.
		return;
	}	
		
	if (!AbilityStruct.bAllowStacking && AbilityHandleStrings.Contains("Default__" + AbilityStruct.Ability->GetName()))
	{
		return;
	}

	if (!IsValid(AbilityStruct.Ability))
	{
		return;
	}

	ULyraGameplayAbility* AbilityCDO = AbilityStruct.Ability->GetDefaultObject<ULyraGameplayAbility>();

	FGameplayAbilitySpec AbilitySpec(AbilityCDO, AbilityStruct.AbilityLevel);
	AbilitySpec.SourceObject = TargetActor;
	AbilitySpec.DynamicAbilityTags.AddTag(AbilityStruct.InputTag);

	AbilitySystemComponent->GiveAbility(AbilitySpec);
	
}

void UMyBlueprintFunctionLibrary::SpawnEnemy(UGameStateComponent* GameStateComponent,  AFPSGameMode* GameMode, TSubclassOf<AAIController> BotControllerClass)
{
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
	SpawnInfo.OverrideLevel = GameStateComponent->GetComponentLevel();
	SpawnInfo.ObjectFlags |= RF_Transient;
	AAIController* NewController = GameStateComponent->GetWorld()->SpawnActor<AAIController>(BotControllerClass,
		FVector::ZeroVector, FRotator::ZeroRotator, SpawnInfo);

	if (NewController != nullptr)
	{
		check(GameMode);
		if (NewController->PlayerState != nullptr)
		{
			const int32 RandomBotNumber = FMath::RandRange(10000, 99999);
			const FString BotName = FString::Printf(TEXT("Enemy %d"), RandomBotNumber);
			NewController->PlayerState->SetPlayerName(BotName);
		}

		GameMode->DispatchPostLogin(NewController);
		GameMode->RestartPlayer(NewController);

		if (NewController->GetPawn() != nullptr)
		{
			if (ULyraPawnExtensionComponent* PawnExtComponent = NewController->GetPawn()->FindComponentByClass<ULyraPawnExtensionComponent>())
			{
				PawnExtComponent->CheckDefaultInitialization();
			}
		}
	}
}
