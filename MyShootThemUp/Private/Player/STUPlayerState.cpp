// My Shoot Them Up Game , All Rights Reserved
// � STUPlayerState.cpp


#include "Player/STUPlayerState.h"

DEFINE_LOG_CATEGORY_STATIC(LogSTUPlayerState, All, All);

	// ������� ������ ���������� � �������
void ASTUPlayerState::LogInfo()
{
	UE_LOG(LogSTUPlayerState,Warning, TEXT("TeamID: %i, Kills: %i, Death: %i"), TeamID, KillsNum, DeathNum);


}