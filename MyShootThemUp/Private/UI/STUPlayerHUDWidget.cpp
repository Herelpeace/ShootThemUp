// My Shoot Them Up Game , All Rights Reserved
// В STUPlayerHUDWidget.cpp


#include "UI/STUPlayerHUDWidget.h"
#include "Components/STUHealthActorComponent.h"  
#include "Components/STUWeaponComponent.h"  


// функция для вызова в БП, возвращает текущее здоровье персонажа
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


// функция для вызова в БП, возвращает структуру FWeaponUIDat содержащую иконки оружия и прицела
bool USTUPlayerHUDWidget::GetWeaponUIData(FWeaponUIData& UIData) const
{
	// получаем указатель на нашего игрока
	const auto Player = GetOwningPlayerPawn();
	// GetOwningPlayerPawn() - функция возвращает указатель на Pawna, в виджетах

	if (!Player) return false;

	// получаем указатель на компонент оружия
	const auto Component = Player->GetComponentByClass(USTUWeaponComponent::StaticClass());
	// GetComponentByClass                     - возвращает указатель на UActor компонет, принимает саб класс компонента который хотим найти
	// USTUWeaponComponent::StaticClass()      - т.к. WeaponComponent имеет только C++ версию, то используем данный способ                                                    

	// переводим указатель из UActor в указатель конкретного компонента
	const auto WeaponComponent = Cast<USTUWeaponComponent>(Component);
	// USTUWeaponComponent     - компонент указатель которого хотим получить
	// Component                - UActor компонент, данного компонента

	if (!WeaponComponent) return 0.0f;

	return WeaponComponent->GetWeaponUIData(UIData);
}

