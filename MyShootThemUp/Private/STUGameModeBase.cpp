// My Shoot Them Up Game , All Rights Reserved
// В STUGameModeBase.cpp


#include "STUGameModeBase.h"
#include "Player/STUBaseCharacter.h"
#include "Player/STUPlayerController.h"
#include "UI/STUGameHUD.h"
#include "AIController.h"
#include "Player/STUPlayerState.h"
#include "STUUtils.h"
#include "Components//STURespawnComponent.h"
#include "EngineUtils.h"

DEFINE_LOG_CATEGORY_STATIC(LogSTUGameModeBase, All, All);

constexpr static int32 MinRoundTimeForRespawn = 10;

ASTUGameModeBase::ASTUGameModeBase() 
{
    DefaultPawnClass      = ASTUBaseCharacter::StaticClass();
    PlayerControllerClass = ASTUPlayerController::StaticClass();
    HUDClass              = ASTUGameHUD::StaticClass();
    PlayerStateClass      = ASTUPlayerState::StaticClass();
}

// внутренняя функция GameMode, запускается до BeginPlay GameMode и акторов
// инициализируем настроки, вызываем функцию спавна игроков
void ASTUGameModeBase::StartPlay()
{
    Super::StartPlay();

    // спавним игроков
    SpawnBots();

    // самый первый раунд
    CurrentRound = 1;

    // вызывается один раз в начале игры, распределяет игроков по командам
    CreateTeamsInfo();

    // запускаем раунд
    StartRound();

    // меняем состояние игры 
    SetMatchState(ESTUMatchState::InProgress);

}


// спавн контроллеров для Pawnoв
void ASTUGameModeBase::SpawnBots()
{
    if (!GetWorld()) return;

    for (int32 i = 0; i < GameData.PlayersNum - 1; ++i)
    {
        // переменная настроек спавна 
        FActorSpawnParameters SpawnInfo;

        // выставляем спавнить всегда, даже если есть столкновения коллизии 
        SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn ;

        // спавним контроллеры npc (в редакторе задаем BP_STUAIController)
        // контроллеры сохраняем в переменную чтобы через них спавнить Chatacteroв
        const auto STUAIController = GetWorld()->SpawnActor<AAIController>(AIControllerClass,SpawnInfo);

        RestartPlayer(STUAIController);
    }

}


// переопределили функцию GetDefaultPawnClassForController, чтобы задать класс Pawn который нужно спавнить 
// если класс не задан в настроках то вызыаем эту же функцию не переопределенную у базового класса 
UClass* ASTUGameModeBase::GetDefaultPawnClassForController_Implementation(AController* InController)
{
    if (InController && InController->IsA<AAIController>())
    {
        // возвращаем класс который устанавливаем в настроках BP (BP_STUAIController)
        return AIPawnClass;
    }
    else
    {
        // вызываем родительскую функцию, не переопределенную
        return Super::GetDefaultPawnClassForController_Implementation(InController);
    }
    
}


// запускает раунд
void ASTUGameModeBase::StartRound()
{
    RoundCoundDown = GameData.RoundTime;

    GetWorldTimerManager().SetTimer(GameRoundTimerHandle, this, &ASTUGameModeBase::GameTimerUpdate, 1.0f, true);

}

// обновляет время таймера 
void ASTUGameModeBase::GameTimerUpdate()
{
    UE_LOG(LogSTUGameModeBase, Warning, TEXT(" Time: %i / Round: %i "), RoundCoundDown, GameData.RoundNum);

    if (--RoundCoundDown == 0)
    {
        GetWorldTimerManager().ClearTimer(GameRoundTimerHandle);

        if (CurrentRound + 1 <= GameData.RoundNum)
        {
            ++CurrentRound;
            RestartPlayers();
            StartRound();
        }
        else
        {
            // вызываем когда все раунды закончены
            // отключаем input и передвижения
            GameOver();
        }
    }
}


// вызывается в начале раунда, делает респавн всех игроков на их места старта
void ASTUGameModeBase::RestartPlayers()
{
    if (!GetWorld()) return;

    for (auto It = GetWorld()->GetControllerIterator();It; ++It)
    {
        // GetWorld()->GetControllerIterator() - получить массив указателей на контроллеры которые находятся на уровне 

        ResetOnePlayer(It->Get());
        // It->Get() получить указатель из массива
    }

}

// вызываеется в цикле, делает респавн того Charactera, контроллер которого передан в качестве параметра 
void ASTUGameModeBase::ResetOnePlayer(AController* Controller)
{
    if (Controller && Controller->GetPawn())
    {
        Controller->GetPawn()->Reset();
        // Controller->GetPawn()->Reset(); - делает Destroy если Controller = 0 или Controller->PlayerState != 0
        // у npc PlayerState = 0 , так как он автоматически не спавнится, для спана его нужно включать вручную

    }

    // делает респавн
    RestartPlayer(Controller);

    // устанавливаем цвет
    SetPlayerColor(Controller);
}

// вызывается один раз в начале игры, распределяет игроков по командам
void ASTUGameModeBase::CreateTeamsInfo()
{
    if (!GetWorld()) return;

    int32 TeamID = 1;

    // пробегаем по всем контроллерам
    for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        const auto Controller = It->Get();

        if (!Controller) continue;
        
        // получаем указатель на PlayerState
        const auto PlayerState = Cast<ASTUPlayerState>(Controller->PlayerState);
        // Controller->PlayerState - получаем указатель на базовый класс PlayerState
        // затем преобразуем его к нашему классу

        if (!PlayerState) continue;

        // задаем номер команды
        PlayerState->SetTeamID(TeamID);

        // задем цвет команды
        PlayerState->SetTeamColor(DetermineColorByTeamID(TeamID));

        // устанавливаем цвет
        SetPlayerColor(Controller);

        // присваиваем следующий номер команды
        TeamID = TeamID == 1 ? 2 : 1;

    }
}

