// My Shoot Them Up Game , All Rights Reserved
// В STUPlayerHUDWidget.cpp


#include "UI/STUPlayerHUDWidget.h"
#include "Components/STUHealthActorComponent.h"  

float USTUPlayerHUDWidget::GetHealthPercent() const
{
	// получаем указатель на нашего игрока
	const auto Player = GetOwningPlayerPawn();
	// GetOwningPlayerPawn() - функция возвращает указатель на Pawna, в виджетах

	if (!Player) return 0.0f;

	// получаем указатель на компонент здоровья, Health Component
	const auto Component = Player->GetComponentByClass(USTUHealthActorComponent::StaticClass());
	// GetComponentByClass                     - возвращает указатель на UActor компонет, принимает саб класс компонента который хотим найти
	// USTUHealthActorComponent::StaticClass() - т.к. Health Component имеет только C++ версию, то используем данный способ                                                    

	// переводим указатель из UActor в указатель конкретного компонента
	const auto HealthComponent = Cast<USTUHealthActorComponent>(Component);
	// USTUHealthActorComponent - компонент указатель которого хотим получить
	// Component                - UActor компонент, данного компонента

	if (!HealthComponent) return 0.0f;

	return HealthComponent->GetHealthPercent();

}

