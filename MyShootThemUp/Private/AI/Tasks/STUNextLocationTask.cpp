// My Shoot Them Up Game , All Rights Reserved
// � STUNextLocationTask.cpp


#include "AI/Tasks/STUNextLocationTask.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "NavigationSystem.h"


USTUNextLocationTask::USTUNextLocationTask()
{
	NodeName = "Next Location";   
	// ���������� NodeName ���� � ������� �����, �� �������� ��������� � ��������� - ��� ����� ���� � ������
}

// ������� ���������� ����� ���������� ���������� �����, ���������� �������� ����� ������ ��������� � ���������� �������� � Blackboard
EBTNodeResult::Type USTUNextLocationTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	// �������� ��������� �� AI ���������� NPC
	const auto Controller = OwnerComp.GetAIOwner();

	// �������� ��������� �� ������� ����� ���������� 
	const auto Blackboard = OwnerComp.GetBlackboardComponent();

	// �������� ����������
	if (!Controller || !Blackboard) return EBTNodeResult::Failed;
	// ������� ������ ������� ���� �� enum
	// Succeeded,	// finished as success
	// Failed,	    // finished as failure
	// Aborted,	    // finished aborting = failure
	// InProgress,	// not finished yet

	// �������� ��������� �� PAwn
	const auto Pawn = Controller->GetPawn();

	if(!Pawn) return EBTNodeResult::Failed;

	// ��������� �� ������� Navigation System
	const auto NavSys = UNavigationSystemV1::GetCurrent(Pawn);

	if (!NavSys) return EBTNodeResult::Failed;

	FNavLocation NavLocation;                  // ���������� � ������� ��������� ����� ��������� ����������
	auto Location = Pawn->GetActorLocation();  // ���������� Pawna 
	if (!SelfCenter)
	{
		// �������� �������� ���������� ���� Object �� Blackboard
		auto CenterActor = Cast<AActor>(Blackboard->GetValueAsObject(CenterActorKey.SelectedKeyName));
		// Blackboard->GetValueAsObject() - ���������� �������� ������� � Blackboard, ��������� ��� �������
		// CenterActorKey.SelectedKeyName - ������ ������� ������ � Blackboard

		if(!CenterActor) return EBTNodeResult::Failed;

		Location = CenterActor->GetActorLocation();
	}


	// �������� ��������� ���������� ������ �������, NPC ������ ������ � ��� ��������� �.�. ��� �������� ����� ������� ���������
	const auto Found = NavSys->GetRandomReachablePointInRadius (Location, Radius, NavLocation );
	// Pawn->GetActorLocation() - ����� ������������ ������� ������ ������ ������ ��������� �����
	// Radius                   - ������ ������
	// NavLocation              - ���������� ���� FNavLocation, � ������� ��������� ���������� 

	if(!Found) return EBTNodeResult::Failed;

	// ���������� ���������� � ���������� �� Blackboard
	Blackboard->SetValueAsVector( AimLocation.SelectedKeyName, NavLocation.Location );
	// AimLocationKey       - ���������� �������� � blackboard, � ������� ���������� �������� �����
	// NavLocation.Location - ������ � ������������

	return EBTNodeResult::Succeeded;
}