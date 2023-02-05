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
	ATTRIBUTE_ACCESSORS(UFPSExtraAttributes, Stamina);
	ATTRIBUTE_ACCESSORS(UFPSExtraAttributes, MaxStamina);
  ATTRIBUTE_ACCESSORS(UFPSExtraAttributes, Mana);
  ATTRIBUTE_ACCESSORS(UFPSExtraAttributes, MaxMana);

protected:

	UFUNCTION()
	void OnRep_Armor(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_MaxArmor(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_Stamina(const FGameplayAttributeData& OldValue);

  UFUNCTION()
  void OnRep_MaxStamina(const FGameplayAttributeData &OldValue);

  UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldValue);

	UFUNCTION()
  void OnRep_MaxMana(const FGameplayAttributeData &OldValue);

  virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;
	
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	void ClampAttribute(const FGameplayAttribute& Attribute, float& NewValue) const;


private:

	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Armor, Category = "FPS|Attributes", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Armor;
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxArmor, Category = "FPS|Attributes", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxArmor;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Stamina, Category = "FPS|Attributes", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Stamina;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxStamina, Category = "FPS|Attributes", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxStamina;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mana, Category = "FPS|Attributes", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Mana;

  UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMana, Category = "FPS|Attributes", Meta = (AllowPrivateAccess = true))
  FGameplayAttributeData MaxMana;
};
