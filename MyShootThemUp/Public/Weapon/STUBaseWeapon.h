// My Shoot Them Up Game , All Rights Reserved
// В STUBaseWeapon.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUBaseWeapon.generated.h"

// делегат оповещает WeaponComponent о том что закончились патроны
DECLARE_MULTICAST_DELEGATE(FOnClipEmptySignature)


class USkeletalMeshComponent; // Forward declaration

// структура в которой храним количество патронов в магазине
USTRUCT(BlueprintType)
struct FAmmoData
{
	GENERATED_USTRUCT_BODY()

		// количество патронов в магазине, количество через которое перезаряжаемся
		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
		int32 Bullets;

		// количество магазинов у текущего оружия, количество перезарядок
	    // доступно для редактирования когда Infinite = false, т.е число магазинов ограничено
		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon", meta = (EditCondition = "!Infinite"))
		int32 Clips;

		// конечное число магазинов или нет
		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
		bool Infinite;
};


UCLASS()
class MYSHOOTTHEMUP_API ASTUBaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	ASTUBaseWeapon();

	// объект делегата, оповещает WeaponComponent о том что закончились патроны
	FOnClipEmptySignature OnClipEmpty;

	// делаем виртуальной т.к. для разных оружий (наследников) будем переопределять свою функцию 
	virtual	void StartFire(); // старт стрельба из оружия 
	virtual	void StopFire();  // стоп стрельба из оружия 
	void ChangeClip();        // меняет магазин на новый, WeaponComponent вызывает функцию если нужна перезарядка

	bool CanReload() const;  // можно ли делать перезарядку

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
    USkeletalMeshComponent* WeaponMesh;        // переменная для Mesh оружия

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite);
    FName MuzzleSocketName = "MuzzleSocket";   // имя сокета

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    float TraceMaxDistance = 1500.0f; // расстояние выстрела 1500 см = 15м

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	FAmmoData DefaultAmmo {15,10,false};  // создаем объект структуры FAmmoData, заполняем его дефолтными данными

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

	// уменьшает количество патронов, вызывается после каждого выстрела
	void DecreaseAmmo();

	// true когда арсенал полностью пустой, количество магазинов и патронов = 0
	bool IsAmmoEmpty() const;

	// true когда текущий магазин пустой
	bool IsClipEmpty() const;

	// выводит состояние аммуниции в консоль
	void LogAmmo();

private:
	// только для использования внутри c++ классе, не должна быть видна в БП
	// храним текущее количество патронов, магазинов
	FAmmoData CurrentAmmo;

};
