// Fill out your copyright notice in the Description page of Project Settings.

#include "BlueprintLibrary/MyBlueprintFunctionLibrary.h"

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
