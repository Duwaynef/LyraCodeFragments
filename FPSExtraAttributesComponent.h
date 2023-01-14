// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/GameFrameworkComponent.h"
#include "FPSExtraAttributes.h"
#include "FPSExtraAttributesComponent.generated.h"

class UFPSExtraAttributes;
struct FOnAttributeChangeData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FFPSExtraAttributes_AttributeChanged, UFPSExtraAttributesComponent*, UFPSExtraAttributesComponent, float,
											   OldValue, float, NewValue, AActor*, Instigator);

class ULyraAbilitySystemComponent;

UCLASS(Blueprintable, meta=(BlueprintSpawnableComponent))
class LYRAGAME_API UFPSExtraAttributesComponent : public UGameFrameworkComponent
{
	GENERATED_BODY()

public:
	
	UFPSExtraAttributesComponent(const FObjectInitializer& ObjectInitializer);

	// Returns the component if one exists on the specified actor.
	UFUNCTION(BlueprintPure, Category = "FPS|Attributes")
	static UFPSExtraAttributesComponent* FindFPSExtraAttributesComponent(const AActor* Actor)
	{
		return (Actor ? Actor->FindComponentByClass<UFPSExtraAttributesComponent>() : nullptr);
	}

	// Initialize the component using an ability system component.
	UFUNCTION(BlueprintCallable, Category = "FPS|Attributes")
	void InitializeWithAbilitySystem(ULyraAbilitySystemComponent* InASC);

	// Uninitialize the component, clearing any references to the ability system.
	UFUNCTION(BlueprintCallable, Category = "FPS|Attributes")
	void UninitializeFromAbilitySystem();

	// Returns the current Armor value.
	UFUNCTION(BlueprintCallable, Category = "FPS|Attributes")
	float GetArmor() const;

	// Returns the current maximum Armor value.
	UFUNCTION(BlueprintCallable, Category = "FPS|Attributes")
	float GetMaxArmor() const;

	// Returns the current Armor in the range [0.0, 1.0].
	UFUNCTION(BlueprintCallable, Category = "FPS|Attributes")
	float GetArmorNormalized() const;

	// Returns the current value.
	UFUNCTION(BlueprintCallable, Category = "FPS|Attributes")
	float GetHPRegen() const;

	// Returns the current  value.
	UFUNCTION(BlueprintCallable, Category = "FPS|Attributes")
	float GetArmorRegen() const;

	UFUNCTION(BlueprintCallable, Category = "FPS|Attributes")
	float GetStaminaRegen() const;

	UFUNCTION(BlueprintCallable, Category = "FPS|Attributes")
	float GetManaRegen() const;
	
	UPROPERTY(BlueprintAssignable)
	FFPSExtraAttributes_AttributeChanged OnArmorChanged;

	UPROPERTY(BlueprintAssignable)
	FFPSExtraAttributes_AttributeChanged OnMaxArmorChanged;
	
	UPROPERTY(BlueprintAssignable)
	FFPSExtraAttributes_AttributeChanged OnHPRegenChanged;

	UPROPERTY(BlueprintAssignable)
	FFPSExtraAttributes_AttributeChanged OnArmorRegenChanged;

	UPROPERTY(BlueprintAssignable)
	FFPSExtraAttributes_AttributeChanged OnStaminaRegenChanged;

protected:
	
	virtual void OnUnregister() override;

	virtual void HandleArmorChanged(const FOnAttributeChangeData& ChangeData);
	virtual void HandleMaxArmorChanged(const FOnAttributeChangeData& ChangeData);
	virtual void HandleHPRegenChanged(const FOnAttributeChangeData& ChangeData);
	virtual void HandleArmorRegenChanged(const FOnAttributeChangeData& ChangeData);
	virtual void HandleStaminaRegenChanged(const FOnAttributeChangeData& ChangeData);
	virtual void HandleManaRegenChanged(const FOnAttributeChangeData& ChangeData);

	
	// Ability system used by this component.
	UPROPERTY()
	ULyraAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<const UFPSExtraAttributes> FPSExtraAttributes;
};
