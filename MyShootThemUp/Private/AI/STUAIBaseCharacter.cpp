// My Shoot Them Up Game , All Rights Reserved
// � ASTUAIBaseCharacter.cpp


#include "AI/STUAIBaseCharacter.h"

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
}