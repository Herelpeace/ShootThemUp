// My Shoot Them Up Game , All Rights Reserved
// В STUAIController.cpp


#include "AI/STUAIController.h"
#include "AI/STUAIBaseCharacter.h"
#include "Components/STUAIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"  // подключен


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
		// запускаем дерево поведения, принимает указатель на дерево поведения
		RunBehaviorTree(STUCharacter->BehaviorTreeAsset);
	}

}

// каждый тик поворачиваемся на актора в зоне видимости
void ASTUAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// получаем актора в зоне видимости
	const auto AimActor = GetFocusOnActor();

	// forward вектор актора поворачивает на объект который передем в качестве параметра 
	SetFocus(AimActor);

}

// возвращает указатель на actor на котором npc нужно сфокусироваться
AActor* ASTUAIController::GetFocusOnActor() const
{
	if (!GetBlackboardComponent()) return nullptr;

	// через имя переменной в Blackboard получаем Object которого кастим до актора
	return Cast<AActor> ( GetBlackboardComponent()->GetValueAsObject(FocusOnKeyName));
	// GetBlackboardComponent()->GetValueAsObject(FocusOnKeyName) - возвращает указатель на базовый тип UObject
	// поэтому кастим его до актора 

}