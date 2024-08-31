// My Shoot Them Up Game , All Rights Reserved
// � STUGameHUD.cpp



#include "UI/STUGameHUD.h"
#include "Engine/Canvas.h"        // ��� ��������� �������� ������, � ��� ���������� ��������� 
#include "Blueprint/UserWidget.h" // ������������ ���� ��������
#include "STUGameModeBase.h"      // ������������ ���� ������ GameMode

DEFINE_LOG_CATEGORY_STATIC(LogSTUGameHUD, All, All);

void ASTUGameHUD::DrawHUD() 
{
    // ��� ��� ������� ��������������, �������� ������������ ������� ����� Super
    Super::DrawHUD();

    // ������� � ������� ��������� ������ ���������
   // DrawCrossHair(); 
}


void ASTUGameHUD::BeginPlay()
{
    Super::BeginPlay();
    
    // ��������� ������������� ������ ������������ �������� �������
    GameWidgets.Add(ESTUMatchState::InProgress, CreateWidget<UUserWidget>(GetWorld(), PlayerHUDWidgetClass));
    GameWidgets.Add(ESTUMatchState::Pause,      CreateWidget<UUserWidget>(GetWorld(), PauseWidgetClass));

    // ��������� �� �������������� �������, ��������� ������� �� �������, ��������� �� ���������
    for (auto GameWidgetPair : GameWidgets)
    {
        // �������� ����� �������� �������
        const auto GameWidget = GameWidgetPair.Value;
        if (!GameWidget) continue;
        // ������� ������ �� �������
        GameWidget->AddToViewport();

        // ������ ���������
        GameWidget->SetVisibility(ESlateVisibility::Hidden);
    }


    if (GetWorld())
    {
        // �������� ������� GameMode
        const auto GameMode = Cast<ASTUGameModeBase>(GetWorld()->GetAuthGameMode());

        if (GameMode)
        {
            // ������������� �� ������� ��������� ���� OnMatchStateChanged
            GameMode->OnMatchStateChanged.AddUObject(this, &ASTUGameHUD::OnMatchStateChanged);
            // ����� ���������� ������� OnMatchStateChanged
        }
    }
}

// Callback �������, ������� ����������� �� ������� ��������� ��������� ���� � BeginPlay, OnMatchStateChanged
// ���������� ������ ��� ����� �������� ��������� ���� 
void ASTUGameHUD::OnMatchStateChanged(ESTUMatchState State)
{
    // ������ ��������� ������� ������
    // ������ ��� ������� �� ���������� ������ ��� CurrentWidget = null
    if (CurrentWidget)
    {
        CurrentWidget->SetVisibility(ESlateVisibility::Hidden);
    }

    // ��������� ���� �� � ������������� ������� ���� �� ������ ��������� ���� 
    // ���� ����, �������� ������� �������� �������� � ������������ � ������� ���������� ���� 
    if (GameWidgets.Contains(State))
    {
        CurrentWidget = GameWidgets[State];
    }

    // �������� ��������� ������� 
    if (CurrentWidget)
    {
        CurrentWidget->SetVisibility(ESlateVisibility::Visible);
    }


    UE_LOG(LogSTUGameHUD,Warning, TEXT("Match state changed: %s "), *UEnum::GetValueAsString(State) );
}



void ASTUGameHUD::DrawCrossHair() 
{
    // int32 CenterX = Canvas->SizeX;  // ������ �������� ���� �� ��� �
    // int32 CenterY = Canvas->SizeY;  // ������ �������� ���� �� ��� Y 

    const TInterval<float> Center(Canvas->SizeX * 0.5f, Canvas->SizeY * 0.5f);

    // TInterval - �������, ������ 2 ���������� ��������� ����
    // float     - ��� ������ ������� ����� ��������� TInterval
    // Center    - �������� ����������
    // (Canvas->SizeX * 0.5f, Canvas->SizeY*0.5f) - ������ ������� �������� � ����������� ������
    // TInterval( ElementType InMin, ElementType InMax )

    const float HalfLineSize = 10.0f;  // ����� ����� ��������� �����
    const float LineThickness = 2.0f;  // ������� ����� 
    const FLinearColor LineColor = FLinearColor::Green;

    // ������ �������������� �����
    // ������� ��������� ����� �� ������
    DrawLine(Center.Min - HalfLineSize, Center.Max, Center.Min + HalfLineSize, Center.Max, LineColor, LineThickness);

    // Center.Min- HalfLineSize - ��������� ����� �� � (�������� � ���� �� 10)
    // Center.Max               - ��������� ����� �� Y
    // Center.Min+HalfLineSize  - �������� ����� �� X (�������� � ����� �� 10)
    // Center.Max               - �������� ����� �� Y (�.� ����� ��������������, �� Y �� ������)
    // LineColor                - ���� �����
    // LineThickness            - ������� �����

    // ������ ������������ �����
    DrawLine(Center.Min, Center.Max - HalfLineSize, Center.Min, Center.Max + HalfLineSize, LineColor, LineThickness);

}