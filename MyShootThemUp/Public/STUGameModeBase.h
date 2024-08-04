// My Shoot Them Up Game , All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Player/STUBaseCharacter.h"
#include "Player/STUPlayerController.h"
#include "STUCoreType.h"
#include "STUGameModeBase.generated.h"

class AAIController;    // ��� ������ �������

UCLASS()
class MYSHOOTTHEMUP_API ASTUGameModeBase : public AGameModeBase
{
    GENERATED_BODY()

public:
    ASTUGameModeBase();

    // ���������� ������� GameMode, ����������� �� BeginPlay GameMode � �������
    // �������������� ��������, �������� ������� ������ �������
    virtual void StartPlay() override;

    virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;


protected:
    UPROPERTY(EditDefaultsOnly, Category = "Game")
    TSubclassOf <AAIController> AIControllerClass;      // ���������� AIControllera 

    UPROPERTY(EditDefaultsOnly, Category = "Game")
    TSubclassOf<APawn> AIPawnClass;                     // ����� npc ������� ����� ���������� GameMode

    UPROPERTY(EditDefaultsOnly, Category = "Game")
    FGameData GameData;                                 // ���� ��������� � ���������� GameMode

private:
    int32 CurrentRound = 1;             // ������� �����
    int32 RoundCoundDown = 0;           // ����� �� ����� ������
    FTimerHandle GameRoundTimerHandle;  // ���������� ������� ������� ����� ����������� ����� � ������


    // ����� ������������ ��� Pawno�
    void SpawnBots(); 

    // ��������� �����
    void StartRound();

    // ��������� ����� ������� 
    void GameTimerUpdate();

    // ���������� � ������ ������, ������ ������� ���� ������� �� �� ����� ������
    void RestartPlayers();

    // ����������� � �����, ������ ������� ���� Charactera, ���������� �������� ������� � �������� ��������� 
    void ResetOnePlayer(AController* Controller);

    // ���������� ���� ��� � ������ ����, ������������ ������� �� ��������
    void CreateTeamsInfo(); 

    // ���������� ���� � ����������� �� TeamID
    FLinearColor DetermineColorByTeamID(int32 TeamID) const;

    // ������������ ���� ������
    void SetPlayerColor(AController* Controller);

};
