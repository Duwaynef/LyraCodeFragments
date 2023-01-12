// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/FPSExtraAttributes.h"
#include "Containers/Array.h"
#include "Net/UnrealNetwork.h"
#include "UObject/CoreNetTypes.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(FPSExtraAttributes)

class FLifetimeProperty;

UFPSExtraAttributes::UFPSExtraAttributes()
	: HPRegen(0.0f)
	, ArmorRegen(0.0f)
	, StaminaRegen(0.0f)
{
}

void UFPSExtraAttributes::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UFPSExtraAttributes, HPRegen, COND_OwnerOnly, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UFPSExtraAttributes, ArmorRegen, COND_OwnerOnly, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UFPSExtraAttributes, StaminaRegen, COND_OwnerOnly, REPNOTIFY_Always);
}

void UFPSExtraAttributes::OnRep_HPRegen(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFPSExtraAttributes, HPRegen, OldValue);
}

void UFPSExtraAttributes::OnRep_ArmorRegen(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFPSExtraAttributes, ArmorRegen, OldValue);
}

void UFPSExtraAttributes::OnRep_StaminaRegen(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFPSExtraAttributes, StaminaRegen, OldValue);
}

void UFPSExtraAttributes::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
	Super::PreAttributeBaseChange(Attribute, NewValue);
}

void UFPSExtraAttributes::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
}

void UFPSExtraAttributes::ClampAttribute(const FGameplayAttribute& Attribute, float& NewValue) const
{
	if (Attribute == GetHPRegenAttribute())
	{
		// Do not allow HP regen to go negative or above max.
		NewValue = FMath::Clamp(NewValue, 0.0f, 1000.0f);
	}
	else if (Attribute == GetArmorRegenAttribute())
	{
		// Do not allow Armor regen to go negative or above max.
		NewValue = FMath::Clamp(NewValue, 0.0f, 1000.0f);
	}
	else if (Attribute == GetStaminaRegenAttribute())
	{
		// Do not allow Armor regen to go negative or above max.
		NewValue = FMath::Clamp(NewValue, 0.0f, 1000.0f);
	}
}
