// My Shoot Them Up Game , All Rights Reserved
// В STUGameOverWidget.cpp


#include "UI/STUGameOverWidget.h"
#include "STUGameModeBase.h"
#include "Player/STUPlayerState.h"          // данные для статистики берем из PlayerSate
#include "UI/STUPlayerStatRowWidget.h"      // переменные строки статистики (name, kills, death, team)
#include "Components/VerticalBox.h"         // бокс в котором помещаем строки 
#include "STUUtils.h"                       // для функции преобразования int32 в Text 



bool USTUGameOverWidget::Initialize()
{
    if (GetWorld())
    {
        // получаем текущий GameMode
        const auto GameMode = Cast<ASTUGameModeBase>(GetWorld()->GetAuthGameMode());

        if (GameMode)
        {
            // подписываемся на делегат состояния игры OnMatchStateChanged
            GameMode->OnMatchStateChanged.AddUObject(this, &USTUGameOverWidget::OnMatchStateChanged);
            // будет вызываться функция OnMatchStateChanged
        }
    }

	return Super::Initialize();
}

// изменение состояния игры
void USTUGameOverWidget::OnMatchStateChanged(ESTUMatchState State)
{
    if (State == ESTUMatchState::GameOver)
    {
        // создаем таблицу статистики
        UpdatePlayerStat();
    }

}

// создает таблицу статистики
void USTUGameOverWidget::UpdatePlayerStat()
{
    if (!GetWorld() || !PlayerStatBox) return;

    // очищаем поле статистики (Удаляем дочерние элементы содержащиеся в VerticalBox)
    PlayerStatBox->ClearChildren();

    // в цикле получаем итераторы всех контроллеров, через них получаем контроллеры 
    // из контроллера получаем указатель на PlayerState 
    // создаем виджет строчки статистики для полученного PlayerState 
    // задаем значения текстовым полям строкового виджета в соответствии с данными из PlayerState 

    for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        // получаем контроллер текущего итератора 
        const auto Controller = It->Get();
        if (!Controller) continue;

        // получаем PlayerState из контроллера
        const auto PlayerState = Cast<ASTUPlayerState>(Controller->PlayerState);
        if (!PlayerState) continue;

        // создаем виджет строчки статистики
        const auto PlayerStatRowWidget = CreateWidget<USTUPlayerStatRowWidget>(GetWorld(), PlayerStatRowWidgetClass);
        if (!PlayerStatRowWidget) continue;

        // заполняем одну строку данных

        // заполняем поле Name, вызываем нашу функцию
        PlayerStatRowWidget->SetPlayerName(FText::FromString(PlayerState->GetPlayerName()));
        // PlayerState->GetPlayerName() - получаем имя игрока, вернет тип string
        // FText::FromString(name)      - преобразуем String в Text 

        // заполняем поле kills, преобразуем int32 в Text
        // PlayerStatRowWidget->SetKills(FText::FromString(FString::FromInt(PlayerState->GetKillsNum())));

        // заполняем поле kills, преобразование int32 в Text вынесено в отдельную функцию 
        PlayerStatRowWidget->SetKills(STUUtils::TextFromInt(PlayerState->GetKillsNum()));

        // поле Death
        PlayerStatRowWidget->SetDeaths(STUUtils::TextFromInt(PlayerState->GetDeathNum()));

        // поле Team
        PlayerStatRowWidget->SetTeam(STUUtils::TextFromInt(PlayerState->GetTeamID() ));

        // подсветка строки персонажа
        PlayerStatRowWidget->SetPlayerIndicatorVisibility(Controller->IsPlayerController());
        // Controller->IsPlayerController() - true если контроллер принадлежит пользователю 

        // заполненную строку добавляем в VerticalBox
        PlayerStatBox->AddChild(PlayerStatRowWidget);

    }

}


