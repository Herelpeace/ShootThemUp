// My Shoot Them Up Game , All Rights Reserved
// В STUHealthPickup.h

#pragma once

#include "CoreMinimal.h"
#include "Pickups/STUBasePickup.h"
#include "STUHealthPickup.generated.h"


UCLASS()
class MYSHOOTTHEMUP_API ASTUHealthPickup : public ASTUBasePickup
{
	GENERATED_BODY()
private:
	// для классов наследников
	virtual bool GivePickupTo(APawn* PlayerPawn) override;
	// true   - подобрали объект, false - объект не взят
	// APawn* - указатель на Pawn, через него полуачаем доступ к компонентам здоровья и оружия
	
};
