// My Shoot Them Up Game , All Rights Reserved
// � STUGameHUD.h
// �������� ������� ��������� ����, Player, Pause, Game Over

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
	// �������������� ������� HUD
	virtual void DrawHUD() override;

protected:
	// ������ ����
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> PlayerHUDWidgetClass;
	// PlayerHUDWidgetClass - ���������� ���� UUserWidget, ���� ��������

	// ������ �����
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget>  PauseWidgetClass; 

	// ������ Game Over
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> GameOverWidgetClass;

	virtual void BeginPlay() override;

private:
	UPROPERTY()
	TMap<ESTUMatchState, UUserWidget*> GameWidgets;
	// TMap           - ������������� ������, � ��� ������ ��� �������
	// ESTUMatchState - ��� ����� (enum)
	// UUserWidget    - ��� �������� (widget)

	UPROPERTY()
		UUserWidget* CurrentWidget = nullptr;  // ������ ��������� �� ������� ������

	// � ������ ������� ��������� ������ ��������� �������
	void DrawCrossHair();	

	// Callback �������, ������� ����������� �� ������� ��������� ��������� ���� � BeginPlay
	void OnMatchStateChanged(ESTUMatchState State);

};
