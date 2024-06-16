// My Shoot Them Up Game , All Rights Reserved
// В STUAmmoePickup.h

#pragma once

#include "CoreMinimal.h"
#include "Pickups/STUBasePickup.h"
#include "STUAmmoePickup.generated.h"

class ASTUBaseWeapon;  // forward declaration т.к объявили переменную данного типа
UCLASS()
class MYSHOOTTHEMUP_API ASTUAmmoePickup : public ASTUBasePickup
{
	GENERATED_BODY()

protected:
	// количество магазинов которое можно взять, от 1 до 10
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup", meta = (ClampMin = "1.0", ClampMax = "10"))
	int32 ClipsAmount = 10;

	// к какому оружию добавляем магазины
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
		TSubclassOf<ASTUBaseWeapon> WeaponType; // переменная типа ASTUBaseWeapon


private:
	// для классов наследников
	virtual bool GivePickupTo(APawn* PlayerPawn) override;
	// true   - подобрали объект, false - объект не взят
	// APawn* - указатель на Pawn, через него полуачаем доступ к компонентам здоровья и оружия
	
};
