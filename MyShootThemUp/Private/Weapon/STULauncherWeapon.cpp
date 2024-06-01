// My Shoot Them Up Game , All Rights Reserved
// В STULauncherWeapon.cpp


#include "Weapon/STULauncherWeapon.h"
#include "Weapon/STUProjectile.h"
#include "Kismet/GameplayStatics.h"  // для спавна ракеты

void ASTULauncherWeapon::StartFire()
{
	// функция с логикой стрельбы
	MakeShot(); 

}

void ASTULauncherWeapon::MakeShot()
{
	// задаем первоначальный трансформ ракеты, в переменную SpawnTransform 
	const FTransform SpawnTransform(FRotator::ZeroRotator, GetMuzzleWorldLocation());
	// FRotator::ZeroRotator    - вращение, нулевое
	// GetMuzzleWorldLocation() - функция в базовом классе,возвращает FVector координаты положения MuzzleSocket
	//                            т.е. координаты спавна ракеты совпадают с координами MuzzleSocket

	// указатель на actor ракеты, спавн ракеты
	auto Projectile = UGameplayStatics::BeginDeferredActorSpawnFromClass(GetWorld(), ProjectileClass, SpawnTransform);
	// UGameplayStatics::BeginDeferredActorSpawnFromClass - спавн ракеты, функция вызывается до вызова BeginPlay, что позволяет настроить класс перед запуском
	// GetWorld()      - уакзатель на мир
	// ProjectileClass - переменная класса ASTUProjectile, класс который спавним
	// SpawnTransform  - трансформация спавна

	// дополнительные параметры спанв ракеты, запишем в следующем уроке

	// необходмо завершить спавн чтобы после него была вызвана функция BeginPlay
	UGameplayStatics::FinishSpawningActor(Projectile, SpawnTransform);
	// Projectile      - наш соспавненный актор
	// SpawnTransform  - трансформация спавна
}
