// My Shoot Them Up Game , All Rights Reserved
// сервис, задаем веро€тность смены оружи€ у npc
// ¬ STUChangeWeaponService.cpp



#include "AI/Services/STUChangeWeaponService.h"
#include "Components/STUWeaponComponent.h"
#include "AIController.h"
#include "STUUtils.h"
#include "BehaviorTree/BlackboardComponent.h"


USTUChangeWeaponService::USTUChangeWeaponService()
{
	NodeName = "Change Weapon";
}

void USTUChangeWeaponService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Controller = OwnerComp.GetAIOwner();

	if (Controller)
	{
		// получаем WeaponComponent
		const auto WeaponComponent = STUUtils::GetSTPlayerComponent<USTUWeaponComponent>(Controller->GetPawn());

		if (WeaponComponent && Probability > 0 && FMath::FRand() <= Probability)
		{
			WeaponComponent->NextWeapon();
		}
	}

	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

}