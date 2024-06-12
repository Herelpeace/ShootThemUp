// My Shoot Them Up Game , All Rights Reserved
// � STUGameModeBase.cpp



#include "UI/STUGameHUD.h"
#include "Engine/Canvas.h"        // ��� ��������� �������� ������, � ��� ���������� ��������� 
#include "Blueprint/UserWidget.h" // ������������ ���� ��������

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

    auto PlayerHUDWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerHUDWidgetClass);
    // CreateWidget <>()    - ��������� ������� �������� �������
    // UUserWidget          - ��� �������, ������� ����� ��������
    // GetWorld()           - ��������� �� ������ ���������, ����� ��� �� �������� this
    // PlayerHUDWidgetClass - ����� ������� ������� ����� �������, �� ���� ���������� � ������� ���������� ������

    if (PlayerHUDWidget)
    {
        PlayerHUDWidget->AddToViewport();
        // AddToViewport() - ������� ���������, ���������� � �������. ����� ��������� �������/���� ���������
    }
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