// My Shoot Them Up Game , All Rights Reserved
// класс ракеты для оружия launcher
// В STUProjectile.cpp


#include "Weapon/STUProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"


ASTUProjectile::ASTUProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

	// создаем компонент Sphere, коллизия
	CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");

	// установим радиус для коллизии
	CollisionComponent->InitSphereRadius(5.0f);

	// включаем коллизию, есть только оповещение о столкновении с другими объектами, физического взаимодействия нет
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	// взаимодействие с другими объектами у которых есть коллизии
	// одинаковая реакция для всех каналов, при взаимодействии ракета будет заблокирована в точке столкновения
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);

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
	check(CollisionComponent);

	// задаем скорость ракете
	// единичный вектор навправления умножаем на значение в поле InitialSpeed у MovementComponent
	MovementComponent->Velocity = ShotDirection * MovementComponent->InitialSpeed;

	// игнорировать акторов для коллизии, если персонаж догнал ракету
	CollisionComponent->IgnoreActorWhenMoving(GetOwner(), true);
	// GetOwner() - указатель на владельца, Charactera
	// true       - true - игнорируем, false - не игнорируем

	// делегат который вызывается когда произошло столкновение с актором или с другим компонентом
	CollisionComponent->OnComponentHit.AddDynamic(this, &ASTUProjectile::OnProjectileHit);
	// this                             - указатель на текущий объект
	// &ASTUProjectile::OnProjectileHit - ссылка на функцию которую вызвать
	//                                    сигнатура функции должна совпадать с сигнатурой делегата

	SetLifeSpan(LifeSecond);
}

// реализация функции вызваемой делегатом
void ASTUProjectile::OnProjectileHit( UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!GetWorld()) return;

	MovementComponent->StopMovementImmediately();
	// StopMovementImmediately() - устанавливает скорость движения в  0

	// наносим Damage урон будет наносится всем акторам которые находятся в модельной сфере
	UGameplayStatics::ApplyRadialDamage(GetWorld(),DamageAmount,GetActorLocation(),DamageRadius,UDamageType::StaticClass(),{GetOwner()},this,nullptr,DoFullDamage); 

	// функция ApplyRadialDamage пробегает по всем переданным в неё акторам и вызывает для них внутри себя функцию TakeDamage(), наносит урон величиной Damage
	// GetWorld()				   - указатель на мир
	// DamageAmount				   - количество наносимого урона
	// GetActorLocation()		   - центр сферы урона
	// DamageRadius				   - радиус сферы
	// UDamageType::StaticClass()  - тип Damage, передаем StaticClass()
	// {GetOwner()}				   - массив акторов которым не будет наноситься урон, {} - пустой массив, урон наносится всем акторам, GetOwner() - себе не наносим
	// this					       - актор который наносит урон
	// GetController()			   - Controller. Получаем контроллер текущего Pawna
	// DoFullDamage			   	   - true - макcимальный урон на любом удалении от центра, false - чем ближе к центру тем урон больше

	// отображаем сферу урона
	DrawDebugSphere(GetWorld(), GetActorLocation(), DamageRadius, 24, FColor::Green, false, 5.0f);

	// удаляем актор при столкновении
	Destroy();
}

// получаем текущий контроллер (для статистики)
AController* ASTUProjectile::GetController() const
{
	// получаем Pawn из GetOwner
	const auto Pawn = Cast<APawn>(GetOwner());

	// получаем контроллер из Pawna
	return Pawn ? Pawn->GetController():nullptr;
}


