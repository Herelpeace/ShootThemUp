// My Shoot Them Up Game , All Rights Reserved
// В STUAIController.cpp


#include "AI/STUAIController.h"
#include "AI/STUAIBaseCharacter.h"

void ASTUAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	// через Pawn получаем Charactera 
	const auto STUCharacter = Cast<ASTUAIBaseCharacter>(InPawn);


	if (STUCharacter)
	{
		// запускаем дерево поведения, принимает указатель на дерево поведения
		RunBehaviorTree(STUCharacter->BehaviorTreeAsset);
	}

}


