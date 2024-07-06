// My Shoot Them Up Game , All Rights Reserved
// В STUNextLocationTask.h

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "STUNextLocationTask.generated.h"

/**
 * 
 */
UCLASS()
class MYSHOOTTHEMUP_API USTUNextLocationTask : public UBTTaskNode
{
	GENERATED_BODY()

public:
	// конструктор класса
	USTUNextLocationTask(); 

	// функция вызывается когда начинается выполнение Таска, генерирует случайню точку вокруг персонажа и записывает значение в Blackboard
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")   // отобразится в редакторе, можно менять
	float Radius = 1000.0f;		// радиус вокруг персонажа в котором ищем рандомную точку

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector AimLocation;		// переменная структуры blackboard в которую записываем найденую точку
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	bool SelfCenter = true;		// искать рандомную точку относительно себя или относительно другого актора

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (EditCondition = "!SelfCenter"))
	FBlackboardKeySelector CenterActorKey;		// ключ для объекта относительно которого находим рандомную точку
};


