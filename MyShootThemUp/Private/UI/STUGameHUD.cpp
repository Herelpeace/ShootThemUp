// My Shoot Them Up Game , All Rights Reserved
// В STUGameModeBase.cpp



#include "UI/STUGameHUD.h"
#include "Engine/Canvas.h"  // для получения размеров экрана, в нем происходит отрисовка 

void ASTUGameHUD::DrawHUD() 
{
    // так как функция переопределена, вызываем родительскую функцию через Super
    Super::DrawHUD();

    // функция в которой находится логика отрисовки
    DrawCrossHair(); 

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