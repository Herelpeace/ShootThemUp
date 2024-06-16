// My Shoot Them Up Game , All Rights Reserved
// В STUHealthPickup.cpp


#include "Pickups/STUHealthPickup.h"
#include "STUHealthActorComponent.h"
#include "STUUtils.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthPickup, All, All);

// для классов наследников
bool ASTUHealthPickup::GivePickupTo(APawn* PlayerPawn)
{
	// шаблонная функция возвращает указатель на компонет персонажа (HealthComponent, WeaponComponent)
    // принимает указатель на Pawn
	const auto HealthComponent = STUUtils::GetSTPlayerComponent<USTUHealthActorComponent>(PlayerPawn);

	if (!HealthComponent) return false;

	return HealthComponent->TryToAddHealth(HealthAmount);
}

