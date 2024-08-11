// My Shoot Them Up Game , All Rights Reserved
// В STUAIController.h

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "STUAIController.generated.h"

class USTUAIPerceptionComponent;
class USTURespawnComponent;

UCLASS()
class MYSHOOTTHEMUP_API ASTUAIController : public AAIController
{
	GENERATED_BODY()

public:
	ASTUAIController();		// конструктор класса


protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	USTUAIPerceptionComponent* STUAIPerceptionComponent;	// указатель на наш Perception компонент, будет отображаться в редакторе у STUAIControllerа

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	USTURespawnComponent* RespawnComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FName FocusOnKeyName = "EnemyActor";	// имя ключа на Object вражеского персонажа (по сути имя указателя на врага)


	virtual void OnPossess(APawn* InPawn) override;

	virtual void Tick(float DeltaTime) override;

private:
	// возвращает указатель на actor на котором npc нужно сфокусироваться 
	AActor* GetFocusOnActor() const;

};
