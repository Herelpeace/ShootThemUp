// My Shoot Them Up Game , All Rights Reserved
// В STUNextLocationTask.cpp


#include "AI/Tasks/STUNextLocationTask.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "NavigationSystem.h"


USTUNextLocationTask::USTUNextLocationTask()
{
	NodeName = "Next Location";   
	// переменная NodeName есть в базовом кассе, ее значение выводится в редакторе - имя нашей ноды с таском
}

// функция вызывается когда начинается выполнение Таска, генерирует случайню точку вокруг персонажа и записывает значение в Blackboard
EBTNodeResult::Type USTUNextLocationTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	// получаем указатель на AI контроллер NPC
	const auto Controller = OwnerComp.GetAIOwner();

	// получаем указатель на текущую доску переменных 
	const auto Blackboard = OwnerComp.GetBlackboardComponent();

	// проверка указателей
	if (!Controller || !Blackboard) return EBTNodeResult::Failed;
	// функция должна вернуть один из enum
	// Succeeded,	// finished as success
	// Failed,	    // finished as failure
	// Aborted,	    // finished aborting = failure
	// InProgress,	// not finished yet

	// получаем указатель на PAwn
	const auto Pawn = Controller->GetPawn();

	if(!Pawn) return EBTNodeResult::Failed;

	// указатель на текущую Navigation System
	const auto NavSys = UNavigationSystemV1::GetCurrent(Pawn);

	if (!NavSys) return EBTNodeResult::Failed;

	FNavLocation NavLocation;                  // переменная в которую навигатор будет сохранять координаты
	auto Location = Pawn->GetActorLocation();  // координаты Pawna 
	if (!SelfCenter)
	{
		// получаем значение переменной типа Object из Blackboard
		auto CenterActor = Cast<AActor>(Blackboard->GetValueAsObject(CenterActorKey.SelectedKeyName));
		// Blackboard->GetValueAsObject() - возвращает значение объекта в Blackboard, принимает имя объекта
		// CenterActorKey.SelectedKeyName - объект который задаем в Blackboard

		if(!CenterActor) return EBTNodeResult::Failed;

		Location = CenterActor->GetActorLocation();
	}


	// получаем рандомные координаты внутри радиуса, NPC всегда сможет к ним добраться т.к. они получены через систему навигации
	const auto Found = NavSys->GetRandomReachablePointInRadius (Location, Radius, NavLocation );
	// Pawn->GetActorLocation() - точка относительно которой строим радиус поиска рандомной точки
	// Radius                   - радиус поиска
	// NavLocation              - переменная типа FNavLocation, в которую сохраняем координаты 

	if(!Found) return EBTNodeResult::Failed;

	// записываем координаты в переменную из Blackboard
	Blackboard->SetValueAsVector( AimLocation.SelectedKeyName, NavLocation.Location );
	// AimLocationKey       - переменная хранимая в blackboard, в которую записываем найденую точку
	// NavLocation.Location - вектор с координатами

	return EBTNodeResult::Succeeded;
}