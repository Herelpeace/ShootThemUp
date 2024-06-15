// My Shoot Them Up Game , All Rights Reserved
// ����� ������ ��� ������ launcher
// � STUProjectile.cpp


#include "Weapon/STUProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"


ASTUProjectile::ASTUProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

	// ������� ��������� Sphere, ��������
	CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");

	// ��������� ������ ��� ��������
	CollisionComponent->InitSphereRadius(5.0f);

	// �������� ��������, ���� ������ ���������� � ������������ � ������� ���������, ����������� �������������� ���
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	// �������������� � ������� ��������� � ������� ���� ��������
	// ���������� ������� ��� ���� �������, ��� �������������� ������ ����� ������������� � ����� ������������
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);

	SetRootComponent(CollisionComponent);

	// ��������� �������� ��� ������� (��� ������)
	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
	MovementComponent->InitialSpeed = 2000.0f;          // ������ �������� �� ���������
	MovementComponent->ProjectileGravityScale = 0.0f;   // ���������� ����������� �� ������ ��� ��������
}


void ASTUProjectile::BeginPlay()
{
	Super::BeginPlay();

	check(MovementComponent);
	check(CollisionComponent);

	// ������ �������� ������
	// ��������� ������ ������������ �������� �� �������� � ���� InitialSpeed � MovementComponent
	MovementComponent->Velocity = ShotDirection * MovementComponent->InitialSpeed;

	// ������������ ������� ��� ��������, ���� �������� ������ ������
	CollisionComponent->IgnoreActorWhenMoving(GetOwner(), true);
	// GetOwner() - ��������� �� ���������, Charactera
	// true       - true - ����������, false - �� ����������

	// ������� ������� ���������� ����� ��������� ������������ � ������� ��� � ������ �����������
	CollisionComponent->OnComponentHit.AddDynamic(this, &ASTUProjectile::OnProjectileHit);
	// this                             - ��������� �� ������� ������
	// &ASTUProjectile::OnProjectileHit - ������ �� ������� ������� �������
	//                                    ��������� ������� ������ ��������� � ���������� ��������

	SetLifeSpan(LifeSecond);
}

// ���������� ������� ��������� ���������
void ASTUProjectile::OnProjectileHit( UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!GetWorld()) return;

	MovementComponent->StopMovementImmediately();
	// StopMovementImmediately() - ������������� �������� �������� �  0

	// ������� Damage ���� ����� ��������� ���� ������� ������� ��������� � ��������� �����
	UGameplayStatics::ApplyRadialDamage(GetWorld(),DamageAmount,GetActorLocation(),DamageRadius,UDamageType::StaticClass(),{GetOwner()},this,nullptr,DoFullDamage); 

	// ������� ApplyRadialDamage ��������� �� ���� ���������� � �� ������� � �������� ��� ��� ������ ���� ������� TakeDamage(), ������� ���� ��������� Damage
	// GetWorld()				   - ��������� �� ���
	// DamageAmount				   - ���������� ���������� �����
	// GetActorLocation()		   - ����� ����� �����
	// DamageRadius				   - ������ �����
	// UDamageType::StaticClass()  - ��� Damage, �������� StaticClass()
	// {GetOwner()}				   - ������ ������� ������� �� ����� ���������� ����, {} - ������ ������, ���� ��������� ���� �������, GetOwner() - ���� �� �������
	// this					       - ����� ������� ������� ����
	// GetController()			   - Controller. �������� ���������� �������� Pawna
	// DoFullDamage			   	   - true - ���c�������� ���� �� ����� �������� �� ������, false - ��� ����� � ������ ��� ���� ������

	// ���������� ����� �����
	DrawDebugSphere(GetWorld(), GetActorLocation(), DamageRadius, 24, FColor::Green, false, 5.0f);

	// ������� ����� ��� ������������
	Destroy();
}

// �������� ������� ���������� (��� ����������)
AController* ASTUProjectile::GetController() const
{
	// �������� Pawn �� GetOwner
	const auto Pawn = Cast<APawn>(GetOwner());

	// �������� ���������� �� Pawna
	return Pawn ? Pawn->GetController():nullptr;
}


