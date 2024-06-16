// My Shoot Them Up Game , All Rights Reserved
// В STUAmmoePickup.cpp


#include "Pickups/STUAmmoePickup.h"
#include "Components/STUHealthActorComponent.h"
#include "Components/STUWeaponComponent.h"
#include "STUUtils.h"

DEFINE_LOG_CATEGORY_STATIC(LogAmmoPickup, All ,All);

// для классов наследников
bool ASTUAmmoePickup::GivePickupTo(APawn* PlayerPawn)
{
	// шаблонная функция возвращает указатель на компонет (HealthComponent, WeaponComponent)
	// принимает указатель на Pawn
	const auto HealthComponent = STUUtils::GetSTPlayerComponent<USTUHealthActorComponent>(PlayerPawn);
	
	// если компонента нет или здоровье персонажа = 0, выходим
	if (!HealthComponent || HealthComponent->isDead()) return false;

	const auto WeaponComponent = STUUtils::GetSTPlayerComponent<USTUWeaponComponent>(PlayerPawn);

	if (!WeaponComponent) return false;

	// добавляем магазины
	return WeaponComponent->TryToAddAmmo(WeaponType, ClipsAmount);

}

