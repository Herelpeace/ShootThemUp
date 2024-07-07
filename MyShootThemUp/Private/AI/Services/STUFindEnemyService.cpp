 
// Tem Up Game , All Rights Reserved
// ������, ���� ���������� � ������� ��� � ���������� Blackboarda
// � STUFindEnemyService.cpp



#include "AI/Services/STUFindEnemyService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "STUUtils.h"
#include "Components/STUAIPerceptionComponent.h"


USTUFindEnemyService::USTUFindEnemyService()
{
	NodeName = "Find Enemy";	// ��� ���� ������� ����� � ��������� 
}


// ������� Tick ���������� ��� Services, ��� ������ ����������
void USTUFindEnemyService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	// �������� Blackboard
	const auto Blackboard = OwnerComp.GetBlackboardComponent();

	if (Blackboard)
	{
		// �������� ���������� 
		const auto Controller = OwnerComp.GetAIOwner();

		// �������� ��� ����� USTUAIPerceptionComponent
		const auto PerceptionComponent = STUUtils::GetSTPlayerComponent<USTUAIPerceptionComponent>(Controller);

		if (PerceptionComponent)
		{
			// ���������� �������� � ���������� EnemyActor � Blackboard
			Blackboard->SetValueAsObject(EnemyActorKey.SelectedKeyName, PerceptionComponent->GetClossesEnemy() );
			// EnemyActorKey.SelectedKeyName - (��� ���������� � Blackboard) ���������� ���������, ���� ��� ���������� ��������� 
			// PerceptionComponent->GetClossesEnemy() - (������ ������� ���������� � ����������) � ������ ������ � ��� Object ���������� 
			//                                          ���������� ��������� �� Object �����.
			//                                          ���������� ��������� �� ������� ����� ������ ������� �������� UObject 
		}
	}

	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}