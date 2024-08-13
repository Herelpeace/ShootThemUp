// My Shoot Them Up Game , All Rights Reserved
// В STUPlayerHUDWidget.cpp


#include "UI/STUPlayerHUDWidget.h"
#include "Components/STUHealthActorComponent.h"  
#include "Components/STUWeaponComponent.h" 
#include "STUUtils.h"

// подписываемся на делегат смены Pawna GetOnNewPawnNotifier
// функция Initialize() вызывается один раз во время старта игры 
bool USTUPlayerHUDWidget::Initialize()
{
	if (GetOwningPlayer())
	{
		// подписываемся на делегат смены Pawna GetOnNewPawnNotifier
		GetOwningPlayer()->GetOnNewPawnNotifier().AddUObject(this, &USTUPlayerHUDWidget::OnNewPawn);
		
		// так как функция OnPosses вызывается до Initialize() то мы не сможем забиндится на делегат 
		// нам нужно вызывать функцию OnNewPawn первый раз принудительно
		OnNewPawn(GetOwningPlayerPawn());
	}
	return Super::Initialize();
}

// для бинда на делегат контроллера GetOnNewPawnNotifier
// вызывается при смене Pawna
// подписываемся на делегат OnHealthChanged (float Health)
void USTUPlayerHUDWidget::OnNewPawn(APawn* NewPawn)
{
	// получаем указатель на копонент здоровья Pawna при помощи шаблонной функции
	const auto HealthComponent = STUUtils::GetSTPlayerComponent<USTUHealthActorComponent>(NewPawn);

	// делаем бинд на делегат OnHealthChanged только в том случае если он еще не забинден
	if (HealthComponent && !HealthComponent->OnHealthChanged.IsBoundToObject(this) )
	{
		//HealthComponent->OnHealthChanged.IsBoundToObject(this) - проверяет что существует bind делегата для данного объекта, что функция забиндена на делегат
		
		// подписались на делегат OnHealthChanged у HealthComponentа
		HealthComponent->OnHealthChanged.AddUObject(this, &USTUPlayerHUDWidget::OnHealthChanged);
	}
}


// для бинда на делегат Health компонента, функция которая будет вызывана
// принимаеиые параметры она получит из события broadcast делегата OnHealthChanged в HealthComponente
void USTUPlayerHUDWidget::OnHealthChanged(float Health, float HealthDelta)
{
	if (HealthDelta < 0.0f)
	{
		OnTakeDamage();
		// функция Event которую будем вызывать в БП
		// тело функции создавать ненужно
	}
}


// функция для вызова в БП, возвращает текущее здоровье персонажа
float USTUPlayerHUDWidget::GetHealthPercent() const
{
	const auto HealthComponent = STUUtils::GetSTPlayerComponent<USTUHealthActorComponent>(GetOwningPlayerPawn());
	// получаем указатель на копонент здоровья Pawna при помощи шаблонной функции

	if (!HealthComponent) return 0.0f;

	return HealthComponent->GetHealthPercent();

}


// функция для вызова в БП, возвращает структуру FWeaponUIDat содержащую иконки оружия и прицела
bool USTUPlayerHUDWidget::GetCurrentWeaponUIData(FWeaponUIData& UIData) const
{
	const auto WeaponComponent = STUUtils::GetSTPlayerComponent<USTUWeaponComponent>(GetOwningPlayerPawn());
	// получаем указатель на копонент WeaponComponent Pawna при помощи шаблонной функции

	if (!WeaponComponent) return false;

	return WeaponComponent->GetCurrentWeaponUIData(UIData);
}


bool USTUPlayerHUDWidget::GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const
{
	const auto WeaponComponent = STUUtils::GetSTPlayerComponent<USTUWeaponComponent>(GetOwningPlayerPawn());
	// получаем указатель на копонент WeaponComponent Pawna при помощи шаблонной функции

	if (!WeaponComponent) return false;

	return WeaponComponent->GetCurrentWeaponAmmoData(AmmoData);

}


// true когда персонаж жив, для виджетов
bool USTUPlayerHUDWidget::IsPlayerAlive() const
{
	const auto HealthComponent = STUUtils::GetSTPlayerComponent<USTUHealthActorComponent>(GetOwningPlayerPawn());
	// получаем указатель на копонент здоровья Pawna при помощи шаблонной функции

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


