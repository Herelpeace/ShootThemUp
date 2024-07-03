// My Shoot Them Up Game , All Rights Reserved
// � STUAIController.cpp


#include "AI/STUAIController.h"
#include "AI/STUAIBaseCharacter.h"

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


