// My Shoot Them Up Game , All Rights Reserved
// � STUPauseWidget.h

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUPauseWidget.generated.h"


class UButton;

UCLASS()
class MYSHOOTTHEMUP_API USTUPauseWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// BeginPlay ��� ��������
	virtual bool Initialize() override;

protected:
	UPROPERTY(meta = (BindWidget))  // ����������� ������ �� BP � ������� � C++
	UButton* ClearPauseButton;
	// UButton - ����� ������
	// ClearPauseButton - ����� ����� �� ��� ������ ������ ���� � �� � ���������, ����� �� ������

private:
	// ������� ��� ������� �� ������������ �������, ��� ����� �� ������ CONTINUE
	UFUNCTION()
	void OnClearPause();

	
};
