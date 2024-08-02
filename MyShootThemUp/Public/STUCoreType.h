#pragma once

// В STUCoreType.h

#include "STUCoreType.generated.h"
// содержит заголовочные файлы структур и делегаты

class ASTUBaseWeapon;  // forward declaration

// для STUBaseWeapon
// делегат оповещает WeaponComponent о том что закончились патроны
// при вызове делегата передаем указатель на оружие которе запрашиват перезарядку
DECLARE_MULTICAST_DELEGATE_OneParam(FOnClipEmptySignature, ASTUBaseWeapon*)


// для STUBaseWeapon
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


// для STUWeaponComponent
// структура в которой храним класс оружия и соответствующую ему анимацию перезарядки
// в редакторе будут поля в которые сможем устанавливать соостветствующие БП
USTRUCT(BlueprintType)
struct FWeaponData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")        // в редакторе будет ?
	TSubclassOf<ASTUBaseWeapon> WeaponClass;  // переменная класса оружия

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	UAnimMontage* ReloadAnimMontage;   // в переменной будем хранить анимацию перезарядки для данного оружия
};

// структура хранит иконки оружия и прицела
USTRUCT(BlueprintType)
struct FWeaponUIData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	UTexture2D* MainIcon;   // переменная для иконки оружия
	// UTexture2D - тип данных для хранения структур

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	UTexture2D* CrossHairIcon;   // переменная для иконки прицела
};


// для STUHealthActorComponent
// делегат оповещает жив персонаж или нет
// доступен только в С++
// все делегаты начинаются с буквы F
DECLARE_MULTICAST_DELEGATE(FOnDeathSignature);

// для STUHealthActorComponent
// создаем делегат с 1 параметром, имя FOnHealthChanged, тип параметров float
// вызываем делегат когда происходит изменение Health
// изменили сигнатуру делегата на 2 параметра, добавили float HealthDelta 
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnHealthChangedSignature, float, float);


// VFX

class UNiagaraSystem; 

// храним настроки для текущей декали
USTRUCT(BlueprintType)
struct FDecalData
{
	GENERATED_USTRUCT_BODY()

	// материал декали
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	UMaterialInterface* Material;

	// размер декали
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	FVector Size = FVector(10.0f);
	// FVector(10.0f) - конструктор, инициализирует все компоненты FVectora одним значением

	// время жизни декали
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	float LifeTime = 5.0f;

	// время за которое декаль будет растворяться (становиться прозрачной)
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	float FadeOutTime = 0.7f;

};

// объединяет niagara эффект и декаль
USTRUCT(BlueprintType)
struct FImpactData
{
	GENERATED_USTRUCT_BODY()

	// указатель на niagara систему
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	UNiagaraSystem* NiagaraEffect;

	// cтруктура с настройками декали
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	FDecalData DecalData;

};

// настройки GameMode
USTRUCT(BlueprintType)
struct FGameData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game", meta = (ClampMin = "1", CalampMax = "100"))
	int32 PlayersNum = 2;	// количество игроков

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game", meta = (ClampMin = "1", ClampMax = "10"))
	int32 RoundNum = 4;		// количество раундов


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game", meta = (ClampMin = "3", ClampMax = "300"))
	int32 RoundTime = 10;		// время одного раунда в секуднах



};