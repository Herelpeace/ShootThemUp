// My Shoot Them Up Game , All Rights Reserved
// � STUAIPerceptionComponent.h

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionComponent.h"
#include "STUAIPerceptionComponent.generated.h"


UCLASS()
class MYSHOOTTHEMUP_API USTUAIPerceptionComponent : public UAIPerceptionComponent
{
	GENERATED_BODY()
public:
	// ���������� ��������� �� ������ ������� ������ ��� ���������
	AActor* GetClossesEnemy() const;
};