// возвращает цвет в зависимости от TeamID
FLinearColor ASTUGameModeBase::DetermineColorByTeamID(int32 TeamID) const
{
    // проверка TeamID-1 меньше чем количество элементов в массиве цветов
    // количество цветов будет равно либо 0 (нет цветов), либо 1, либо 2
    if (TeamID - 1 < GameData.TeamColors.Num())
    {
        // возвращаем цвет команды
        return GameData.TeamColors[TeamID - 1];
    }
    else
    {
        // возвращаем дефолтный цвет для команд которым не задан цвет 
        return GameData.DefaultTeamColor;
    }

}

// устанавлиает цвет игроку
void ASTUGameModeBase::SetPlayerColor(AController* Controller)
{
    if (!Controller) return;

    // получаем Charactera
    const auto Character = Cast<ASTUBaseCharacter>(Controller->GetPawn());

    if (!Character) return;

    // получаем PlayerState
    const auto PlayerState = Cast<ASTUPlayerState>(Controller->PlayerState);
    if (!PlayerState) return;

    // устанавливаем цвет, новая функция из Charactera 
    Character->SetPlayerColor(PlayerState->GetTeamColor());

}

// записывает статистику убийств
void ASTUGameModeBase::Killed(AController* KillerController, AController* VictimController)
{
    // сначала получаем PlayerStatы киллера и жертвы
    const auto KillerPlayerState = KillerController ? Cast<ASTUPlayerState>(KillerController->PlayerState) : nullptr;

    const auto  VictimPlayerState = VictimController ? Cast<ASTUPlayerState>(VictimController->PlayerState) : nullptr;

    if (KillerPlayerState)
    {
        // киллеру прибавляем количество убийств
        KillerPlayerState->AddKill();
    }

    if (VictimPlayerState)
    {
        // жертве прибавляем количество смертей
        VictimPlayerState->AddDeath();
    }

    StartRespawn(VictimController);

}

// выводит информацию по всем PlayerStatам, после того как завончилась игра 
void ASTUGameModeBase::LogPlayerInfo()
{
    if (!GetWorld()) return;

    // пробегаем по всем контроллерам
    for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        const auto Controller = It->Get();

        if (!Controller) continue;

        // получаем указатель на PlayerState
        const auto PlayerState = Cast<ASTUPlayerState>(Controller->PlayerState);
        // Controller->PlayerState - получаем указатель на базовый класс PlayerState
        // затем преобразуем его к нашему классу

        if (!PlayerState) continue;

        // вызываем нашу функцию логирования 
        PlayerState->LogInfo();
    }

}

// вспомогательная
void ASTUGameModeBase::StartRespawn(AController* Controller)
{
    const auto RespawnAvialable = RoundCoundDown > MinRoundTimeForRespawn + GameData.RespawnTime;
    if (!RespawnAvialable) return;

    const auto RespawnComponent = STUUtils::GetSTPlayerComponent<USTURespawnComponent>(Controller);
    if (!RespawnComponent) return;

    // запускаем респавн 
    RespawnComponent->Respawn(GameData.RespawnTime);

}

// делвем респавн персонажа не дожидаяясь окончания раунда
void ASTUGameModeBase::RespawnRequest(AController* Controller)
{
    ResetOnePlayer(Controller);
    
}

// вызывается когда все раунды окончены
void ASTUGameModeBase::GameOver()
{
    UE_LOG(LogSTUGameModeBase, Warning, TEXT("==========GAME OVER=========="));
    LogPlayerInfo();

    for (auto Pawn : TActorRange<APawn>(GetWorld()))
    {
        if (Pawn)
        {
            // отключает коллизию
            // отключает движение (movementComponent)
            // отключает физические симуляции
            Pawn->TurnOff();

            // отключаем inputComponent у всех персонажей
            Pawn->DisableInput(nullptr);    
        }

    }

    // меняем состояние игры 
    SetMatchState(ESTUMatchState::GameOver);
}

// устанавливает MatchState, и вызывает Broadcast делегата состояния игры OnMatchStateChanged
void ASTUGameModeBase::SetMatchState(ESTUMatchState State)
{
    // если текущее состояние игры равно новому состоянию, выходим
    if (MatchState == State) return;

    MatchState = State;

    // оповещаем всех что состояние игры изменилось 
    OnMatchStateChanged.Broadcast(MatchState);

}

// переопределяем функцию паузы GameMode
bool ASTUGameModeBase::SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate)
{
    // получаем состояние родительской функции, true - установилась пауза
    const auto PauseSet = Super::SetPause(PC, CanUnpauseDelegate);

    if (PauseSet)
    {
        // меняем состояние игры 
        SetMatchState(ESTUMatchState::Pause);
    }

    return  PauseSet;
}


// функция снятия паузы 
bool ASTUGameModeBase::ClearPause()
{
    // сохраняем значение родительской функции 
    const auto PauseCleared = Super::ClearPause();

    if (PauseCleared)
    {
        // меняем состояние игры 
        SetMatchState(ESTUMatchState::InProgress);
    }

    return PauseCleared;
}





