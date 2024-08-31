// My Shoot Them Up Game , All Rights Reserved
// В STUGameModeBase.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Player/STUBaseCharacter.h"
#include "Player/STUPlayerController.h"
#include "STUCoreType.h"
#include "STUGameModeBase.generated.h"

class AAIController;    // для спавна игроков

UCLASS()
class MYSHOOTTHEMUP_API ASTUGameModeBase : public AGameModeBase
{
    GENERATED_BODY()

public:
    ASTUGameModeBase();

    // создаем экземпляр делегата состояний игры 
    FOnMatchStateChangedSignature OnMatchStateChanged;

    // внутренняя функция GameMode, запускается до BeginPlay GameMode и акторов
    // инициализируем настроки, вызываем функцию спавна игроков
    virtual void StartPlay() override;

    virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;

    // записывает статистику убийств
    void Killed(AController* KillerController, AController* VictimController);

    // настроки GameData
    FGameData GetGameData() const { return GameData; }

    // текущий раунд
    int32 GetCurrentRoundNum() const { return CurrentRound; }

    // время до конца раунда
    int32 GetRoundSecondsRemaining() const { return RoundCoundDown; }

    // делвем респавн персонажа не дожидаяясь окончания раунда
    void RespawnRequest(AController* Controller);

    // переопределяем функцию паузы GameMode
    virtual bool SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate = FCanUnpause()) override;

    // функция снятия паузы 
    virtual bool ClearPause() override;


protected:
    UPROPERTY(EditDefaultsOnly, Category = "Game")
    TSubclassOf <AAIController> AIControllerClass;      // переменная AIControllera 

    UPROPERTY(EditDefaultsOnly, Category = "Game")
    TSubclassOf<APawn> AIPawnClass;                     // класс npc который будет спавниться GameMode

    UPROPERTY(EditDefaultsOnly, Category = "Game")
    FGameData GameData;                                 // наша структура с натройками GameMode

private:
    ESTUMatchState MatchState = ESTUMatchState::WaitingToStart;  // текущее состояние игры

    int32 CurrentRound = 1;             // текущий раунд
    int32 RoundCoundDown = 0;           // время до конца раунда
    FTimerHandle GameRoundTimerHandle;  // дискриптор таймера который будет отсчитывать время в раунде


    // спавн контроллеров для Pawnoв
    void SpawnBots(); 

    // запускает раунд
    void StartRound();

    // обновляет время таймера 
    void GameTimerUpdate();

    // вызывается в начале раунда, делает респавн всех игроков на их места старта
    void RestartPlayers();

    // вызываеется в цикле, делает респавн того Charactera, контроллер которого передан в качестве параметра 
    void ResetOnePlayer(AController* Controller);

    // вызывается один раз в начале игры, распределяет игроков по командам
    void CreateTeamsInfo(); 

    // возвращает цвет в зависимости от TeamID
    FLinearColor DetermineColorByTeamID(int32 TeamID) const;

    // устанавлиает цвет игроку
    void SetPlayerColor(AController* Controller);

    // выводит информацию по всем PlayerStatам, после того как завончилась игра 
    void LogPlayerInfo();

    // вспомогательная
    void StartRespawn(AController* Controller);

    // вызывается когда все раунды окончены
    void GameOver();

    // устанавливает MatchState, и вызывает Broadcast делегата состояния игры OnMatchStateChanged
    void SetMatchState(ESTUMatchState State);

};
