// My Shoot Them Up Game , All Rights Reserved
// В STUWeaponFXComponent.cpp


#include "Weapon/Components/STUWeaponFXComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Kismet/GameplayStatics.h"
#include "Components/DecalComponent.h"


USTUWeaponFXComponent::USTUWeaponFXComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// проигрываем эффект Niagara при выстреле
void USTUWeaponFXComponent::PlayImpactFX(const FHitResult& Hit)
{
	auto ImpactData = DefaultImpactData;             // записываем эффект в переменную

	if (Hit.PhysMaterial.IsValid())                  // проверка что у объекта есть физический материал
	{
		const auto PhysMat = Hit.PhysMaterial.Get(); // получаем физический материал

		if (ImpactDataMap.Contains(PhysMat))         // у контейнера вызваем функцию Contains(key) - проверят есть ли ключ в контейнере
		{
			ImpactData = ImpactDataMap[PhysMat];     // записываем эффект который соответствует найденному ключу
		}
	}

	// спавна эффекта niagara в мир
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(),ImpactData.NiagaraEffect, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
	// у найденого параметра ImpactData вызываем эффект niagara
	// GetWorld()                  - указатель на мир, можно передать как GetWorld() так и this
	// Effect                      - указатель на переменную niagara эффектом (UNiagaraSystem* Effect)
	// Hit.ImpactPoint             - координаты в которых произойдет спавн
	// Hit.ImpactNormal.Rotation() - ориентация в пространстве (положение векторов эффекта)
	// bool bAutoDestroy           - дополнительный параметр, автоудаление эффекта после проигрывания, по умолчанию стоит в true
	// проверка GetWorld() и Effect на null есть внутри функции

	// в  FHitResult находится нужная информация для спавна эффекта (положение в мире, нормаль и т.д.)

	// спавн декалей
	auto DecalComponent = UGameplayStatics::SpawnDecalAtLocation(GetWorld(), ImpactData.DecalData.Material, ImpactData.DecalData.Size, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
	// SpawnDecalAtLocation - просто спавним декаль 
	// SpawnDecalAttached   - спавним декаль и присоединяем к scene Componentу
	// После спавна функция возвращает указатель на DecalComponent, данный компонент нужен
	
	// GetWorld()                     - указатель на мир
	// ImpactData->DecalData.Material - материал декали
	// ImpactData->DecalData.Size     - размер декали
	// Hit.ImpactPoint                - локация в мире
	// Hit.ImpactNormal.Rotation()    - вращение декали
	// остальные эффекты по умолчанию

	if (DecalComponent)
	{
		DecalComponent->SetFadeOut(ImpactData.DecalData.LifeTime, ImpactData.DecalData.FadeOutTime);
		// ImpactData->DecalData.LifeTime     - через какое время запустится анимация исчезновения декали
		// ImpactData->DecalData.FadeOutTime  - сколько времени будет длиться анимация (исчезновение)
		// 3 булевая переменная отвечат за удаление ownera декали, нужна когда для спавна использовалась SpawnDecalAttached 
	}
}

