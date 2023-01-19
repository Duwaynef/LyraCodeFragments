# LyraCodeFragments
intresting code fragments from lyra cpp

## MyBlueprintFunctionLibary

Contains two blueprint nodes currently:
  - Give Actor ability with InputTag
      - Ability      
      - Ability Level
      - Target
      - InputTag
      - Stackable

![alt text](https://github.com/DuwayneF/LyraCodeFragments/blob/main/images/GiveActorAbility.png?raw=true)
      
  - SpawnEnemy: (Spawns enemy using the gameplay experience, and pawn data)
      - GameMode
      - GameStateComponent
      - AIControler

![alt text](https://github.com/DuwayneF/LyraCodeFragments/blob/main/images/SpawnEnemyWithHeroData.png?raw=true)

## FPSGameMode

This is a example game mode that allows you to give enemies and players different pawn data from your gameplay experience, this allows you to spawn enemies with their own specific gameplay abilities etc. for instance if you wanted your player to have the respawn abiltiy but not the enemy you could have the same pawn data for both, but leave out the respawn on the enemy data.

we must make other lyra changes to make this implmentation work, that includes:

LyraPlayerState.cpp
  - #include "FPSGamemode.h" // relative to your gamemode at the top
  - change: (here we are telling it to call our custom get pawn data code) around line: 126
      - if (const ULyraPawnData* NewPawnData = LyraGameMode->GetPawnDataForController(GetOwningController()))
      to
      - if (const ULyraPawnData* NewPawnData = FPSGameMode->GetEnemyDataForController(GetOwningController()))

LyraExperienceDefinition.h
  - we add: around line:46 under public:
      - 	```c
          UPROPERTY(EditDefaultsOnly, Category=Gameplay)
          TObjectPtr<const ULyraPawnData> DefaultEnemyData;
          ``` 

In the FPSGamemode.cpp the logic can be extended to do more than player vs bot hero data if you needed
different data for different enemies per say.

in the end we end up with this image below in our experience definition:

![alt text](https://github.com/DuwayneF/LyraCodeFragments/blob/main/images/EnemyPawnData.png?raw=true)


## FPSTeamCreationComponent

This allows overriding of the player team setup, in the case of the code posted here it does players become team 1 and bots team 2
to make a PvE based game.

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
