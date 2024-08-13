// My Shoot Them Up Game , All Rights Reserved
// STURespawnComponent.h

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STURespawnComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYSHOOTTHEMUP_API USTURespawnComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USTURespawnComponent();

	// ��������� ������ �������� ����� �������� �����
	void Respawn(int32 RespawnTime);

	// �������� ���������� ������ ��������
	int32 GetRespawnCountDown() const { return RespawnCountDown; }

	// true - ������ �������
	bool IsRespawnInProgress() const;

private:
	// ���������� �������
	FTimerHandle RespawnTimerHandle;

	// ����� ���������� �� ��������
	int32 RespawnCountDown = 0;

	// ��������� ����� �� ��������, ��������� �������
	void RespawnTimerUpdate();
			
};