// My Shoot Them Up Game , All Rights Reserved
// � ASTUAIBaseCharacter.h

#pragma once

#include "CoreMinimal.h"
#include "Player/STUBaseCharacter.h"
#include "STUAIBaseCharacter.generated.h"

/**
 * 
 */
UCLASS()
class MYSHOOTTHEMUP_API ASTUAIBaseCharacter : public ASTUBaseCharacter
{
	GENERATED_BODY()
	
public:
	// ����������� ������ � ���������� �.� � ������� ������ ����������� ��� �� � ����������
	ASTUAIBaseCharacter(const FObjectInitializer& ObjInit );
};
