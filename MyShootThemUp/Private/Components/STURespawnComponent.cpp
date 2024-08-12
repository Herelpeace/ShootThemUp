// My Shoot Them Up Game , All Rights Reserved
// STURespawnComponent.cpp


#include "Components/STURespawnComponent.h"
#include "STUGameModeBase.h"


USTURespawnComponent::USTURespawnComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}


// ��������� ������ �������� ����� �������� �����
void USTURespawnComponent::Respawn(int32 RespawnTime)
{
	if (!GetWorld()) return;

	RespawnCountDown = RespawnTime;

	GetWorld()->GetTimerManager().SetTimer(RespawnTimerHandle, this, &USTURespawnComponent::RespawnTimerUpdate, 1.0f, true);

}


// ��������� ����� �� ��������, ��������� �������
void USTURespawnComponent::RespawnTimerUpdate()
{
	if (--RespawnCountDown == 0)
	{
		if (!GetWorld()) return;

		// ������� ������
		GetWorld()->GetTimerManager().ClearTimer(RespawnTimerHandle);

		// �������� ��������� �� GameMode
		const auto GameMode = Cast<ASTUGameModeBase>(GetWorld()->GetAuthGameMode());

		if (!GameMode) return;

		// �������� �������
		GameMode->RespawnRequest(Cast<AController>(GetOwner()));
		// Cast<AController>(GetOwner())
		// � Component ���� ��������, � ��������� ���� ����������, ��� ���� ���������� �������� � ������� 


	}

}

// true - ������ �������
bool USTURespawnComponent::IsRespawnInProgress() const
{
	return GetWorld() && GetWorld()->GetTimerManager().IsTimerActive(RespawnTimerHandle);
}

