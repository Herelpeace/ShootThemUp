// My Shoot Them Up Game , All Rights Reserved
// В ASTUAIBaseCharacter.cpp


#include "AI/STUAIBaseCharacter.h"

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
}