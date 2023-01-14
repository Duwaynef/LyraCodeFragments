// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSExtraAttributes.h"
#include "Containers/Array.h"
#include "Net/UnrealNetwork.h"
#include "UObject/CoreNetTypes.h"
#include "LyraGameplayTags.h"
#include "AbilitySystem/LyraAbilitySystemComponent.h"
#include "Engine/World.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(FPSExtraAttributes)

class FLifetimeProperty;

UFPSExtraAttributes::UFPSExtraAttributes()
	: Armor(0.0f)
	, MaxArmor(100.0f)
	, ArmorRegen(0.0f)
	, StaminaRegen(0.0f)
	, ManaRegen(0.0f)
{
}

void UFPSExtraAttributes::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME_CONDITION_NOTIFY(UFPSExtraAttributes, Armor, COND_OwnerOnly, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UFPSExtraAttributes, MaxArmor, COND_OwnerOnly, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UFPSExtraAttributes, ArmorRegen, COND_OwnerOnly, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UFPSExtraAttributes, StaminaRegen, COND_OwnerOnly, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UFPSExtraAttributes, ManaRegen, COND_OwnerOnly, REPNOTIFY_Always);
}

void UFPSExtraAttributes::OnRep_Armor(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFPSExtraAttributes, Armor, OldValue);
}

void UFPSExtraAttributes::OnRep_MaxArmor(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFPSExtraAttributes, MaxArmor, OldValue);
}

void UFPSExtraAttributes::OnRep_ArmorRegen(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFPSExtraAttributes, ArmorRegen, OldValue);
}

void UFPSExtraAttributes::OnRep_ManaRegen(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFPSExtraAttributes, ManaRegen, OldValue);
}

void UFPSExtraAttributes::OnRep_StaminaRegen(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFPSExtraAttributes, StaminaRegen, OldValue);
}

void UFPSExtraAttributes::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
	Super::PreAttributeBaseChange(Attribute, NewValue);
	ClampAttribute(Attribute, NewValue);
}

void UFPSExtraAttributes::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	ClampAttribute(Attribute, NewValue);
}

void UFPSExtraAttributes::ClampAttribute(const FGameplayAttribute& Attribute, float& NewValue) const
{
	if (Attribute == GetArmorAttribute())
	{
		// Do not allow health to go negative or above max health.
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxArmor());
	}
	else if (Attribute == GetMaxArmorAttribute())
	{
		// Do not allow max health to drop below 1.
		NewValue = FMath::Max(NewValue, 1.0f);
	}
	else if (Attribute == GetHPRegenAttribute())
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
