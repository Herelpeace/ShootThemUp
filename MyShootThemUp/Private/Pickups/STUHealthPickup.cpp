// My Shoot Them Up Game , All Rights Reserved
// � STUHealthPickup.cpp


#include "Pickups/STUHealthPickup.h"
#include "STUHealthActorComponent.h"
#include "STUUtils.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthPickup, All, All);

// ��� ������� �����������
bool ASTUHealthPickup::GivePickupTo(APawn* PlayerPawn)
{
	// ��������� ������� ���������� ��������� �� �������� ��������� (HealthComponent, WeaponComponent)
    // ��������� ��������� �� Pawn
	const auto HealthComponent = STUUtils::GetSTPlayerComponent<USTUHealthActorComponent>(PlayerPawn);

	if (!HealthComponent) return false;

	return HealthComponent->TryToAddHealth(HealthAmount);
}

