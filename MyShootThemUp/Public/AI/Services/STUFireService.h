// My Shoot Them Up Game , All Rights Reserved
// В STUFireService.h

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "STUFireService.generated.h"

UCLASS()
class MYSHOOTTHEMUP_API USTUFireService : public UBTService
{
	GENERATED_BODY()

public:
	USTUFireService();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector EnemyActorKey;	// ключ с вражеским актором

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};
