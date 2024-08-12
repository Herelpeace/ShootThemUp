// My Shoot Them Up Game , All Rights Reserved


#include "UI/STUSpectatorWidget.h"
#include "STUUtils.h"
#include "Components/STURespawnComponent.h"

// true если таймер запущен
// int32& CountDownTime - количество секунд до респавна
bool USTUSpectatorWidget::GetRespawnTime(int32& CountDownTime) const
{
	const auto RespawnComponent = STUUtils::GetSTPlayerComponent<USTURespawnComponent>(GetOwningPlayer());

	if (!RespawnComponent || !RespawnComponent->IsRespawnInProgress()) return false;

	CountDownTime = RespawnComponent->GetRespawnCountDown();
	return true;
}