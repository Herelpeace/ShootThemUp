// My Shoot Them Up Game , All Rights Reserved
// В STUFireService.cpp


#include "AI/Services/STUFireService.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/STUWeaponComponent.h"
#include "STUUtils.h"


USTUFireService::USTUFireService()
{
	NodeName = "Fire";
}

void USTUFireService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Controller = OwnerComp.GetAIOwner();
	const auto Blackboard = OwnerComp.GetBlackboardComponent();

	// проверка стоит ли npc стрелять 
	const auto HasAim = Blackboard && Blackboard->GetValueAsObject(EnemyActorKey.SelectedKeyName);

	if (Controller)
	{
		// получаем Wepaon компонент через Pawn который кастим до WeaponComponent
		const auto WeaponComponent = STUUtils::GetSTPlayerComponent<USTUWeaponComponent>(Controller->GetPawn());

		if (WeaponComponent)
		{
			// как только появится враг, будем стрелять 
			HasAim ? WeaponComponent->StartFire() : WeaponComponent->StopFire();
		}
	}

	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}