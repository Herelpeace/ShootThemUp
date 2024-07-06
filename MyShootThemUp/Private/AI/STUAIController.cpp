// My Shoot Them Up Game , All Rights Reserved
// � STUAIController.cpp


#include "AI/STUAIController.h"
#include "AI/STUAIBaseCharacter.h"
#include "Components/STUAIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"  // ���������


ASTUAIController::ASTUAIController()
{
	// ������� ��������� �� ������ ������ ���������� -  PerceptionComponent
	STUAIPerceptionComponent = CreateDefaultSubobject<USTUAIPerceptionComponent>("STUPerceptionComponent");

	// ������������� ��� ���������, ����������� �� ���������. ��������� ������ �� ���������
	SetPerceptionComponent(*STUAIPerceptionComponent);
}


void ASTUAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	// ����� Pawn �������� Charactera 
	const auto STUCharacter = Cast<ASTUAIBaseCharacter>(InPawn);


	if (STUCharacter)
	{
		// ��������� ������ ���������, ��������� ��������� �� ������ ���������
		RunBehaviorTree(STUCharacter->BehaviorTreeAsset);
	}

}

// ������ ��� �������������� �� ������ � ���� ���������
void ASTUAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// �������� ������ � ���� ���������
	const auto AimActor = GetFocusOnActor();

	// forward ������ ������ ������������ �� ������ ������� ������� � �������� ��������� 
	SetFocus(AimActor);

}

// ���������� ��������� �� actor �� ������� npc ����� ���������������
AActor* ASTUAIController::GetFocusOnActor() const
{
	if (!GetBlackboardComponent()) return nullptr;

	// ����� ��� ���������� � Blackboard �������� Object �������� ������ �� ������
	return Cast<AActor> ( GetBlackboardComponent()->GetValueAsObject(FocusOnKeyName));
	// GetBlackboardComponent()->GetValueAsObject(FocusOnKeyName) - ���������� ��������� �� ������� ��� UObject
	// ������� ������ ��� �� ������ 

}