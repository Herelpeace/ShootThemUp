// My Shoot Them Up Game , All Rights Reserved
// В STUProjectile.cpp


#include "Weapon/STUProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

ASTUProjectile::ASTUProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

	// создаем компонент Sphere, коллизия
	CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");

	// установим радиус для коллизии
	CollisionComponent->InitSphereRadius(5.0f);

	SetRootComponent(CollisionComponent);

	// компонент скорости для акторов (для ракеты)
	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
	MovementComponent->InitialSpeed = 2000.0f;          // задаем скорость по умолчанию
	MovementComponent->ProjectileGravityScale = 0.0f;   // гравитация действующая на актора при движении

}


void ASTUProjectile::BeginPlay()
{
	Super::BeginPlay();

	check(MovementComponent);

	// задаем скорость ракете
	// единичный вектор навправления умножаем на значение в поле InitialSpeed у MovementComponent
	MovementComponent->Velocity = ShotDirection * MovementComponent->InitialSpeed;
	
	SetLifeSpan(5.0f);

}


