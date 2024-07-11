// My Shoot Them Up Game , All Rights Reserved
// � STUNeedAmmoDecorator.cpp


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
	// �������� ����������
	const auto Controller = OwnerComp.GetAIOwner();

	if (!Controller) return false;

	// �������� ��������� ������ 
	const auto WeaponComponent = STUUtils::GetSTPlayerComponent<USTUWeaponComponent>(Controller->GetPawn());

	if (!WeaponComponent) return false;

	// � weaponComponent �������� ����� ������� NeedAmmo(WeaponType);
	return WeaponComponent->NeedAmmo(WeaponType);

}


