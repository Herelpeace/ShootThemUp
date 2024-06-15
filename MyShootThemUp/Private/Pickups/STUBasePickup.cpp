// My Shoot Them Up Game , All Rights Reserved
// В STUBasePickup.cpp

#include "Pickups/STUBasePickup.h"
#include "Components/SphereComponent.h" // для коллизии сферы

DEFINE_LOG_CATEGORY_STATIC(LogBasePickup, All, All);

ASTUBasePickup::ASTUBasePickup()
{
	PrimaryActorTick.bCanEverTick = true;

	// создаем компонент Sphere, коллизия
	CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");

	// установим радиус для коллизии
	CollisionComponent->InitSphereRadius(50.0f);

	// включаем коллизию, есть только оповещение о столкновении с другими объектами, физического взаимодействия нет
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	// взаимодействие с другими объектами у которых есть коллизии
	// одинаковая реакция для всех каналов, при взаимодействии сработает событие Overlap
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	// при overlap будет вызвана функция NotifyActorBeginOverlap() которую нужно переопределить

	SetRootComponent(CollisionComponent);

}

void ASTUBasePickup::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASTUBasePickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// вызывается при срабатывании события overlap на акторе (переопределена)
void ASTUBasePickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	UE_LOG(LogBasePickup, Warning, TEXT(" Pickup was taken "));
	
	// удаляем компонент сферы
	Destroy();
}

