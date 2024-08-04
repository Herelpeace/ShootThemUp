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
    int32 CurrentRound = 1;             // текущий раунд
    int32 RoundCoundDown = 0;           // врем€ до конца раунда
    FTimerHandle GameRoundTimerHandle;  // дискриптор таймера который будет отсчитывать врем€ в раунде


    // спавн контроллеров дл€ Pawnoв
    void SpawnBots(); 

    // запускает раунд
    void StartRound();

    // обновл€ет врем€ таймера 
    void GameTimerUpdate();

    // вызываетс€ в начале раунда, делает респавн всех игроков на их места старта
    void RestartPlayers();

    // вызываеетс€ в цикле, делает респавн того Charactera, контроллер которого передан в качестве параметра 
    void ResetOnePlayer(AController* Controller);

    // вызываетс€ один раз в начале игры, распредел€ет игроков по командам
    void CreateTeamsInfo(); 

    // возвращает цвет в зависимости от TeamID
    FLinearColor DetermineColorByTeamID(int32 TeamID) const;

    // устанавлиает цвет игроку
    void SetPlayerColor(AController* Controller);

};
