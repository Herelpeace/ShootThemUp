// My Shoot Them Up Game , All Rights Reserved
// В STURifleWeapon.h

#pragma once

#include "CoreMinimal.h"
#include "Weapon/STUBaseWeapon.h"
#include "STURifleWeapon.generated.h"

/**
 * 
 */
UCLASS()
class MYSHOOTTHEMUP_API ASTURifleWeapon : public ASTUBaseWeapon
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float TimeBetweenShots = 0.1f;    // время между выстрелами

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float BulletSpread = 1.5f;        // половина угла конуса разброса при выстрелах (полный угол = умножить на 2)

	virtual	void StartFire() override;  // переопределяем старт стрельба из оружия 
	virtual	void StopFire()  override;  // переопределяем стоп стрельба из оружия 

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float DamageAmount = 10.0f;       // Damage наносимый актору

	virtual void MakeShot() override;  // переопределяем функция логики стрельбы

	// заполняем начальные и конечные координаты для рисуемой линии
	virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const override;

private:
	// переменная для таймера
	FTimerHandle ShotTimerHandle;

	// нанесение урона Damage, актору
	void MakeDamage(FHitResult& HitResult);
	
};
