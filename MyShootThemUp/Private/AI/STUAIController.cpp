// My Shoot Them Up Game , All Rights Reserved
// � STUAIController.cpp


#include "AI/STUAIController.h"
#include "AI/STUAIBaseCharacter.h"
#include "Components/STUAIPerceptionComponent.h"


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

void ASTUAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// �������� ������ � ���� ���������
	const auto AimActor = STUAIPerceptionComponent->GetClossesEnemy();

	// forward ������ ������ ������������ �� ������ ������� ������� � �������� ��������� 
	SetFocus(AimActor);

}
