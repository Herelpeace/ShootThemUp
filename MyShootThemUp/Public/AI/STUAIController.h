// My Shoot Them Up Game , All Rights Reserved
// В STUAIController.h

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "STUAIController.generated.h"

class USTUAIPerceptionComponent;

UCLASS()
class MYSHOOTTHEMUP_API ASTUAIController : public AAIController
{
	GENERATED_BODY()

public:
	ASTUAIController();		// конструктор класса


protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	USTUAIPerceptionComponent* STUAIPerceptionComponent;	// указатель на наш Perception компонент, будет отображаться в редакторе у STUAIControllerа

	virtual void OnPossess(APawn* InPawn) override;

	virtual void Tick(float DeltaTime) override;

};
