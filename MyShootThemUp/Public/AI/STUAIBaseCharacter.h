// My Shoot Them Up Game , All Rights Reserved
// В STUAIBaseCharacter.h

#pragma once

#include "CoreMinimal.h"
#include "Player/STUBaseCharacter.h"
#include "STUAIBaseCharacter.generated.h"

class UBehaviorTree;

UCLASS()
class MYSHOOTTHEMUP_API ASTUAIBaseCharacter : public ASTUBaseCharacter
{
	GENERATED_BODY()
	
public:
	// конструктор класса с параметром т.к в базовом классе конструктор так же с параметром
	ASTUAIBaseCharacter(const FObjectInitializer& ObjInit );

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
	UBehaviorTree* BehaviorTreeAsset;		// для установки BehaviorTree ассета

protected:
	virtual void OnDeath() override;



};
