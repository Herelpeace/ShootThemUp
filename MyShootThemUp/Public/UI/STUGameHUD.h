// My Shoot Them Up Game , All Rights Reserved
// � STUGameModeBase.h

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
	// �������������� ������� HUD
	virtual void DrawHUD() override;

	private:
	// � ������ �������� ��������� ������ ���������
	void DrawCrossHair();

	
};
