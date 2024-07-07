// My Shoot Them Up Game , All Rights Reserved
// ¬ STUAIBaseCharacter.cpp


#include "AI/STUAIBaseCharacter.h"
#include "AI/STUAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/STUAIWeaponComponent.h"
#include "BrainComponent.h"


// конструктор класса с параметром т.к в базовом классе конструктор так же с параметром
ASTUAIBaseCharacter::ASTUAIBaseCharacter(const FObjectInitializer& ObjInit) :Super(ObjInit.SetDefaultSubobjectClass<USTUAIWeaponComponent>("WeaponComponent"))
{
	// настройка Details-> Pawn-> Auto Possess AI
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	//
	//   Disabled,
	//	PlacedInWorld,
	//	Spawned,
	//	PlacedInWorldOrSpawned

	// настройка Details-> Pawn-> AI Controller Class, переопределена в Ѕѕ
	AIControllerClass = ASTUAIBaseCharacter::StaticClass();

	// дл€ плавного поворота npc
	bUseControllerRotationYaw = false;

	if (GetCharacterMovement())
	{
		GetCharacterMovement()->bUseControllerDesiredRotation = true;

		GetCharacterMovement()->RotationRate = FRotator(0.0f, 200.0f, 0.0f);
	}
}

// переопредел€ем функцию OnDeath() базового класса 
void ASTUAIBaseCharacter::OnDeath()
{
	Super::OnDeath();

	// получаем AIController в классе Charactera
	const auto STUController = Cast<AAIController>(Controller);

	// проверка что у контроллера есть BrainComponent
	if (STUController && STUController->BrainComponent)
	{
		// останавливаем дерево поведени€
		STUController->BrainComponent->Cleanup();
	}

}