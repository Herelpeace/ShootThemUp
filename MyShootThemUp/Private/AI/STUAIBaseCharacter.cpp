// My Shoot Them Up Game , All Rights Reserved
// � STUAIBaseCharacter.cpp


#include "AI/STUAIBaseCharacter.h"
#include "AI/STUAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/STUAIWeaponComponent.h"
#include "BrainComponent.h"


// ����������� ������ � ���������� �.� � ������� ������ ����������� ��� �� � ����������
ASTUAIBaseCharacter::ASTUAIBaseCharacter(const FObjectInitializer& ObjInit) :Super(ObjInit.SetDefaultSubobjectClass<USTUAIWeaponComponent>("WeaponComponent"))
{
	// ��������� Details-> Pawn-> Auto Possess AI
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	//
	//   Disabled,
	//	PlacedInWorld,
	//	Spawned,
	//	PlacedInWorldOrSpawned

	// ��������� Details-> Pawn-> AI Controller Class, �������������� � ��
	AIControllerClass = ASTUAIBaseCharacter::StaticClass();

	// ��� �������� �������� npc
	bUseControllerRotationYaw = false;

	if (GetCharacterMovement())
	{
		GetCharacterMovement()->bUseControllerDesiredRotation = true;

		GetCharacterMovement()->RotationRate = FRotator(0.0f, 200.0f, 0.0f);
	}
}

// �������������� ������� OnDeath() �������� ������ 
void ASTUAIBaseCharacter::OnDeath()
{
	Super::OnDeath();

	// �������� AIController � ������ Charactera
	const auto STUController = Cast<AAIController>(Controller);

	// �������� ��� � ����������� ���� BrainComponent
	if (STUController && STUController->BrainComponent)
	{
		// ������������� ������ ���������
		STUController->BrainComponent->Cleanup();
	}

}