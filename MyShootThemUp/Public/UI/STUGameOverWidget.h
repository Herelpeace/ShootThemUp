// My Shoot Them Up Game , All Rights Reserved
// ¬ STUGameOverWidget.h

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUCoreType.h"					// дл€ Enum MatchState
#include "STUGameOverWidget.generated.h"

class UVerticalBox;		// объект VerticalBox в виджетах, базовый класс

UCLASS()
class MYSHOOTTHEMUP_API USTUGameOverWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual bool Initialize() override;

protected:
	UPROPERTY(meta = (BindWidget))
	UVerticalBox* PlayerStatBox;										// в него помещаем строки статистики

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> PlayerStatRowWidgetClass;					// класс виджета одной строки статистики, на основе него создаем остальные строки 

private:
	void OnMatchStateChanged(ESTUMatchState State);			// изменение состо€ни€ игры
	void UpdatePlayerStat();								// создает таблицу статистики
	
	

};
