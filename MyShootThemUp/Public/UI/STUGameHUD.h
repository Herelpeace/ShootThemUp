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

	private:
	// в данной фнункции находится логика отрисовки
	void DrawCrossHair();

	
};
