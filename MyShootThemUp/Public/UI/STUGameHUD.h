// My Shoot Them Up Game , All Rights Reserved
// В STUGameHUD.h
// Содержит виджеты состояний игры, Player, Pause, Game Over

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "STUCoreType.h"
#include "STUGameHUD.generated.h"


UCLASS()
class MYSHOOTTHEMUP_API ASTUGameHUD : public AHUD
{
	GENERATED_BODY()

	public:	
	// переопредилили функцию HUD
	virtual void DrawHUD() override;

protected:
	// виджет игры
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> PlayerHUDWidgetClass;
	// PlayerHUDWidgetClass - переменная типа UUserWidget, всех виджетов

	// виджет паузы
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget>  PauseWidgetClass; 

	// виджет Game Over
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> GameOverWidgetClass;

	virtual void BeginPlay() override;

private:
	UPROPERTY()
	TMap<ESTUMatchState, UUserWidget*> GameWidgets;
	// TMap           - ассоциотивный массив, в нем храним все виджеты
	// ESTUMatchState - тип ключа (enum)
	// UUserWidget    - тип значения (widget)

	UPROPERTY()
		UUserWidget* CurrentWidget = nullptr;  // хранит указатель на текущий виджет

	// в данной функции находится логика отрисовки прицела
	void DrawCrossHair();	

	// Callback функция, которую подписываем на делегат изменения состояния игры в BeginPlay
	void OnMatchStateChanged(ESTUMatchState State);

};
