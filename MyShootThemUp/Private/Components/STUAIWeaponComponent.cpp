// My Shoot Them Up Game , All Rights Reserved
// смена оружия если нет патронов, наследник от STUWeaponComponent
// В STUAIWeaponComponent.cpp



#include "Components/STUAIWeaponComponent.h"
#include "STUBaseWeapon.h"


// старт стрельба мышкой
void USTUAIWeaponComponent::StartFire()
{
	if (!CanFire()) return;

	// если нет патронов меняем оружие в противном случае стреляем
	if (CurrentWeapon->IsAmmoEmpty())
	{
		NextWeapon();
	}
	else
	{
		CurrentWeapon->StartFire();
	}

}

// при смене оружия
void USTUAIWeaponComponent::NextWeapon()
{
	// вернет true когда можно менять оружие
	if (!CanEquip()) return;

	// берем следующий элемент массива по модулую к величине массива чтобы не выйти за его пределы
	int32 NextIndex = (CurrentWeaponIndex + 1) % Weapons.Num();

	while (NextIndex != CurrentWeaponIndex)
	{
		if (!Weapons[NextIndex]->IsAmmoEmpty()) break;
		NextIndex = (NextIndex+1) % Weapons.Num();
	}

	// если нашли орудие с патронами, меняем текущее оружие на него 
	if (CurrentWeaponIndex != NextIndex)
	{
		CurrentWeaponIndex = NextIndex;
		EquipWeapon(CurrentWeaponIndex);
	}

}