// My Shoot Them Up Game , All Rights Reserved
// � STUAIController.h

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
	ASTUAIController();		// ����������� ������


protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	USTUAIPerceptionComponent* STUAIPerceptionComponent;	// ��������� �� ��� Perception ���������, ����� ������������ � ��������� � STUAIController�

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	USTURespawnComponent* RespawnComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FName FocusOnKeyName = "EnemyActor";	// ��� ����� �� Object ���������� ��������� (�� ���� ��� ��������� �� �����)


	virtual void OnPossess(APawn* InPawn) override;

	virtual void Tick(float DeltaTime) override;

private:
	// ���������� ��������� �� actor �� ������� npc ����� ��������������� 
	AActor* GetFocusOnActor() const;

};
