// My Shoot Them Up Game , All Rights Reserved
// В STUProjectile.cpp


#include "Weapon/STUProjectile.h"
#include "Components/SphereComponent.h"


ASTUProjectile::ASTUProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

	// создаем компонент Sphere, коллизия
	CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");

	// установим радиус для коллизии
	CollisionComponent->InitSphereRadius(5.0f);

	SetRootComponent(CollisionComponent);

}


void ASTUProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}


