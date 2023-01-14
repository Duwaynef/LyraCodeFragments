// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "AbilitySystem/Attributes/LyraAttributeSet.h"
#include "Misc/AssertionMacros.h"
#include "UObject/Class.h"
#include "UObject/UObjectGlobals.h"
#include "FPSExtraAttributes.generated.h"

class UObject;
struct FFrame;
struct FGameplayEffectModCallbackData;

UCLASS(BlueprintType)
class LYRAGAME_API UFPSExtraAttributes : public ULyraAttributeSet
{
	GENERATED_BODY()

public:

	UFPSExtraAttributes();

	
	ATTRIBUTE_ACCESSORS(UFPSExtraAttributes, Armor);
	ATTRIBUTE_ACCESSORS(UFPSExtraAttributes, MaxArmor);
	ATTRIBUTE_ACCESSORS(UFPSExtraAttributes, ArmorRegen);
	ATTRIBUTE_ACCESSORS(UFPSExtraAttributes, StaminaRegen);
	ATTRIBUTE_ACCESSORS(UFPSExtraAttributes, ManaRegen);

protected:

	UFUNCTION()
	void OnRep_Armor(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_MaxArmor(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_ArmorRegen(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_ManaRegen(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_StaminaRegen(const FGameplayAttributeData& OldValue);

	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;
	
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	void ClampAttribute(const FGameplayAttribute& Attribute, float& NewValue) const;


private:

	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Armor, Category = "FPS|Attributes", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Armor;
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxArmor, Category = "FPS|Attributes", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxArmor;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ArmorRegen, Category = "FPS|Attributes", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData ArmorRegen;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_StaminaRegen, Category = "FPS|Attributes", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData StaminaRegen;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ManaRegen, Category = "FPS|Attributes", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData ManaRegen;
	
};
