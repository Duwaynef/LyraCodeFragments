// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameplayTagContainer.h"
#include "AbilitySystem/LyraAbilitySystemComponent.h"
#include "GameModes/LyraGameMode.h"
#include "Components/GameStateComponent.h"
#include "Character/LyraPawnExtensionComponent.h"
#include "MyBlueprintFunctionLibrary.generated.h"


class ULyraGameplayAbility;
class ULyraPawnData;
class UGameStateComponent;

USTRUCT(BlueprintType)
struct FMyBlueprintFunctionLibrary_GameplayAbilityStruct
{
	GENERATED_BODY()

public:

	// Gameplay ability to grant.
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<ULyraGameplayAbility> Ability = nullptr;

	// Level of ability to grant.
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int32 AbilityLevel = 1;

	// Tag used to process input for the ability.
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Meta = (Categories = "InputTag"))
	FGameplayTag InputTag;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bAllowStacking = false;
	
};

/**
 * 
 */
UCLASS()
class LYRAGAME_API UMyBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category="FPS Blueprint Functions")
	static void GiveActorAbilityWithInputTag(AActor* TargetActor, UAbilitySystemComponent* AbilitySystemComponent,
		FMyBlueprintFunctionLibrary_GameplayAbilityStruct AbilityStruct);

	UFUNCTION(BlueprintCallable, Category="FPS Blueprint Functions")
	static void SpawnEnemy(UGameStateComponent* GameStateComponent, AFPSGameMode* GameMode, TSubclassOf<AAIController> BotControllerClass);	
	
};
