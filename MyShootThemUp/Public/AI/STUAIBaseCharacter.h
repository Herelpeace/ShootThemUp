// My Shoot Them Up Game , All Rights Reserved
// В ASTUAIBaseCharacter.h

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
	// конструктор класса с параметром т.к в базовом классе конструктор так же с параметром
	ASTUAIBaseCharacter(const FObjectInitializer& ObjInit );
};
