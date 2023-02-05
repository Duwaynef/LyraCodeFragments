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
	: Armor(100.0f)
	, MaxArmor(100.0f)
	, Stamina(100.0f)
	, MaxStamina(0.0f)
	, Mana(100.0f)
  , MaxMana(0.0f)
{
}

void UFPSExtraAttributes::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME_CONDITION_NOTIFY(UFPSExtraAttributes, Armor, COND_OwnerOnly, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UFPSExtraAttributes, MaxArmor, COND_OwnerOnly, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UFPSExtraAttributes, Stamina, COND_OwnerOnly, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UFPSExtraAttributes, MaxStamina, COND_OwnerOnly, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UFPSExtraAttributes, Mana, COND_OwnerOnly, REPNOTIFY_Always);
  DOREPLIFETIME_CONDITION_NOTIFY(UFPSExtraAttributes, MaxMana, COND_OwnerOnly, REPNOTIFY_Always);
}

void UFPSExtraAttributes::OnRep_Armor(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFPSExtraAttributes, Armor, OldValue);
}

void UFPSExtraAttributes::OnRep_MaxArmor(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFPSExtraAttributes, MaxArmor, OldValue);
}

void UFPSExtraAttributes::OnRep_Stamina(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFPSExtraAttributes, Stamina, OldValue);
}

void UFPSExtraAttributes::OnRep_MaxStamina(const FGameplayAttributeData &OldValue)
{
  GAMEPLAYATTRIBUTE_REPNOTIFY(UFPSExtraAttributes, MaxStamina, OldValue);
}

void UFPSExtraAttributes::OnRep_Mana(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFPSExtraAttributes, Mana, OldValue);
}

void UFPSExtraAttributes::OnRep_MaxMana(const FGameplayAttributeData &OldValue)
{
  GAMEPLAYATTRIBUTE_REPNOTIFY(UFPSExtraAttributes, MaxMana, OldValue);
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
		// Do not allow attribute to go negative or above max.
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxArmor());
	}
	else if (Attribute == GetMaxArmorAttribute())
	{
		// Do not allow max to drop below 0.
		NewValue = FMath::Max(NewValue, 0.0f);
	}
	else if (Attribute == GetStaminaAttribute())
	{
    // Do not allow attribute to go negative or above max.
    NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxStaminaAttribute());
	}
  else if (Attribute == GetMaxStaminaAttribute())
  {
    // Do not allow max to drop below 0.
    NewValue = FMath::Max(NewValue, 0.0f);
  }
	else if (Attribute == GetManaAttribute())
	{
    // Do not allow attribute to go negative or above max.
    NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxManaAttribute());
	}
  else if (Attribute == GetMaxManaAttribute())
  {
    // Do not allow max to drop below 0.
    NewValue = FMath::Max(NewValue, 0.0f);
  }
}
