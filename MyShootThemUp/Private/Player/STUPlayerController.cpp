// My Shoot Them Up Game , All Rights Reserved


#include "Player/STUPlayerController.h"
#include "Components/STURespawnComponent.h"


ASTUPlayerController::ASTUPlayerController()
{

	// ������� ��� ��������� RespawnComponent
	RespawnComponent = CreateDefaultSubobject<USTURespawnComponent>("RespwnComponent");

}