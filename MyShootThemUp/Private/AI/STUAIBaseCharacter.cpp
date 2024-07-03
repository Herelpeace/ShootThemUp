// My Shoot Them Up Game , All Rights Reserved
// � STUAIBaseCharacter.cpp


#include "AI/STUAIBaseCharacter.h"
#include "AI/STUAIController.h"
#include "GameFramework/CharacterMovementComponent.h"


// ����������� ������ � ���������� �.� � ������� ������ ����������� ��� �� � ����������
ASTUAIBaseCharacter::ASTUAIBaseCharacter(const FObjectInitializer& ObjInit):Super(ObjInit)
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