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

	// запускает таймер респавна через заданное время
	void Respawn(int32 RespawnTime);

	// получаем количество секунд респавна
	int32 GetRespawnCountDown() const { return RespawnCountDown; }

	// true - таймер запущен
	bool IsRespawnInProgress() const;

private:
	// дискриптор таймера
	FTimerHandle RespawnTimerHandle;

	// время оставшееся до респавна
	int32 RespawnCountDown = 0;

	// уменьшает время до респавна, запускает респавн
	void RespawnTimerUpdate();
			
};
