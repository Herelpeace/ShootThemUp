// My Shoot Them Up Game , All Rights Reserved
// В STUGameModeBase.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
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
	// в данной фнункции находится логика отрисовки
	void DrawCrossHair();	
};
