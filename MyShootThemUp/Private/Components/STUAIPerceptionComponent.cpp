// My Shoot Them Up Game , All Rights Reserved
// � STUAIPerceptionComponent.cpp


#include "Components/STUAIPerceptionComponent.h"
#include "AIController.h"
#include "STUUtils.h"
#include "Components/STUHealthActorComponent.h"
#include "Perception/AISenseConfig_Sight.h"



AActor* USTUAIPerceptionComponent::GetClossesEnemy() const
{
	TArray<AActor*> PercieveActors;  // ������ � ������� ��������� ������� ������� ������ ��������

	// �������� ������� ������� ������ ��������
	GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PercieveActors);
	// UAISense_Sight::StaticClass() - ��� �������
	// PercieveActors                - ������ � ������� ��������� �������

	if (PercieveActors.Num() == 0) return nullptr;
	
	// ������� ��������� �������, �������� ���������� ������� �� �������
	const auto Controller = Cast<AAIController>(GetOwner());

	if (!Controller) return nullptr;

	// ����� ���������� �������� �������� (�����) ������� �� ������� 
	const auto Pawn = Controller->GetPawn();

	if (!Pawn) return nullptr;

	float BestDistance = MAX_FLT;  // ��������� ����� ������ ����� 

	AActor* BestPawn = nullptr;

	for (const auto PecieveActor : PercieveActors)
	{
		// �������� ��������� �������� � ������� ������� ������ � ���� ��������� 
		const auto HealthComponent = STUUtils::GetSTPlayerComponent<USTUHealthActorComponent>(PecieveActor);

		// �������� Pawna
		const auto PercievePawn = Cast<APawn>(PecieveActor);

		// ��������� �������� �� ������ Pawn �������� � ���� ���������
		const auto AreEnemies = PercievePawn && STUUtils::AreEnemies(Controller, PercievePawn->Controller);

		// � ��������� ���� ��������� �������� � �������� �� ����� 0
		if (HealthComponent && !HealthComponent->isDead() && AreEnemies)
		{
			// �������� ���������� �� ������������ ������
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