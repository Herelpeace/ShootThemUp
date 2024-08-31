// My Shoot Them Up Game , All Rights Reserved
// � STUGameModeBase.cpp


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

// ���������� ������� GameMode, ����������� �� BeginPlay GameMode � �������
// �������������� ��������, �������� ������� ������ �������
void ASTUGameModeBase::StartPlay()
{
    Super::StartPlay();

    // ������� �������
    SpawnBots();

    // ����� ������ �����
    CurrentRound = 1;

    // ���������� ���� ��� � ������ ����, ������������ ������� �� ��������
    CreateTeamsInfo();

    // ��������� �����
    StartRound();

    // ������ ��������� ���� 
    SetMatchState(ESTUMatchState::InProgress);

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
            // �������� ����� ��� ������ ���������
            // ��������� input � ������������
            GameOver();
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

    // ������ �������
    RestartPlayer(Controller);

    // ������������� ����
    SetPlayerColor(Controller);
}

// ���������� ���� ��� � ������ ����, ������������ ������� �� ��������
void ASTUGameModeBase::CreateTeamsInfo()
{
    if (!GetWorld()) return;

    int32 TeamID = 1;

    // ��������� �� ���� ������������
    for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        const auto Controller = It->Get();

        if (!Controller) continue;
        
        // �������� ��������� �� PlayerState
        const auto PlayerState = Cast<ASTUPlayerState>(Controller->PlayerState);
        // Controller->PlayerState - �������� ��������� �� ������� ����� PlayerState
        // ����� ����������� ��� � ������ ������

        if (!PlayerState) continue;

        // ������ ����� �������
        PlayerState->SetTeamID(TeamID);

        // ����� ���� �������
        PlayerState->SetTeamColor(DetermineColorByTeamID(TeamID));

        // ������������� ����
        SetPlayerColor(Controller);

        // ����������� ��������� ����� �������
        TeamID = TeamID == 1 ? 2 : 1;

    }
}

// ���������� ���� � ����������� �� TeamID
FLinearColor ASTUGameModeBase::DetermineColorByTeamID(int32 TeamID) const
{
    // �������� TeamID-1 ������ ��� ���������� ��������� � ������� ������
    // ���������� ������ ����� ����� ���� 0 (��� ������), ���� 1, ���� 2
    if (TeamID - 1 < GameData.TeamColors.Num())
    {
        // ���������� ���� �������
        return GameData.TeamColors[TeamID - 1];
    }
    else
    {
        // ���������� ��������� ���� ��� ������ ������� �� ����� ���� 
        return GameData.DefaultTeamColor;
    }

}

// ������������ ���� ������
void ASTUGameModeBase::SetPlayerColor(AController* Controller)
{
    if (!Controller) return;

    // �������� Charactera
    const auto Character = Cast<ASTUBaseCharacter>(Controller->GetPawn());

    if (!Character) return;

    // �������� PlayerState
    const auto PlayerState = Cast<ASTUPlayerState>(Controller->PlayerState);
    if (!PlayerState) return;

    // ������������� ����, ����� ������� �� Charactera 
    Character->SetPlayerColor(PlayerState->GetTeamColor());

}

// ���������� ���������� �������
void ASTUGameModeBase::Killed(AController* KillerController, AController* VictimController)
{
    // ������� �������� PlayerStat� ������� � ������
    const auto KillerPlayerState = KillerController ? Cast<ASTUPlayerState>(KillerController->PlayerState) : nullptr;

    const auto  VictimPlayerState = VictimController ? Cast<ASTUPlayerState>(VictimController->PlayerState) : nullptr;

    if (KillerPlayerState)
    {
        // ������� ���������� ���������� �������
        KillerPlayerState->AddKill();
    }

    if (VictimPlayerState)
    {
        // ������ ���������� ���������� �������
        VictimPlayerState->AddDeath();
    }

    StartRespawn(VictimController);

}

// ������� ���������� �� ���� PlayerStat��, ����� ���� ��� ����������� ���� 
void ASTUGameModeBase::LogPlayerInfo()
{
    if (!GetWorld()) return;

    // ��������� �� ���� ������������
    for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        const auto Controller = It->Get();

        if (!Controller) continue;

        // �������� ��������� �� PlayerState
        const auto PlayerState = Cast<ASTUPlayerState>(Controller->PlayerState);
        // Controller->PlayerState - �������� ��������� �� ������� ����� PlayerState
        // ����� ����������� ��� � ������ ������

        if (!PlayerState) continue;

        // �������� ���� ������� ����������� 
        PlayerState->LogInfo();
    }

}

// ���������������
void ASTUGameModeBase::StartRespawn(AController* Controller)
{
    const auto RespawnAvialable = RoundCoundDown > MinRoundTimeForRespawn + GameData.RespawnTime;
    if (!RespawnAvialable) return;

    const auto RespawnComponent = STUUtils::GetSTPlayerComponent<USTURespawnComponent>(Controller);
    if (!RespawnComponent) return;

    // ��������� ������� 
    RespawnComponent->Respawn(GameData.RespawnTime);

}

// ������ ������� ��������� �� ���������� ��������� ������
void ASTUGameModeBase::RespawnRequest(AController* Controller)
{
    ResetOnePlayer(Controller);
    
}

// ���������� ����� ��� ������ ��������
void ASTUGameModeBase::GameOver()
{
    UE_LOG(LogSTUGameModeBase, Warning, TEXT("==========GAME OVER=========="));
    LogPlayerInfo();

    for (auto Pawn : TActorRange<APawn>(GetWorld()))
    {
        if (Pawn)
        {
            // ��������� ��������
            // ��������� �������� (movementComponent)
            // ��������� ���������� ���������
            Pawn->TurnOff();

            // ��������� inputComponent � ���� ����������
            Pawn->DisableInput(nullptr);    
        }

    }

    // ������ ��������� ���� 
    SetMatchState(ESTUMatchState::GameOver);
}

// ������������� MatchState, � �������� Broadcast �������� ��������� ���� OnMatchStateChanged
void ASTUGameModeBase::SetMatchState(ESTUMatchState State)
{
    // ���� ������� ��������� ���� ����� ������ ���������, �������
    if (MatchState == State) return;

    MatchState = State;

    // ��������� ���� ��� ��������� ���� ���������� 
    OnMatchStateChanged.Broadcast(MatchState);

}

// �������������� ������� ����� GameMode
bool ASTUGameModeBase::SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate)
{
    // �������� ��������� ������������ �������, true - ������������ �����
    const auto PauseSet = Super::SetPause(PC, CanUnpauseDelegate);

    if (PauseSet)
    {
        // ������ ��������� ���� 
        SetMatchState(ESTUMatchState::Pause);
    }

    return  PauseSet;
}


// ������� ������ ����� 
bool ASTUGameModeBase::ClearPause()
{
    // ��������� �������� ������������ ������� 
    const auto PauseCleared = Super::ClearPause();

    if (PauseCleared)
    {
        // ������ ��������� ���� 
        SetMatchState(ESTUMatchState::InProgress);
    }

    return PauseCleared;
}





