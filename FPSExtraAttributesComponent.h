// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/GameFrameworkComponent.h"
#include "Delegates/Delegate.h"
#include "GameFramework/Actor.h"
#include "FPSExtraAttributesComponent.generated.h"

struct FOnAttributeChangeData;
class UFPSExtraAttributes;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FFPSExtraAttributes_AttributeChanged, UFPSExtraAttributesComponent*, UFPSExtraAttributesComponent, float,
											   OldValue, float, NewValue, AActor*, Instigator);

UCLASS()
class FPSROGUELIKERUNTIME_API UFPSExtraAttributesComponent : public UGameFrameworkComponent
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

	// Returns the current value.
	UFUNCTION(BlueprintCallable, Category = "FPS|Attributes")
	float GetHPRegen() const;

	// Returns the current  value.
	UFUNCTION(BlueprintCallable, Category = "FPS|Attributes")
	float GetArmorRegen() const;

	UFUNCTION(BlueprintCallable, Category = "FPS|Attributes")
	float GetStaminaRegen() const;
	
	// Delegate fired when the value has changed.
	UPROPERTY(BlueprintAssignable)
	FFPSExtraAttributes_AttributeChanged OnHPRegenChanged;

	UPROPERTY(BlueprintAssignable)
	FFPSExtraAttributes_AttributeChanged OnArmorRegenChanged;

	UPROPERTY(BlueprintAssignable)
	FFPSExtraAttributes_AttributeChanged OnStaminaRegenChanged;

protected:
	
	virtual void OnUnregister() override;
	
	virtual void HandleHPRegenChanged(const FOnAttributeChangeData& ChangeData);
	virtual void HandleArmorRegenChanged(const FOnAttributeChangeData& ChangeData);
	virtual void HandleStaminaRegenChanged(const FOnAttributeChangeData& ChangeData);

	
	// Ability system used by this component.
	UPROPERTY()
	ULyraAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY()
	const UFPSExtraAttributesComponent* FPSExtraAttributes;
};
