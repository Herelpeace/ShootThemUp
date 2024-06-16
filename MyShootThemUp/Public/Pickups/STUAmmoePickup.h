// My Shoot Them Up Game , All Rights Reserved
// В STUAmmoePickup.h

#pragma once

#include "CoreMinimal.h"
#include "Pickups/STUBasePickup.h"
#include "STUAmmoePickup.generated.h"

/**
 * 
 */
UCLASS()
class MYSHOOTTHEMUP_API ASTUAmmoePickup : public ASTUBasePickup
{
	GENERATED_BODY()

private:
	// для классов наследников
	virtual bool GivePickupTo(APawn* Playerpawn) override;
	// true   - подобрали объект, false - объект не взят
	// APawn* - указатель на Pawn, через него полуачаем доступ к компонентам здоровья и оружия
	
};
