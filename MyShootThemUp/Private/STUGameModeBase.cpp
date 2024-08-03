// My Shoot Them Up Game , All Rights Reserved
// В STUGameModeBase.cpp


#include "STUGameModeBase.h"
#include "Player/STUBaseCharacter.h"
#include "Player/STUPlayerController.h"
#include "UI/STUGameHUD.h"
#include "AIController.h"

DEFINE_LOG_CATEGORY_STATIC(LogSTUGameModeBase, All, All);

ASTUGameModeBase::ASTUGameModeBase() 
{
    DefaultPawnClass      = ASTUBaseCharacter::StaticClass();
    PlayerControllerClass = ASTUPlayerController::StaticClass();
    HUDClass              = ASTUGameHUD::StaticClass();
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

    // запускаем раунд
    StartRound();

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
            UE_LOG(LogSTUGameModeBase, Warning, TEXT("==========GAME OVER=========="));
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

    RestartPlayer(Controller);

}
