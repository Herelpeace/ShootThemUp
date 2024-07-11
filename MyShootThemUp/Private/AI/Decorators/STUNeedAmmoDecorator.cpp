// My Shoot Them Up Game , All Rights Reserved
// В STUNeedAmmoDecorator.cpp


#include "AI/Decorators/STUNeedAmmoDecorator.h"
#include "STUUtils.h"
#include "AIController.h"
#include "Components/STUWeaponComponent.h"


USTUNeedAmmoDecorator::USTUNeedAmmoDecorator()
{
	NodeName = "Need Ammo";
}

bool USTUNeedAmmoDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	// получаем контроллер
	const auto Controller = OwnerComp.GetAIOwner();

	if (!Controller) return false;

	// получаем компонент оружия 
	const auto WeaponComponent = STUUtils::GetSTPlayerComponent<USTUWeaponComponent>(Controller->GetPawn());

	if (!WeaponComponent) return false;

	// в weaponComponent вызываем новую функцию NeedAmmo(WeaponType);
	return WeaponComponent->NeedAmmo(WeaponType);

}


