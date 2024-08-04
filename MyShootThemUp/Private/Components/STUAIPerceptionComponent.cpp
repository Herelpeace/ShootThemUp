// My Shoot Them Up Game , All Rights Reserved
// В STUAIPerceptionComponent.cpp


#include "Components/STUAIPerceptionComponent.h"
#include "AIController.h"
#include "STUUtils.h"
#include "Components/STUHealthActorComponent.h"
#include "Perception/AISenseConfig_Sight.h"



AActor* USTUAIPerceptionComponent::GetClossesEnemy() const
{
	TArray<AActor*> PercieveActors;  // массив в котором сохраняем акторов которых увидел персонаж

	// получает акторов которых увидел персонаж
	GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PercieveActors);
	// UAISense_Sight::StaticClass() - тип чувства
	// PercieveActors                - массив в который сохраняем акторов

	if (PercieveActors.Num() == 0) return nullptr;
	
	// получем владельца объекта, получаем контроллер который им владеет
	const auto Controller = Cast<AAIController>(GetOwner());

	if (!Controller) return nullptr;

	// через контроллер получаем персонаж (пешку) которым он владеет 
	const auto Pawn = Controller->GetPawn();

	if (!Pawn) return nullptr;

	float BestDistance = MAX_FLT;  // некоторое очень больше число 

	AActor* BestPawn = nullptr;

	for (const auto PecieveActor : PercieveActors)
	{
		// получаем компонент здоровья у акторов которые попали в поле видимости 
		const auto HealthComponent = STUUtils::GetSTPlayerComponent<USTUHealthActorComponent>(PecieveActor);

		// получаем Pawna
		const auto PercievePawn = Cast<APawn>(PecieveActor);

		// проверяем является ли врагом Pawn попавшмй в поле видимости
		const auto AreEnemies = PercievePawn && STUUtils::AreEnemies(Controller, PercievePawn->Controller);

		// у персонажа есть компонент хдоровья и здоровье не равно 0
		if (HealthComponent && !HealthComponent->isDead() && AreEnemies)
		{
			// получаем расстояние до наблючаемого актора
			const auto CurrentDistance = (PecieveActor->GetActorLocation() - Pawn->GetActorLocation()).Size();

			if (CurrentDistance < BestDistance)
			{
				BestDistance = CurrentDistance;
				BestPawn = PecieveActor;
			}
		}
	}

	return BestPawn;
}