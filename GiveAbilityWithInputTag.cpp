// Fill out your copyright notice in the Description page of Project Settings.


#include "GiveAbilityActor.h"
#include "AbilitySystem/LyraAbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"

// Sets default values
AGiveAbilityActor::AGiveAbilityActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	TriggerCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Trigger Capsule"));
	TriggerCapsule->InitCapsuleSize(100.f, 100.0f);;
	TriggerCapsule->SetCollisionProfileName(TEXT("Trigger"));
	TriggerCapsule->SetupAttachment(RootComponent);

	TriggerCapsule->OnComponentBeginOverlap.AddDynamic(this, &AGiveAbilityActor::OnOverlapBegin); 
	TriggerCapsule->OnComponentEndOverlap.AddDynamic(this, &AGiveAbilityActor::OnOverlapEnd); 

}

void AGiveAbilityActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (bEnableDebugMessages)
	{			
		UE_LOG(LogTemp, Warning, TEXT("GiveAbilityActor, Overlapped"));
	}
	
	UAbilitySystemComponent* LyraASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(OtherActor);
	check(LyraASC);
	
	if (!LyraASC->IsOwnerActorAuthoritative())
	{
		// Must be authoritative to give or take ability sets.
		if (bEnableDebugMessages)
		{			
			UE_LOG(LogTemp, Warning, TEXT("GiveAbilityActor, Musc be Authoritive"));
		}
		return;
	}

	for (int32 AbilityIndex = 0; AbilityIndex < GrantedGameplayAbilities.Num(); ++AbilityIndex)
	{
	
		const FGiveAbilityActor_GameplayAbility& AbilityToGrant = GrantedGameplayAbilities[AbilityIndex];

		if (!IsValid(AbilityToGrant.Ability))
		{
			UE_LOG(LogTemp, Error, TEXT("GrantedGameplayAbilities[%d] on ability set [%s] is not valid."), AbilityIndex, *GetNameSafe(this));
			continue;
		}

		ULyraGameplayAbility* AbilityCDO = AbilityToGrant.Ability->GetDefaultObject<ULyraGameplayAbility>();

		FGameplayAbilitySpec AbilitySpec(AbilityCDO, AbilityToGrant.AbilityLevel);
		AbilitySpec.SourceObject = OtherActor;
		AbilitySpec.DynamicAbilityTags.AddTag(AbilityToGrant.InputTag);

		LyraASC->GiveAbility(AbilitySpec);
	}
}

void AGiveAbilityActor::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (bEnableDebugMessages)
	{			
		UE_LOG(LogTemp, Warning, TEXT("GiveAbilityActor, Overlapped Ended"));
	}	
}
