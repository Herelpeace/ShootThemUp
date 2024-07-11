// My Shoot Them Up Game , All Rights Reserved
// ¬ STUHealthPercentDecorator.h

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "STUHealthPercentDecorator.generated.h"


UCLASS()
class MYSHOOTTHEMUP_API USTUHealthPercentDecorator : public UBTDecorator
{
	GENERATED_BODY()

public:
	USTUHealthPercentDecorator();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float HealthPercent = 0.6f;   // (установили 60%) допустимый процент здоровь€, если оно меньше то декоратор возвращает true 

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	
};
