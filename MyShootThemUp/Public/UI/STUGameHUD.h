// My Shoot Them Up Game , All Rights Reserved
// В STUGameHUD.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "STUCoreType.h"
#include "STUGameHUD.generated.h"

/**
 * 
 */
UCLASS()
class MYSHOOTTHEMUP_API ASTUGameHUD : public AHUD
{
	GENERATED_BODY()

	public:	
	// переопредилили функцию HUD
	virtual void DrawHUD() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> PlayerHUDWidgetClass;
	// PlayerHUDWidgetClass - переменная типа UUserWidget, всех виджетов


	virtual void BeginPlay() override;

private:
	// в данной функции находится логика отрисовки
	void DrawCrossHair();	

	// Callback функция, которую подписываем на делегат изменения состояния игры в BeginPlay
	void OnMatchStateChanged(ESTUMatchState State);

};
