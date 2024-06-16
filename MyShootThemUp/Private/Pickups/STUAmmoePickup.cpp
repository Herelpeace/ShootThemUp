// My Shoot Them Up Game , All Rights Reserved
// � STUAmmoePickup.cpp


#include "Pickups/STUAmmoePickup.h"
#include "Components/STUHealthActorComponent.h"
#include "Components/STUWeaponComponent.h"
#include "STUUtils.h"

DEFINE_LOG_CATEGORY_STATIC(LogAmmoPickup, All ,All);

// ��� ������� �����������
bool ASTUAmmoePickup::GivePickupTo(APawn* PlayerPawn)
{
	// ��������� ������� ���������� ��������� �� �������� (HealthComponent, WeaponComponent)
	// ��������� ��������� �� Pawn
	const auto HealthComponent = STUUtils::GetSTPlayerComponent<USTUHealthActorComponent>(PlayerPawn);
	
	// ���� ���������� ��� ��� �������� ��������� = 0, �������
	if (!HealthComponent || HealthComponent->isDead()) return false;

	const auto WeaponComponent = STUUtils::GetSTPlayerComponent<USTUWeaponComponent>(PlayerPawn);

	if (!WeaponComponent) return false;

	// ��������� ��������
	return WeaponComponent->TryToAddAmmo(WeaponType, ClipsAmount);

}

