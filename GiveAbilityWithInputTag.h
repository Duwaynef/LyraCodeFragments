// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayTagContainer.h"
#include "Components/CapsuleComponent.h"
#include "GiveAbilityActor.generated.h"

class ULyraGameplayAbility;

USTRUCT(BlueprintType)
struct FGiveAbilityActor_GameplayAbility
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

UCLASS()
class FPSROGUELIKERUNTIME_API AGiveAbilityActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGiveAbilityActor();

	// declare overlap begin function
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// declare overlap end function
	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	UPROPERTY(VisibleAnywhere, Category = "Trigger Capsule")
	class UCapsuleComponent* TriggerCapsule;
	
	// Gameplay abilities to grant when this ability set is granted.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay Abilities")
	TArray<FGiveAbilityActor_GameplayAbility> GrantedGameplayAbilities;

	// Gameplay abilities to grant when this ability set is granted.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay Abilities")
	bool bEnableDebugMessages = false;;

};
