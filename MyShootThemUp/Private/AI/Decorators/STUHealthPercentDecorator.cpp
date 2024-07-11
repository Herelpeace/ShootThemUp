// My Shoot Them Up Game , All Rights Reserved
// � STUHealthPercentDecorator.cpp


#include "AI/Decorators/STUHealthPercentDecorator.h"
#include "AIController.h"
#include "STUUtils.h"
#include "Components/STUHealthActorComponent.h"

USTUHealthPercentDecorator::USTUHealthPercentDecorator()
{
	NodeName = "Health Percent";
}

bool USTUHealthPercentDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	// �������� ��������� �� ���������� 
	const auto Controller = OwnerComp.GetAIOwner();

	if (!Controller) return false;

	// �������� ��������� �������� 
	const auto HealthComponent = STUUtils::GetSTPlayerComponent<USTUHealthActorComponent>(Controller->GetPawn());

	// ���� �������� ����� ����
	if (!HealthComponent || HealthComponent->isDead()) return false;

	// ���������� true ���� ������� �������� ��������� ������ �������������� ���� ������
	return HealthComponent->GetHealthPercent() <= HealthPercent;

}