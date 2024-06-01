// My Shoot Them Up Game , All Rights Reserved
// ¬ STUBaseWeapon.h

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

	// делаем виртуальной т.к. дл€ разных оружий (наследников) будем переопредел€ть свою функцию 
	virtual	void StartFire(); // старт стрельба из оружи€ 
	virtual	void StopFire();  // стоп стрельба из оружи€ 

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
    USkeletalMeshComponent* WeaponMesh;        // переменна€ дл€ Mesh оружи€

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite);
    FName MuzzleSocketName = "MuzzleSocket";   // им€ сокета

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    float TraceMaxDistance = 1500.0f; // рассто€ние выстрела 1500 см = 15м

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float DamageAmount = 10.0f;       // Damage наносимый актору

	virtual void MakeShot();

	// заполн€ем начальные и конечные координаты дл€ рисуемой линии
	virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;

	virtual void BeginPlay() override;

	//функц€ возвращает указатель на контроллер текущего актора
	APlayerController* GetPlayerController() const;  

	// получаем  оординаты и вращение камеры
	bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;

	// функци€ возвращает положение сокета
	FVector GetMuzzleWorldLocation() const;

	// получаем данные о пересечении (столкновении)
	void MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd); 

	// нанесение урона Damage, актору
	void MakeDamage(FHitResult& HitResult);




};
