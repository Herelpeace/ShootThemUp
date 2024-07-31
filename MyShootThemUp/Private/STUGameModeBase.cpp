// My Shoot Them Up Game , All Rights Reserved
// В STUGameModeBase.cpp


#include "STUGameModeBase.h"
#include "Player/STUBaseCharacter.h"
#include "Player/STUPlayerController.h"
#include "UI/STUGameHUD.h"
#include "AIController.h"

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