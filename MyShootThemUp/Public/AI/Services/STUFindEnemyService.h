// My Shoot Them Up Game , All Rights Reserved
// В STUFindEnemyService.h

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "STUFindEnemyService.generated.h"


UCLASS()
class MYSHOOTTHEMUP_API USTUFindEnemyService : public UBTService
{
	GENERATED_BODY()

public:
	USTUFindEnemyService();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector EnemyActorKey;	// переменная селектора, ключ для вражеского персонажа 

	// функция Tick специально для Services, для поиска противника
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
