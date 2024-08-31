// My Shoot Them Up Game , All Rights Reserved
// В STUPauseWidget.cpp


#include "UI/STUPauseWidget.h"
#include "GameFramework/GameModeBase.h"
#include "Components/Button.h"


// BeginPlay для виджетов
bool USTUPauseWidget::Initialize()
{
	// сохраняем значение которое возвращает родительская функция 
	const auto InitStatus = Super::Initialize();

	if (ClearPauseButton)
	{
		// биндим кнопку на делегат клика по кнопке, вызываем функцию OnClearPause()
		ClearPauseButton->OnClicked.AddDynamic(this, &USTUPauseWidget::OnClearPause);

		// возможные делегаты
		// ClearPauseButton->OnClicked  - при клике на кнопку
		// ClearPauseButton->OnHovered  - при наведенеии
		// ClearPauseButton->OnPressed  - при нажатии
		// ClearPauseButton->OnReleased - при отжатии
	}

	// возыращаем значение родительской функции 
	return InitStatus;
}


// функция для подписи на динамический делегат, при клике по кнопке CONTINUE
void USTUPauseWidget::OnClearPause()
{
	// проверка на мир и на GameMode
	if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

	// возвращает тики всем акторам, снимает паузу
	GetWorld()->GetAuthGameMode()->ClearPause();
}
