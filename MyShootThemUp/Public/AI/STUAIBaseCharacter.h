// My Shoot Them Up Game , All Rights Reserved
// � STUAIBaseCharacter.h

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
	// ����������� ������ � ���������� �.� � ������� ������ ����������� ��� �� � ����������
	ASTUAIBaseCharacter(const FObjectInitializer& ObjInit );

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
	UBehaviorTree* BehaviorTreeAsset;		// ��� ��������� BehaviorTree ������

protected:
	virtual void OnDeath() override;



};
