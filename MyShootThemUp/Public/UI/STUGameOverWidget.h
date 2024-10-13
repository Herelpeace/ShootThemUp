// My Shoot Them Up Game , All Rights Reserved
// � STUGameOverWidget.h

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUCoreType.h"					// ��� Enum MatchState
#include "STUGameOverWidget.generated.h"

class UVerticalBox;		// ������ VerticalBox � ��������, ������� �����

UCLASS()
class MYSHOOTTHEMUP_API USTUGameOverWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual bool Initialize() override;

protected:
	UPROPERTY(meta = (BindWidget))
	UVerticalBox* PlayerStatBox;										// � ���� �������� ������ ����������

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> PlayerStatRowWidgetClass;					// ����� ������� ����� ������ ����������, �� ������ ���� ������� ��������� ������ 

private:
	void OnMatchStateChanged(ESTUMatchState State);			// ��������� ��������� ����
	void UpdatePlayerStat();								// ������� ������� ����������
	
	

};
