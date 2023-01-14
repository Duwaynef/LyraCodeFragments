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
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UFPSExtraAttributes::GetHPRegenAttribute()).AddUObject(this, &ThisClass::HandleHPRegenChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UFPSExtraAttributes::GetArmorRegenAttribute()).AddUObject(this, &ThisClass::HandleArmorRegenChanged);	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UFPSExtraAttributes::GetStaminaRegenAttribute()).AddUObject(this, &ThisClass::HandleStaminaRegenChanged);
	
}

void UFPSExtraAttributesComponent::UninitializeFromAbilitySystem()
{
	FPSExtraAttributes = nullptr;
	AbilitySystemComponent = nullptr;
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

float UFPSExtraAttributesComponent::GetHPRegen() const
{
	return (FPSExtraAttributes ? FPSExtraAttributes->GetHPRegen() : 0.0f);
}

float UFPSExtraAttributesComponent::GetArmorRegen() const
{
	return (FPSExtraAttributes ? FPSExtraAttributes->GetArmorRegen() : 0.0f);
}

float UFPSExtraAttributesComponent::GetStaminaRegen() const
{
	return (FPSExtraAttributes ? FPSExtraAttributes->GetStaminaRegen() : 0.0f);
}

float UFPSExtraAttributesComponent::GetManaRegen() const
{
	return (FPSExtraAttributes ? FPSExtraAttributes->GetManaRegen() : 0.0f);
}

void UFPSExtraAttributesComponent::OnUnregister()
{
	UninitializeFromAbilitySystem();
	Super::OnUnregister();
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

void UFPSExtraAttributesComponent::HandleHPRegenChanged(const FOnAttributeChangeData& ChangeData)
{
	OnHPRegenChanged.Broadcast(this, ChangeData.OldValue, ChangeData.NewValue, GetInstigatorFromAttrChangeDataFPSExtraAttributes(ChangeData));
}

void UFPSExtraAttributesComponent::HandleArmorRegenChanged(const FOnAttributeChangeData& ChangeData)
{
	OnArmorRegenChanged.Broadcast(this, ChangeData.OldValue, ChangeData.NewValue, GetInstigatorFromAttrChangeDataFPSExtraAttributes(ChangeData));
}

void UFPSExtraAttributesComponent::HandleStaminaRegenChanged(const FOnAttributeChangeData& ChangeData)
{
	OnStaminaRegenChanged.Broadcast(this, ChangeData.OldValue, ChangeData.NewValue, GetInstigatorFromAttrChangeDataFPSExtraAttributes(ChangeData));
}

void UFPSExtraAttributesComponent::HandleManaRegenChanged(const FOnAttributeChangeData& ChangeData)
{
	OnManaRegenChanged.Broadcast(this, ChangeData.OldValue, ChangeData.NewValue, GetInstigatorFromAttrChangeDataFPSExtraAttributes(ChangeData));
}
