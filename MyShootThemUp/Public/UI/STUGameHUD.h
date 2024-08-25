// My Shoot Them Up Game , All Rights Reserved
// � STUGameHUD.h

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
	// �������������� ������� HUD
	virtual void DrawHUD() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> PlayerHUDWidgetClass;
	// PlayerHUDWidgetClass - ���������� ���� UUserWidget, ���� ��������


	virtual void BeginPlay() override;

private:
	// � ������ ������� ��������� ������ ���������
	void DrawCrossHair();	

	// Callback �������, ������� ����������� �� ������� ��������� ��������� ���� � BeginPlay
	void OnMatchStateChanged(ESTUMatchState State);

};
