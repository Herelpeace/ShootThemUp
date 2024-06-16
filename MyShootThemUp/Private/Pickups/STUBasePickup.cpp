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

	check(CollisionComponent);

	// генерируем случайный угол вращения
	GenerateRataionYaw();
}

void ASTUBasePickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// задает вращение в локальных координатах
	AddActorLocalRotation(FRotator(0.0f, RatationYaw,0.0f));
}

// вызывается при срабатывании события overlap на акторе (переопределена)
void ASTUBasePickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	// получаем указатель на Pawn актора OtherActor
	const auto Pawn = Cast<APawn>(OtherActor);
	
	// по сути определяем брать ли pickup
	if (GivePickupTo(Pawn))  // у базового класса GivePickupTo(Pawn) всегда возвращает false
	{                        // у наследников после измнения значения компонента возвращают true
		// скрываем объект
		PickupWasTaken();
	}

}

// переопределяем в наследниках,если подобрали объект, меняет значения у Charactera
bool ASTUBasePickup::GivePickupTo(APawn* PlayerPawn)
{
	return false;
}

// вызывается после взятия объекта, скрываем объект
void ASTUBasePickup::PickupWasTaken()
{
	// отключаем коллизию, коллизия перестает взаимодейстовать с объектами
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	if (GetRootComponent())
	{
		GetRootComponent()->SetVisibility(false, true);
		// GetRootComponent()->SetVisibility() - задать видимость у корневого компонента актора, по сути видим актор или нет
		// false                               - видим компонент или нет
		// true                                - приминить новое значение Visibility к дочерним компонентам
	}

	FTimerHandle RespawnTimerHandle;  // создаем переменную таймера
	GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &ASTUBasePickup::Respawn, RespawnTime);
	// RespawnTimerHandle      - переменная таймера
	// this                    - объект у которого вызываем таймер
	// ASTUBasePickup::Respawn - функция вызываемая при срабатывании таймера
	// RespawnTime             - время через которое будет вызвана функция ASTUBasePickup::Respawn
}

// вызывается по срабатываению таймера респавна, делаем актор видимым
void ASTUBasePickup::Respawn()
{
	// генерируем случайный угол вращения
	GenerateRataionYaw();

	// включаем взимодействие коллизии с объектами
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

	if (GetRootComponent())
	{
		GetRootComponent()->SetVisibility(true, true);
		// делаем объект видимым
	}

}

// функция вычиляет рандомный угол вращения
void ASTUBasePickup::GenerateRataionYaw()
{
	const auto Direction = FMath::RandBool() ? 1.0f : -1.0f;
	RatationYaw = FMath::RandRange(1.0f, 5.0f)*Direction;
	//FMath::RandRange (n1, n2) - возвращает рандомное число между n1 и n 2

}

