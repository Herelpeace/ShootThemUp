// My Shoot Them Up Game , All Rights Reserved
// ¬ STURifleWeapon.h

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
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float TimeBetweenShots = 0.1f;    // врем€ между выстрелами

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float BulletSpread = 1.5f;        // половина угла конуса разброса при выстрелах (полный угол = умножить на 2)

	virtual	void StartFire() override;  // переопредел€ем старт стрельба из оружи€ 
	virtual	void StopFire()  override;  // переопредел€ем стоп стрельба из оружи€ 

protected:
	virtual void MakeShot() override;  // переопредел€ем функци€ логики стрельбы

	// заполн€ем начальные и конечные координаты дл€ рисуемой линии
	virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const override;

private:
	// переменна€ дл€ таймера
	FTimerHandle ShotTimerHandle;

	
};
