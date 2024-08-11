// My Shoot Them Up Game , All Rights Reserved


#include "Player/STUPlayerController.h"
#include "Components/STURespawnComponent.h"


ASTUPlayerController::ASTUPlayerController()
{

	// создаем наш компонент RespawnComponent
	RespawnComponent = CreateDefaultSubobject<USTURespawnComponent>("RespwnComponent");

}