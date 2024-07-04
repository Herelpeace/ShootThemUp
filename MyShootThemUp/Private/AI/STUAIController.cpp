// My Shoot Them Up Game , All Rights Reserved
// ¬ STUAIController.cpp


#include "AI/STUAIController.h"
#include "AI/STUAIBaseCharacter.h"
#include "Components/STUAIPerceptionComponent.h"


ASTUAIController::ASTUAIController()
{
	// создали компонент из нашего класса компонента -  PerceptionComponent
	STUAIPerceptionComponent = CreateDefaultSubobject<USTUAIPerceptionComponent>("STUPerceptionComponent");

	// устанавливаем наш компонент, компонентом по умолчанию. принимает ссылку на компонент
	SetPerceptionComponent(*STUAIPerceptionComponent);
}


void ASTUAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	// через Pawn получаем Charactera 
	const auto STUCharacter = Cast<ASTUAIBaseCharacter>(InPawn);


	if (STUCharacter)
	{
		// запускаем дерево поведени€, принимает указатель на дерево поведени€
		RunBehaviorTree(STUCharacter->BehaviorTreeAsset);
	}

}

void ASTUAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// получаем актора в зоне видимости
	const auto AimActor = STUAIPerceptionComponent->GetClossesEnemy();

	// forward вектор актора поворачивает на объект который передем в качестве параметра 
	SetFocus(AimActor);

}
