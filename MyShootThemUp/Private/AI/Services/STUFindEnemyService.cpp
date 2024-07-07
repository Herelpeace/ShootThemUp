 
// Tem Up Game , All Rights Reserved
// сервис, ищем противника и заносим его в переменную Blackboarda
// В STUFindEnemyService.cpp



#include "AI/Services/STUFindEnemyService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "STUUtils.h"
#include "Components/STUAIPerceptionComponent.h"


USTUFindEnemyService::USTUFindEnemyService()
{
	NodeName = "Find Enemy";	// имя узла который будет в редакторе 
}


// функция Tick специально для Services, для поиска противника
void USTUFindEnemyService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	// получили Blackboard
	const auto Blackboard = OwnerComp.GetBlackboardComponent();

	if (Blackboard)
	{
		// получаем контроллер 
		const auto Controller = OwnerComp.GetAIOwner();

		// получаем наш класс USTUAIPerceptionComponent
		const auto PerceptionComponent = STUUtils::GetSTPlayerComponent<USTUAIPerceptionComponent>(Controller);

		if (PerceptionComponent)
		{
			// записываем значение в переменную EnemyActor у Blackboard
			Blackboard->SetValueAsObject(EnemyActorKey.SelectedKeyName, PerceptionComponent->GetClossesEnemy() );
			// EnemyActorKey.SelectedKeyName - (имя переменной у Blackboard) переменная селектора, ключ для вражеского персонажа 
			// PerceptionComponent->GetClossesEnemy() - (данные которые записываем в переменную) в данном случае у нас Object переменная 
			//                                          записываем указатель на Object класс.
			//                                          записываем указатель на базовый класс актора который является UObject 
		}
	}

	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}