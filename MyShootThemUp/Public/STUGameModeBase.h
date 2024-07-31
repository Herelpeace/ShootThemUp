// My Shoot Them Up Game , All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Player/STUBaseCharacter.h"
#include "Player/STUPlayerController.h"
#include "STUCoreType.h"
#include "STUGameModeBase.generated.h"

class AAIController;    // дл€ спавна игроков

UCLASS()
class MYSHOOTTHEMUP_API ASTUGameModeBase : public AGameModeBase
{
    GENERATED_BODY()

public:
    ASTUGameModeBase();

    // внутренн€€ функци€ GameMode, запускаетс€ до BeginPlay GameMode и акторов
    // инициализируем настроки, вызываем функцию спавна игроков
    virtual void StartPlay() override;

    virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;


protected:
    UPROPERTY(EditDefaultsOnly, Category = "Game")
    TSubclassOf <AAIController> AIControllerClass;      // переменна€ AIControllera 

    UPROPERTY(EditDefaultsOnly, Category = "Game")
    TSubclassOf<APawn> AIPawnClass;                     // класс npc который будет спавнитьс€ GameMode

    UPROPERTY(EditDefaultsOnly, Category = "Game")
    FGameData GameData;                                 // наша структура с натройками GameMode

private:
    // спавн контроллеров дл€ Pawnoв
    void SpawnBots(); 

};
