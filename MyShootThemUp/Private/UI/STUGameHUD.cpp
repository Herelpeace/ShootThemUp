// My Shoot Them Up Game , All Rights Reserved
// В STUGameHUD.cpp



#include "UI/STUGameHUD.h"
#include "Engine/Canvas.h"        // для получения размеров экрана, в нем происходит отрисовка 
#include "Blueprint/UserWidget.h" // заголовочный файл виджетов
#include "STUGameModeBase.h"      // заголовочный файл нашего GameMode

DEFINE_LOG_CATEGORY_STATIC(LogSTUGameHUD, All, All);

void ASTUGameHUD::DrawHUD() 
{
    // так как функция переопределена, вызываем родительскую функцию через Super
    Super::DrawHUD();

    // функция в которой находится логика отрисовки
   // DrawCrossHair(); 
}


void ASTUGameHUD::BeginPlay()
{
    Super::BeginPlay();
    
    // заполняем ассоциотивный массив одновременно создавая виджеты
    GameWidgets.Add(ESTUMatchState::InProgress, CreateWidget<UUserWidget>(GetWorld(), PlayerHUDWidgetClass));
    GameWidgets.Add(ESTUMatchState::Pause,      CreateWidget<UUserWidget>(GetWorld(), PauseWidgetClass));

    // пробегаем по ассоциотивному массиву, добавляем виджеты во вьюпорт, отключаем их видимость
    for (auto GameWidgetPair : GameWidgets)
    {
        // получаем сырое значение виджета
        const auto GameWidget = GameWidgetPair.Value;
        if (!GameWidget) continue;
        // выводим виджет во вьюпорт
        GameWidget->AddToViewport();

        // делаем невидимым
        GameWidget->SetVisibility(ESlateVisibility::Hidden);
    }


    if (GetWorld())
    {
        // получаем текущий GameMode
        const auto GameMode = Cast<ASTUGameModeBase>(GetWorld()->GetAuthGameMode());

        if (GameMode)
        {
            // подписываемся на делегат состояния игры OnMatchStateChanged
            GameMode->OnMatchStateChanged.AddUObject(this, &ASTUGameHUD::OnMatchStateChanged);
            // будет вызываться функция OnMatchStateChanged
        }
    }
}

// Callback функция, которую подписываем на делегат изменения состояния игры в BeginPlay, OnMatchStateChanged
// вызывается каждый раз когда меняется состояние игры 
void ASTUGameHUD::OnMatchStateChanged(ESTUMatchState State)
{
    // делаем невидимым текущий виджет
    // первый раз функция не вызывается потому что CurrentWidget = null
    if (CurrentWidget)
    {
        CurrentWidget->SetVisibility(ESlateVisibility::Hidden);
    }

    // проверяем есть ли в ассоциотивном массиве ключ на данное состояние игры 
    // если есть, текущему виджету присваем значение в соответствии с текущим состоянием игры 
    if (GameWidgets.Contains(State))
    {
        CurrentWidget = GameWidgets[State];
    }

    // включаем видимость виджета 
    if (CurrentWidget)
    {
        CurrentWidget->SetVisibility(ESlateVisibility::Visible);
    }


    UE_LOG(LogSTUGameHUD,Warning, TEXT("Match state changed: %s "), *UEnum::GetValueAsString(State) );
}



void ASTUGameHUD::DrawCrossHair() 
{
    // int32 CenterX = Canvas->SizeX;  // размер текущего окна по оси Х
    // int32 CenterY = Canvas->SizeY;  // размер текущего окна по оси Y 

    const TInterval<float> Center(Canvas->SizeX * 0.5f, Canvas->SizeY * 0.5f);

    // TInterval - отрезок, хранит 2 переменные указаного типа
    // float     - тип данных который будет принимать TInterval
    // Center    - название переменной
    // (Canvas->SizeX * 0.5f, Canvas->SizeY*0.5f) - данные которые передаем в конструктор класса
    // TInterval( ElementType InMin, ElementType InMax )

    const float HalfLineSize = 10.0f;  // длина одной половинки линии
    const float LineThickness = 2.0f;  // толщина линии 
    const FLinearColor LineColor = FLinearColor::Green;

    // рисуем горизонтальную линию
    // функция отрисовки линий на экране
    DrawLine(Center.Min - HalfLineSize, Center.Max, Center.Min + HalfLineSize, Center.Max, LineColor, LineThickness);

    // Center.Min- HalfLineSize - начальная точка по Х (сдвинули в лево на 10)
    // Center.Max               - начальная точка по Y
    // Center.Min+HalfLineSize  - конечная точка по X (сдвинули в право на 10)
    // Center.Max               - конечная точка по Y (т.к линия горизонтальная, то Y не меняем)
    // LineColor                - цвет линии
    // LineThickness            - толщина линии

    // риусем вертикальную линию
    DrawLine(Center.Min, Center.Max - HalfLineSize, Center.Min, Center.Max + HalfLineSize, LineColor, LineThickness);

}