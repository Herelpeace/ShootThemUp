// My Shoot Them Up Game , All Rights Reserved
// � STUAmmoePickup.cpp


#include "Pickups/STUAmmoePickup.h"

DEFINE_LOG_CATEGORY_STATIC(LogAmmoPickup, All ,All);

// ��� ������� �����������
bool ASTUAmmoePickup::GivePickupTo(APawn* Playerpawn)
{
	UE_LOG(LogAmmoPickup, Warning, TEXT(" Ammo was taken"));
	return true;

}

