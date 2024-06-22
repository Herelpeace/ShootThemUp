// My Shoot Them Up Game , All Rights Reserved
// В STUWeaponFXComponent.cpp


#include "Weapon/Components/STUWeaponFXComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"



USTUWeaponFXComponent::USTUWeaponFXComponent()
{

	PrimaryComponentTick.bCanEverTick = true;


}


// Called when the game startsvoid USTUWeaponFXComponent::BeginPlay()
void USTUWeaponFXComponent::BeginPlay()
{
	Super::BeginPlay();


	
}



void USTUWeaponFXComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

// проигрываем эффект Niagara при выстреле
void USTUWeaponFXComponent::PlayImpactFX(const FHitResult& Hit)
{
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