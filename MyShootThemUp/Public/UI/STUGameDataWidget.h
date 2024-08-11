// My Shoot Them Up Game , All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUGameDataWidget.generated.h"

class ASTUGameModeBase;
class ASTUPlayerState;

UCLASS()
class MYSHOOTTHEMUP_API USTUGameDataWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	// ���������� ������
	int32 GetKillsNum() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	// ������� �����
	int32 GetCurrentRoundNm() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	// ����� ���������� �������
	int32 GetTotalRoundsNum() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	// ���������� ������ �� ����� ������
	int32 GetRoundSecondsRemaining() const;

private:
	ASTUGameModeBase* GetSTUGameMode() const;
	ASTUPlayerState* GetSTUPlayerState() const;
};
