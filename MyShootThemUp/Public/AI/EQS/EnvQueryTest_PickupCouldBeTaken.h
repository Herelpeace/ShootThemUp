// My Shoot Them Up Game , All Rights Reserved
// В EnvQueryTest_PickupCouldBeTaken.h

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "EnvQueryTest_PickupCouldBeTaken.generated.h"


UCLASS()
class MYSHOOTTHEMUP_API UEnvQueryTest_PickupCouldBeTaken : public UEnvQueryTest
{
	GENERATED_BODY()

public:
	// конструктор
	UEnvQueryTest_PickupCouldBeTaken(const FObjectInitializer& ObjectInitializer);

	// запускается при вызове EQS 
	virtual void RunTest(FEnvQueryInstance& QueryInstance) const override;
	
};
