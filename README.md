# LyraCodeFragments
intresting code fragments from lyra cpp

## FPSExtraAttributes & FPSExtraAttributesComponent

This allows you to extend the existing attributes. if you want to add it to all LyraPlayercharacters by default without using the definitions (i haven't been able to get this working with the experience definitions) you have to make the changes to Lyra below.

LyraCharacter.h
  - #include "FPSExtraAttributesComponent.h"
  - import class
    - class FPSExtraAttributesComponent;
  - line 157 ish under private:
    - 	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Lyra|Character", Meta = (AllowPrivateAccess = "true"))
	      TObjectPtr<UFPSExtraAttributesComponent> FPSExtraAttributesComponent;

LyraCharacter.cpp
  -   #include "FPSExtraAttributesComponent.h"
  -   line 97 ish
    -   FPSExtraAttributesComponent = CreateDefaultSubobject<UFPSExtraAttributesComponent>(TEXT("FPSExtraAttributesComponent"));
  - under OnAbilitySystemInitialized() line 226 ish
    -   FPSExtraAttributesComponent->InitializeWithAbilitySystem(LyraASC);
  - under UninitializeFromAbilitySystem() line 234 ish
    -   FPSExtraAttributesComponent->UninitializeFromAbilitySystem();

LyraPlayerState.cpp
  -   #include "FPSExtraAttributes.h"
  -   line 56 ish
    -   CreateDefaultSubobject<UFPSExtraAttributes>(TEXT("FPSExtraAttributes"));

## GiveAbilityWithInputTag

With this code you can make a blueprint actor ( this as the base class ) and it will give you the ability to grant a ability ( or many )
during gameplay with an input tag attached. This is something i haven't been able to figure out how to do without cpp.

You can configure an array of:
  - Gameplay ability
  - InputTag
  - Ability level
  - If the ability stacks

And display debug messages that will show all abilities the user has


## MyBlueprintFunctionLibary

Contains one blueprint node currently:
  - Give Actor ability with InputTag
      - Ability      
      - Ability Level
      - Target
      - InputTag
      - Stackable      
