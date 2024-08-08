// My Shoot Them Up Game , All Rights Reserved
// В STURifleWeapon.h

#pragma once

#include "CoreMinimal.h"
#include "Weapon/STUBaseWeapon.h"
#include "STURifleWeapon.generated.h"

class USTUWeaponFXComponent;
class UNiagaraSystem;
class UNiagaraComponent;



UCLASS()
class MYSHOOTTHEMUP_API ASTURifleWeapon : public ASTUBaseWeapon
{
	GENERATED_BODY()

public:
	ASTURifleWeapon(); // конструктор класса, нужен для компонета USTUWeaponFXComponent

	virtual void BeginPlay() override;  // переопределяем функцию BeginPlay, для Check компонента WeaponFXComponent
	virtual	void StartFire() override;  // переопределяем старт стрельба из оружия 
	virtual	void StopFire()  override;  // переопределяем стоп стрельба из оружия 

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float TimeBetweenShots = 0.1f;    // время между выстрелами

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float BulletSpread = 1.5f;        // половина угла конуса разброса при выстрелах (полный угол = умножить на 2)

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float DamageAmount = 10.0f;       // Damage наносимый актору

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	UNiagaraSystem* TraceFX;          // 'эффект трассировки

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	FString TraceTargetName = "TraceTarget";	// название переменной с конечной точкой эффекта

	UPROPERTY(VisibleAnywhere, Category = "VFX") // создается раздел VFX в котором появляются поля заданные в USTUWeaponFXComponent
	USTUWeaponFXComponent* WeaponFXComponent;     // выбираем FX в редакторе БП винтовки

	virtual void MakeShot() override;  // переопределяем функция логики стрельбы

	// заполняем начальные и конечные координаты для рисуемой линии
	virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const override;

private:
	// переменная для таймера
	FTimerHandle ShotTimerHandle;

	UPROPERTY()
	UNiagaraComponent* MuzzleFXComponent;

	// нанесение урона Damage, актору
	void MakeDamage(FHitResult& HitResult);
	
	// спавнит niagara system
	void InitMuzzleFX();

	// устанавливает видимость эффекта
	void SetMuzzleFXVisibility(bool Visibility);

	// спавн эффекта трассировки
	void SpawnTraceFX(const FVector& TraceStart, const FVector& TraceEnd);

	// получаем текущий контроллер (для статистики)
	AController* GetController() const;
	

};
