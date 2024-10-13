// My Shoot Them Up Game , All Rights Reserved
// � STUGameOverWidget.cpp


#include "UI/STUGameOverWidget.h"
#include "STUGameModeBase.h"
#include "Player/STUPlayerState.h"          // ������ ��� ���������� ����� �� PlayerSate
#include "UI/STUPlayerStatRowWidget.h"      // ���������� ������ ���������� (name, kills, death, team)
#include "Components/VerticalBox.h"         // ���� � ������� �������� ������ 
#include "STUUtils.h"                       // ��� ������� �������������� int32 � Text 



bool USTUGameOverWidget::Initialize()
{
    if (GetWorld())
    {
        // �������� ������� GameMode
        const auto GameMode = Cast<ASTUGameModeBase>(GetWorld()->GetAuthGameMode());

        if (GameMode)
        {
            // ������������� �� ������� ��������� ���� OnMatchStateChanged
            GameMode->OnMatchStateChanged.AddUObject(this, &USTUGameOverWidget::OnMatchStateChanged);
            // ����� ���������� ������� OnMatchStateChanged
        }
    }

	return Super::Initialize();
}

// ��������� ��������� ����
void USTUGameOverWidget::OnMatchStateChanged(ESTUMatchState State)
{
    if (State == ESTUMatchState::GameOver)
    {
        // ������� ������� ����������
        UpdatePlayerStat();
    }

}

// ������� ������� ����������
void USTUGameOverWidget::UpdatePlayerStat()
{
    if (!GetWorld() || !PlayerStatBox) return;

    // ������� ���� ���������� (������� �������� �������� ������������ � VerticalBox)
    PlayerStatBox->ClearChildren();

    // � ����� �������� ��������� ���� ������������, ����� ��� �������� ����������� 
    // �� ����������� �������� ��������� �� PlayerState 
    // ������� ������ ������� ���������� ��� ����������� PlayerState 
    // ������ �������� ��������� ����� ���������� ������� � ������������ � ������� �� PlayerState 

    for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        // �������� ���������� �������� ��������� 
        const auto Controller = It->Get();
        if (!Controller) continue;

        // �������� PlayerState �� �����������
        const auto PlayerState = Cast<ASTUPlayerState>(Controller->PlayerState);
        if (!PlayerState) continue;

        // ������� ������ ������� ����������
        const auto PlayerStatRowWidget = CreateWidget<USTUPlayerStatRowWidget>(GetWorld(), PlayerStatRowWidgetClass);
        if (!PlayerStatRowWidget) continue;

        // ��������� ���� ������ ������

        // ��������� ���� Name, �������� ���� �������
        PlayerStatRowWidget->SetPlayerName(FText::FromString(PlayerState->GetPlayerName()));
        // PlayerState->GetPlayerName() - �������� ��� ������, ������ ��� string
        // FText::FromString(name)      - ����������� String � Text 

        // ��������� ���� kills, ����������� int32 � Text
        // PlayerStatRowWidget->SetKills(FText::FromString(FString::FromInt(PlayerState->GetKillsNum())));

        // ��������� ���� kills, �������������� int32 � Text �������� � ��������� ������� 
        PlayerStatRowWidget->SetKills(STUUtils::TextFromInt(PlayerState->GetKillsNum()));

        // ���� Death
        PlayerStatRowWidget->SetDeaths(STUUtils::TextFromInt(PlayerState->GetDeathNum()));

        // ���� Team
        PlayerStatRowWidget->SetTeam(STUUtils::TextFromInt(PlayerState->GetTeamID() ));

        // ��������� ������ ���������
        PlayerStatRowWidget->SetPlayerIndicatorVisibility(Controller->IsPlayerController());
        // Controller->IsPlayerController() - true ���� ���������� ����������� ������������ 

        // ����������� ������ ��������� � VerticalBox
        PlayerStatBox->AddChild(PlayerStatRowWidget);

    }

}


