// My Shoot Them Up Game , All Rights Reserved
// В STUAIBaseCharacter.cpp


#include "AI/STUAIBaseCharacter.h"
#include "AI/STUAIController.h"
#include "GameFramework/CharacterMovementComponent.h"


// конструктор класса с параметром т.к в базовом классе конструктор так же с параметром
ASTUAIBaseCharacter::ASTUAIBaseCharacter(const FObjectInitializer& ObjInit):Super(ObjInit)
{
	// настройка Details-> Pawn-> Auto Possess AI
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	//
	//   Disabled,
	//	PlacedInWorld,
	//	Spawned,
	//	PlacedInWorldOrSpawned

	// настройка Details-> Pawn-> AI Controller Class, переопределена в БП
	AIControllerClass = ASTUAIBaseCharacter::StaticClass();

	// для плавного поворота npc
	bUseControllerRotationYaw = false;

	if (GetCharacterMovement())
	{
		GetCharacterMovement()->bUseControllerDesiredRotation = true;

		GetCharacterMovement()->RotationRate = FRotator(0.0f, 200.0f, 0.0f);
	}

}