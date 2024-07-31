// My Shoot Them Up Game , All Rights Reserved
// � STUGameModeBase.cpp


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

// ���������� ������� GameMode, ����������� �� BeginPlay GameMode � �������
// �������������� ��������, �������� ������� ������ �������
void ASTUGameModeBase::StartPlay()
{
    Super::StartPlay();

    // ������� �������
    SpawnBots();

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