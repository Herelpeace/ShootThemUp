// My Shoot Them Up Game , All Rights Reserved
// В STUWeaponFXComponent.cpp


#include "Weapon/Components/STUWeaponFXComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "PhysicalMaterials/PhysicalMaterial.h"



USTUWeaponFXComponent::USTUWeaponFXComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// проигрываем эффект Niagara при выстреле
void USTUWeaponFXComponent::PlayImpactFX(const FHitResult& Hit)
{
	auto Effect = DefaultEffect;  // записываем эффект в переменную

	if (Hit.PhysMaterial.IsValid())  // проверка что у объекта есть физический материал
	{
		const auto PhysMat = Hit.PhysMaterial.Get(); // получаем физический материал

		if (EffectsMap.Contains(PhysMat))  // у контейнера вызваем функцию Contains(key) - проверят есть ли ключ в контейнере
		{
			Effect = EffectsMap[PhysMat]; // записываем эффект который соответствует найденному ключу
		}
	}

	// функция спавна эффекта niagara в мир
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(),Effect, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
	// GetWorld()                  - указатель на мир, можно передать как GetWorld() так и this
	// Effect                      - указатель на переменную niagara эффектом (UNiagaraSystem* Effect)
	// Hit.ImpactPoint             - координаты в которых произойдет спавн
	// Hit.ImpactNormal.Rotation() - ориентация в пространстве (положение векторов эффекта)
	// bool bAutoDestroy           - дополнительный параметр, автоудаление эффекта после проигрывания, по умолчанию стоит в true
	// проверка GetWorld() и Effect на null есть внутри функции
}

// в  FHitResult находится нужная информация для спавна эффекта (положение в мире, нормаль и т.д.)