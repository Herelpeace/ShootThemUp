// My Shoot Them Up Game , All Rights Reserved
// В STUHealthPercentDecorator.cpp


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
	// получаем указатель на контроллер 
	const auto Controller = OwnerComp.GetAIOwner();

	if (!Controller) return false;

	// получаем компонент здоровья 
	const auto HealthComponent = STUUtils::GetSTPlayerComponent<USTUHealthActorComponent>(Controller->GetPawn());

	// если здоровье равно нулю
	if (!HealthComponent || HealthComponent->isDead()) return false;

	// возвращаем true если процент здоровья персонажа меньше установленного нами порога
	return HealthComponent->GetHealthPercent() <= HealthPercent;

}