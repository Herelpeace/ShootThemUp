// My Shoot Them Up Game , All Rights Reserved
// В STUPlayerHUDWidget.cpp


#include "UI/STUPlayerHUDWidget.h"
#include "Components/STUHealthActorComponent.h"  
#include "Components/STUWeaponComponent.h"  


// функция для вызова в БП, возвращает текущее здоровье персонажа
float USTUPlayerHUDWidget::GetHealthPercent() const
{
	const auto HealthComponent = GetHealthComponent();

	if (!HealthComponent) return 0.0f;

	return HealthComponent->GetHealthPercent();

}


// функция для вызова в БП, возвращает структуру FWeaponUIDat содержащую иконки оружия и прицела
bool USTUPlayerHUDWidget::GetCurrentWeaponUIData(FWeaponUIData& UIData) const
{
	// получаем указатель на weaponComponent
	const auto WeaponComponent = GetWeaponComponent();

	if (!WeaponComponent) return false;

	return WeaponComponent->GetCurrentWeaponUIData(UIData);
}


bool USTUPlayerHUDWidget::GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const
{
	// получаем указатель на weaponComponent
	const auto WeaponComponent = GetWeaponComponent();

	if (!WeaponComponent) return false;

	return WeaponComponent->GetCurrentWeaponAmmoData(AmmoData);

}

USTUWeaponComponent* USTUPlayerHUDWidget::GetWeaponComponent() const
{
	// получаем указатель на нашего игрока
	const auto Player = GetOwningPlayerPawn();
	// GetOwningPlayerPawn() - функция возвращает указатель на Pawna, в виджетах

	if (!Player) return nullptr;

	// получаем указатель на компонент оружия
	const auto Component = Player->GetComponentByClass(USTUWeaponComponent::StaticClass());
	// GetComponentByClass                     - возвращает указатель на UActor компонет, принимает саб класс компонента который хотим найти
	// USTUWeaponComponent::StaticClass()      - т.к. WeaponComponent имеет только C++ версию, то используем данный способ                                                    

	// переводим указатель из UActor в указатель конкретного компонента
	const auto WeaponComponent = Cast<USTUWeaponComponent>(Component);
	// USTUWeaponComponent     - компонент указатель которого хотим получить
	// Component                - UActor компонент, данного компонента

	return WeaponComponent;
}

// общая функция получения HealthComponent
USTUHealthActorComponent* USTUPlayerHUDWidget::GetHealthComponent() const
{
	// получаем указатель на нашего игрока
	const auto Player = GetOwningPlayerPawn();
	// GetOwningPlayerPawn() - функция возвращает указатель на Pawna, в виджетах

	if (!Player) return nullptr;

	// получаем указатель на компонент оружия
	const auto Component = Player->GetComponentByClass(USTUHealthActorComponent::StaticClass());
	// GetComponentByClass                     - возвращает указатель на UActor компонет, принимает саб класс компонента который хотим найти
	// USTUWeaponComponent::StaticClass()      - т.к. WeaponComponent имеет только C++ версию, то используем данный способ                                                    

	// переводим указатель из UActor в указатель конкретного компонента
	const auto HealthComponent = Cast<USTUHealthActorComponent>(Component);
	// USTUHealthComponent      - компонент указатель которого хотим получить
	// Component                - UActor компонент, данного компонента

	return HealthComponent;

}


// true когда персонаж жив, для виджетов
bool USTUPlayerHUDWidget::IsPlayerAlive() const
{
	// получаем компонет здоровья charactera
	const auto HealthComponent = GetHealthComponent();

	return HealthComponent && !HealthComponent->isDead();
	// проверяем на null и вызываем метод IsDead, если он false значит пероснаж жив 
	// IsDead никогда не будет true потому что после гибели charactera контроллер перехватывает
	// управление Pawna
	// о том что здоровье персонажа равно 0 узнаем если HealthComponent = false

}

// true в режиме наблюдателя, для виджетов
bool USTUPlayerHUDWidget::IsPlayerSpectating() const
{
	// получение текущего контроллкра игрока в виджетах
	const auto Controller = GetOwningPlayer();

	return Controller && Controller->GetStateName() == NAME_Spectating;

	// в STUBaseCharacter после гибели персонажа мы меняем контроллер на NAME_Spectating (внтуренний unreal)
	// в данном случае проверяем является ли имя контроллера NAME_Spectating

}


