// My Shoot Them Up Game , All Rights Reserved
// В STUHealthPickup.cpp


#include "Pickups/STUHealthPickup.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthPickup, All, All);

// для классов наследников
bool ASTUHealthPickup::GivePickupTo(APawn* PlayerPawn)
{
	UE_LOG(LogHealthPickup, Warning, TEXT(" Health was taken"));
	return true;
}

