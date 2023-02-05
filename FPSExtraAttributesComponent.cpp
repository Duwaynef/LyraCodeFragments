// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSExtraAttributesComponent.h"

#include "LyraLogChannels.h"
#include "AbilitySystem/LyraAbilitySystemComponent.h"
#include "FPSExtraAttributes.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"
#include "Messages/LyraVerbMessageHelpers.h"

UFPSExtraAttributesComponent::UFPSExtraAttributesComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryComponentTick.bStartWithTickEnabled = false;
	PrimaryComponentTick.bCanEverTick = false;

	SetIsReplicatedByDefault(true);

	AbilitySystemComponent = nullptr;
	FPSExtraAttributes = nullptr;
}

void UFPSExtraAttributesComponent::InitializeWithAbilitySystem(ULyraAbilitySystemComponent* InASC)
{
	AActor* Owner = GetOwner();
	check(Owner);

	if (AbilitySystemComponent)
	{
		UE_LOG(LogLyra, Error, TEXT("FPSExtraAttributesComponent: component for owner [%s] has already been initialized with an ability system."), *GetNameSafe(Owner));
		return;
	}

	AbilitySystemComponent = InASC;
	if (!AbilitySystemComponent)
	{
		UE_LOG(LogLyra, Error, TEXT("FPSExtraAttributesComponent: Cannot initialize AbilitySystemComponent component for owner [%s] with NULL ability system."), *GetNameSafe(Owner));
		return;
	}

	FPSExtraAttributes = AbilitySystemComponent->GetSet<UFPSExtraAttributes>();
	if (!FPSExtraAttributes)
	{
		UE_LOG(LogLyra, Error, TEXT("FPSExtraAttributesComponent: Cannot initialize FPSExtraAttributes component for owner [%s] with NULL set on the ability system."), *GetNameSafe(Owner));
		return;
	}

	// Register to listen for attribute changes.
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UFPSExtraAttributes::GetArmorAttribute()).AddUObject(this, &ThisClass::HandleArmorChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UFPSExtraAttributes::GetMaxArmorAttribute()).AddUObject(this, &ThisClass::HandleMaxArmorChanged);
  AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UFPSExtraAttributes::GetStaminaAttribute()).AddUObject(this, &ThisClass::HandleStaminaChanged);
  AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UFPSExtraAttributes::GetMaxStaminaAttribute()).AddUObject(this, &ThisClass::HandleMaxStaminaChanged);
  AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UFPSExtraAttributes::GetManaAttribute()).AddUObject(this, &ThisClass::HandleManaChanged);
  AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UFPSExtraAttributes::GetMaxManaAttribute()).AddUObject(this, &ThisClass::HandleMaxManaChanged);
}

void UFPSExtraAttributesComponent::UninitializeFromAbilitySystem()
{
	FPSExtraAttributes = nullptr;
	AbilitySystemComponent = nullptr;
}

void UFPSExtraAttributesComponent::OnUnregister()
{
  UninitializeFromAbilitySystem();
  Super::OnUnregister();
}

float UFPSExtraAttributesComponent::GetArmor() const
{
	return (FPSExtraAttributes ? FPSExtraAttributes->GetArmor() : 0.0f);
}

float UFPSExtraAttributesComponent::GetMaxArmor() const
{
	return (FPSExtraAttributes ? FPSExtraAttributes->GetMaxArmor() : 0.0f);
}

float UFPSExtraAttributesComponent::GetArmorNormalized() const
{
	if (FPSExtraAttributes)
	{
		const float Armor = FPSExtraAttributes->GetArmor();
		const float MaxArmor = FPSExtraAttributes->GetMaxArmor();

		return ((MaxArmor > 0.0f) ? (Armor / MaxArmor) : 0.0f);
	}

	return 0.0f;
}

float UFPSExtraAttributesComponent::GetStamina() const
{
  return (FPSExtraAttributes ? FPSExtraAttributes->GetStamina() : 0.0f);
}

float UFPSExtraAttributesComponent::GetMaxStamina() const
{
  return (FPSExtraAttributes ? FPSExtraAttributes->GetMaxStamina() : 0.0f);
}

float UFPSExtraAttributesComponent::GetStaminaNormalized() const
{
  if (FPSExtraAttributes)
  {
    const float Stamina = FPSExtraAttributes->GetStamina();
    const float MaxStamina = FPSExtraAttributes->GetMaxStamina();

    return ((MaxStamina > 0.0f) ? (Stamina / MaxStamina) : 0.0f);
  }

  return 0.0f;
}

float UFPSExtraAttributesComponent::GetMana() const
{
  return (FPSExtraAttributes ? FPSExtraAttributes->GetMana() : 0.0f);
}

float UFPSExtraAttributesComponent::GetMaxMana() const
{
  return (FPSExtraAttributes ? FPSExtraAttributes->GetMaxMana() : 0.0f);
}

float UFPSExtraAttributesComponent::GetManaNormalized() const
{
  if (FPSExtraAttributes)
  {
    const float Mana = FPSExtraAttributes->GetMana();
    const float MaxMana = FPSExtraAttributes->GetMaxMana();

    return ((MaxMana > 0.0f) ? (Mana / MaxMana) : 0.0f);
  }

  return 0.0f;
}

static AActor* GetInstigatorFromAttrChangeDataFPSExtraAttributes(const FOnAttributeChangeData& ChangeData)
{
	if (ChangeData.GEModData != nullptr)
	{
		const FGameplayEffectContextHandle& EffectContext = ChangeData.GEModData->EffectSpec.GetEffectContext();
		return EffectContext.GetOriginalInstigator();
	}

	return nullptr;
}

void UFPSExtraAttributesComponent::HandleArmorChanged(const FOnAttributeChangeData& ChangeData)
{
	OnArmorChanged.Broadcast(this, ChangeData.OldValue, ChangeData.NewValue, GetInstigatorFromAttrChangeDataFPSExtraAttributes(ChangeData));
}

void UFPSExtraAttributesComponent::HandleMaxArmorChanged(const FOnAttributeChangeData& ChangeData)
{
	OnMaxArmorChanged.Broadcast(this, ChangeData.OldValue, ChangeData.NewValue, GetInstigatorFromAttrChangeDataFPSExtraAttributes(ChangeData));
}

void UFPSExtraAttributesComponent::HandleStaminaChanged(const FOnAttributeChangeData &ChangeData)
{
  OnStaminaChanged.Broadcast(this, ChangeData.OldValue, ChangeData.NewValue, GetInstigatorFromAttrChangeDataFPSExtraAttributes(ChangeData));
}

void UFPSExtraAttributesComponent::HandleMaxStaminaChanged(const FOnAttributeChangeData &ChangeData)
{
  OnMaxStaminaChanged.Broadcast(this, ChangeData.OldValue, ChangeData.NewValue, GetInstigatorFromAttrChangeDataFPSExtraAttributes(ChangeData));
}

void UFPSExtraAttributesComponent::HandleManaChanged(const FOnAttributeChangeData &ChangeData)
{
  OnManaChanged.Broadcast(this, ChangeData.OldValue, ChangeData.NewValue, GetInstigatorFromAttrChangeDataFPSExtraAttributes(ChangeData));
}

void UFPSExtraAttributesComponent::HandleMaxManaChanged(const FOnAttributeChangeData &ChangeData)
{
  OnMaxManaChanged.Broadcast(this, ChangeData.OldValue, ChangeData.NewValue, GetInstigatorFromAttrChangeDataFPSExtraAttributes(ChangeData));
}
