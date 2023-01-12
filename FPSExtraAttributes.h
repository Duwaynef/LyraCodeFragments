// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/Attributes/LyraAttributeSet.h"
#include "FPSExtraAttributes.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
		GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
		GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
		GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
		GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

class UObject;
struct FFrame;

UCLASS()
class FPSROGUELIKERUNTIME_API UFPSExtraAttributes : public ULyraAttributeSet
{
	GENERATED_BODY()

public:

	UFPSExtraAttributes();
	
	ATTRIBUTE_ACCESSORS(UFPSExtraAttributes, HPRegen)	
	ATTRIBUTE_ACCESSORS(UFPSExtraAttributes, ArmorRegen)	
	ATTRIBUTE_ACCESSORS(UFPSExtraAttributes, StaminaRegen)

protected:

	UFUNCTION()
	void OnRep_HPRegen(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_ArmorRegen(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_StaminaRegen(const FGameplayAttributeData& OldValue);

	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;
	
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	void ClampAttribute(const FGameplayAttribute& Attribute, float& NewValue) const;


private:
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_BaseDamage, Category = "FPS|Attributes", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData HPRegen;	

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_BaseDamage, Category = "FPS|Attributes", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData ArmorRegen;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_BaseDamage, Category = "FPS|Attributes", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData StaminaRegen;
	
};
