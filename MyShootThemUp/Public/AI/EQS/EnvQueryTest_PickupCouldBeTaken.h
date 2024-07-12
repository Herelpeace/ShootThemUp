// My Shoot Them Up Game , All Rights Reserved
// � EnvQueryTest_PickupCouldBeTaken.h

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "EnvQueryTest_PickupCouldBeTaken.generated.h"


UCLASS()
class MYSHOOTTHEMUP_API UEnvQueryTest_PickupCouldBeTaken : public UEnvQueryTest
{
	GENERATED_BODY()

public:
	// �����������
	UEnvQueryTest_PickupCouldBeTaken(const FObjectInitializer& ObjectInitializer);

	// ����������� ��� ������ EQS 
	virtual void RunTest(FEnvQueryInstance& QueryInstance) const override;
	
};
