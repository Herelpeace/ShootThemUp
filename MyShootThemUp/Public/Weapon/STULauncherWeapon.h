// My Shoot Them Up Game , All Rights Reserved
// В STULauncherWeapon.h

#pragma once

#include "CoreMinimal.h"
#include "Weapon/STUBaseWeapon.h"
#include "STULauncherWeapon.generated.h"

class ASTUProjectile;  // forward declaration

UCLASS()
class MYSHOOTTHEMUP_API ASTULauncherWeapon : public ASTUBaseWeapon
{
	GENERATED_BODY()

public:
	virtual	void StartFire() override;  // переопределяем старт стрельба из оружия 
	//virtual	void StopFire()  override;  // переопределяем стоп стрельба из оружия 

protected:
	// класс ракеты который будем спавнить при выстреле Launchera
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<ASTUProjectile> ProjectileClass;  // создали переменную STUProjectile класс
	                                              // позволяют из списка выбирать нужный БП

	virtual void MakeShot() override;  // переопределяем функция логики стрельбы
	
};
