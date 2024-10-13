// My Shoot Them Up Game , All Rights Reserved
// В STUPlayerStatRowWidget.h

/*
*  Скрипт для виджета строки статистики выводимой в GameOver
*/

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUPlayerStatRowWidget.generated.h"

//forward declaration блоков из виджетов
class UImage;       // класс картинки
class UTextBlock;	// текстовый блок

UCLASS()
class MYSHOOTTHEMUP_API USTUPlayerStatRowWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// функции для установки значений каждой переменной виджета
	void SetPlayerName(const FText& Text);
	void SetKills(const FText& Text);
	void SetDeaths(const FText& Text);
	void SetTeam(const FText& Text);
	void SetPlayerIndicatorVisibility(bool Visible);


protected:
	// переременные которые будут выводится в виджете
	UPROPERTY(meta = (BindWidget))
	UTextBlock* PlayerNameTextBlock;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* KillsTextBlock;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* DeathsTextBlock;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TeamTextBlock;

	UPROPERTY(meta = (BindWidget))
	UImage* PlayerIndicatorImage;

	
};
