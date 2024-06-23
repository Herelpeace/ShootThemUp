// My Shoot Them Up Game , All Rights Reserved
// В STUWeaponFXComponent.h

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUCoreType.h"
#include "STUWeaponFXComponent.generated.h"

class UNiagaraSystem; // forward declaration
class UPhysicalMaterial;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYSHOOTTHEMUP_API USTUWeaponFXComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USTUWeaponFXComponent();

public:	
	void PlayImpactFX(const FHitResult& Hit);
	// в  FHitResult находится нужная информация для спавна эффекта (положение в мире, нормаль и т.д.)

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")  // будет поле в котором можно выбрать эффект
	FImpactData DefaultImpactData;  // дефолтный эффект содержит как niagarу так и декаль

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	TMap<UPhysicalMaterial*, FImpactData > ImpactDataMap;      // отображается как массив в котором выбираем: материал - эффект и декаль к нему

	// TMap - Ассоциативный контейнер, принимает типы котрые хотим в нем хранить 
	// хранит их в виде комбинации ключа и значения т.е какому то ключу соответствует значение 
	// В качестве ключа используем физический материал, а в качестве значения niagara систему
};
