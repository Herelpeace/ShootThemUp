// My Shoot Them Up Game , All Rights Reserved
// В STUPauseWidget.h

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
	// BeginPlay для виджетов
	virtual bool Initialize() override;

protected:
	UPROPERTY(meta = (BindWidget))  // ассоциирует кнопку из BP с кнопкой в C++
	UButton* ClearPauseButton;
	// UButton - класс кнопок
	// ClearPauseButton - точно такое же имя кнопки должно быть в БП в редакторе, иначе не найдет

private:
	// функция для подписи на динамический делегат, при клике по кнопке CONTINUE
	UFUNCTION()
	void OnClearPause();

	
};
