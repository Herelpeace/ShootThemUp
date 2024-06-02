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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite);
    FName MuzzleSocketName = "MuzzleSocket";   // имя сокета

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    float TraceMaxDistance = 1500.0f; // расстояние выстрела 1500 см = 15м



	virtual void MakeShot();

	// заполняем начальные и конечные координаты для рисуемой линии
	virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;

	virtual void BeginPlay() override;

	//функця возвращает указатель на контроллер текущего актора
	APlayerController* GetPlayerController() const;  

	// получаем Координаты и вращение камеры
	bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;

	// функция возвращает положение сокета
	FVector GetMuzzleWorldLocation() const;

	// получаем данные о пересечении (столкновении)
	void MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd); 

};
