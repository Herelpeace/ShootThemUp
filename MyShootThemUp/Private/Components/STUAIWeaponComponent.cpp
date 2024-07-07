// My Shoot Them Up Game , All Rights Reserved
// ����� ������ ���� ��� ��������, ��������� �� STUWeaponComponent
// � STUAIWeaponComponent.cpp



#include "Components/STUAIWeaponComponent.h"
#include "STUBaseWeapon.h"


// ����� �������� ������
void USTUAIWeaponComponent::StartFire()
{
	if (!CanFire()) return;

	// ���� ��� �������� ������ ������ � ��������� ������ ��������
	if (CurrentWeapon->IsAmmoEmpty())
	{
		NextWeapon();
	}
	else
	{
		CurrentWeapon->StartFire();
	}

}

// ��� ����� ������
void USTUAIWeaponComponent::NextWeapon()
{
	// ������ true ����� ����� ������ ������
	if (!CanEquip()) return;

	// ����� ��������� ������� ������� �� ������� � �������� ������� ����� �� ����� �� ��� �������
	int32 NextIndex = (CurrentWeaponIndex + 1) % Weapons.Num();

	while (NextIndex != CurrentWeaponIndex)
	{
		if (!Weapons[NextIndex]->IsAmmoEmpty()) break;
		NextIndex = (NextIndex+1) % Weapons.Num();
	}

	// ���� ����� ������ � ���������, ������ ������� ������ �� ���� 
	if (CurrentWeaponIndex != NextIndex)
	{
		CurrentWeaponIndex = NextIndex;
		EquipWeapon(CurrentWeaponIndex);
	}

}