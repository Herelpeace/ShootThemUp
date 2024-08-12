// My Shoot Them Up Game , All Rights Reserved
// STURespawnComponent.cpp


#include "Components/STURespawnComponent.h"
#include "STUGameModeBase.h"


USTURespawnComponent::USTURespawnComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}


// запускает таймер респавна через заданное время
void USTURespawnComponent::Respawn(int32 RespawnTime)
{
	if (!GetWorld()) return;

	RespawnCountDown = RespawnTime;

	GetWorld()->GetTimerManager().SetTimer(RespawnTimerHandle, this, &USTURespawnComponent::RespawnTimerUpdate, 1.0f, true);

}


// уменьшает время до респавна, запускает респавн
void USTURespawnComponent::RespawnTimerUpdate()
{
	if (--RespawnCountDown == 0)
	{
		if (!GetWorld()) return;

		// удаляем таймер
		GetWorld()->GetTimerManager().ClearTimer(RespawnTimerHandle);

		// получаем указатель на GameMode
		const auto GameMode = Cast<ASTUGameModeBase>(GetWorld()->GetAuthGameMode());

		if (!GameMode) return;

		// вызываем респавн
		GameMode->RespawnRequest(Cast<AController>(GetOwner()));
		// Cast<AController>(GetOwner())
		// У Component есть владелец, у владельца есть контроллер, вот этот контроллер передаем в функцию 


	}

}

// true - таймер запущен
bool USTURespawnComponent::IsRespawnInProgress() const
{
	return GetWorld() && GetWorld()->GetTimerManager().IsTimerActive(RespawnTimerHandle);
}

