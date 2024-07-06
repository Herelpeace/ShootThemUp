// My Shoot Them Up Game , All Rights Reserved
// � STUNextLocationTask.h

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
	// ����������� ������
	USTUNextLocationTask(); 

	// ������� ���������� ����� ���������� ���������� �����, ���������� �������� ����� ������ ��������� � ���������� �������� � Blackboard
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")   // ����������� � ���������, ����� ������
	float Radius = 1000.0f;		// ������ ������ ��������� � ������� ���� ��������� �����

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector AimLocation;		// ���������� ��������� blackboard � ������� ���������� �������� �����
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	bool SelfCenter = true;		// ������ ��������� ����� ������������ ���� ��� ������������ ������� ������

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (EditCondition = "!SelfCenter"))
	FBlackboardKeySelector CenterActorKey;		// ���� ��� ������� ������������ �������� ������� ��������� �����
};


