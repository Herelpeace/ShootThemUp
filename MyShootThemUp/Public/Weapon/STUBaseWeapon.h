// My Shoot Them Up Game , All Rights Reserved
// В STUBaseWeapon.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUBaseWeapon.generated.h"



class USkeletalMeshComponent; // Forward declaration

UCLASS()
class MYSHOOTTHEMUP_API ASTUBaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	ASTUBaseWeapon();

	// делаем виртуальной т.к. для разных оружий (наследников) будем переопределять свою функцию 
	virtual	void StartFire(); // старт стрельба из оружия 
	virtual	void StopFire();  // стоп стрельба из оружия 

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
    USkeletalMeshComponent* WeaponMesh;        // переменная для Mesh оружия

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite);
    FName MuzzleSocketName = "MuzzleSocket";   // имя сокета

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    float TraceMaxDistance = 1500.0f; // расстояние выстрела 1500 см = 15м

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float DamageAmount = 10.0f;       // Damage наносимый актору

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float TimeBetweenShots = 0.1f;    // время между выстрелами

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float BulletSpread = 1.5f;        // половина угла конуса разброса при выстрелах (полный угол = умножить на 2)

	void MakeShot();

	virtual void BeginPlay() override;

	//функця возвращает указатель на контроллер текущего актора
	APlayerController* GetPlayerController() const;  

	// получаем Координаты и вращение камеры
	bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;

	// функция возвращает положение сокета
	FVector GetMuzzleWorldLocation() const;

	// заполняем начальные и конечные координаты для рисуемой линии
	bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;

	// получаем данные о пересечении (столкновении)
	void MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd); 

	// нанесение урона Damage, актору
	void MakeDamage(FHitResult& HitResult);


private:

	// переменная для таймера
	FTimerHandle ShotTimerHandle;

};
