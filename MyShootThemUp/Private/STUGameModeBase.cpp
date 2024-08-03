// My Shoot Them Up Game , All Rights Reserved
// � STUGameModeBase.cpp


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

// ���������� ������� GameMode, ����������� �� BeginPlay GameMode � �������
// �������������� ��������, �������� ������� ������ �������
void ASTUGameModeBase::StartPlay()
{
    Super::StartPlay();

    // ������� �������
    SpawnBots();

    // ����� ������ �����
    CurrentRound = 1;

    // ��������� �����
    StartRound();

}

// ����� ������������ ��� Pawno�
void ASTUGameModeBase::SpawnBots()
{
    if (!GetWorld()) return;

    for (int32 i = 0; i < GameData.PlayersNum - 1; ++i)
    {
        // ���������� �������� ������ 
        FActorSpawnParameters SpawnInfo;

        // ���������� �������� ������, ���� ���� ���� ������������ �������� 
        SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn ;

        // ������� ����������� npc (� ��������� ������ BP_STUAIController)
        // ����������� ��������� � ���������� ����� ����� ��� �������� Chatactero�
        const auto STUAIController = GetWorld()->SpawnActor<AAIController>(AIControllerClass,SpawnInfo);

        RestartPlayer(STUAIController);
    }

}

// �������������� ������� GetDefaultPawnClassForController, ����� ������ ����� Pawn ������� ����� �������� 
// ���� ����� �� ����� � ��������� �� ������� ��� �� ������� �� ���������������� � �������� ������ 
UClass* ASTUGameModeBase::GetDefaultPawnClassForController_Implementation(AController* InController)
{
    if (InController && InController->IsA<AAIController>())
    {
        // ���������� ����� ������� ������������� � ��������� BP (BP_STUAIController)
        return AIPawnClass;
    }
    else
    {
        // �������� ������������ �������, �� ����������������
        return Super::GetDefaultPawnClassForController_Implementation(InController);
    }
    
}


// ��������� �����
void ASTUGameModeBase::StartRound()
{
    RoundCoundDown = GameData.RoundTime;

    GetWorldTimerManager().SetTimer(GameRoundTimerHandle, this, &ASTUGameModeBase::GameTimerUpdate, 1.0f, true);

}

// ��������� ����� ������� 
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


// ���������� � ������ ������, ������ ������� ���� ������� �� �� ����� ������
void ASTUGameModeBase::RestartPlayers()
{
    if (!GetWorld()) return;

    for (auto It = GetWorld()->GetControllerIterator();It; ++It)
    {
        // GetWorld()->GetControllerIterator() - �������� ������ ���������� �� ����������� ������� ��������� �� ������ 

        ResetOnePlayer(It->Get());
        // It->Get() �������� ��������� �� �������
    }

}

// ����������� � �����, ������ ������� ���� Charactera, ���������� �������� ������� � �������� ��������� 
void ASTUGameModeBase::ResetOnePlayer(AController* Controller)
{
    if (Controller && Controller->GetPawn())
    {
        Controller->GetPawn()->Reset();
        // Controller->GetPawn()->Reset(); - ������ Destroy ���� Controller = 0 ��� Controller->PlayerState != 0
        // � npc PlayerState = 0 , ��� ��� �� ������������� �� ���������, ��� ����� ��� ����� �������� �������

    }

    RestartPlayer(Controller);

}
