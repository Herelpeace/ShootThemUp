// My Shoot Them Up Game , All Rights Reserved
// � STUBasePickup.cpp

#include "Pickups/STUBasePickup.h"
#include "Components/SphereComponent.h" // ��� �������� �����

DEFINE_LOG_CATEGORY_STATIC(LogBasePickup, All, All);

ASTUBasePickup::ASTUBasePickup()
{
	PrimaryActorTick.bCanEverTick = true;

	// ������� ��������� Sphere, ��������
	CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");

	// ��������� ������ ��� ��������
	CollisionComponent->InitSphereRadius(50.0f);

	// �������� ��������, ���� ������ ���������� � ������������ � ������� ���������, ����������� �������������� ���
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	// �������������� � ������� ��������� � ������� ���� ��������
	// ���������� ������� ��� ���� �������, ��� �������������� ��������� ������� Overlap
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	// ��� overlap ����� ������� ������� NotifyActorBeginOverlap() ������� ����� ��������������

	SetRootComponent(CollisionComponent);
}

void ASTUBasePickup::BeginPlay()
{
	Super::BeginPlay();	

	check(CollisionComponent);
}

void ASTUBasePickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// ���������� ��� ������������ ������� overlap �� ������ (��������������)
void ASTUBasePickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	// �������� ��������� �� Pawn ������ OtherActor
	const auto Pawn = Cast<APawn>(OtherActor);
	
	
	if (GivePickupTo(Pawn))  // � �������� ������ GivePickupTo(Pawn) ������ ���������� false
	{
		// �������� ������
		PickupWasTaken();
	}

}

// �������������� � �����������,���� ��������� ������, ������ �������� � Charactera
bool ASTUBasePickup::GivePickupTo(APawn* Playerpawn)
{
	return false;
}

// ���������� ���� ������ �������, �������� ������
void ASTUBasePickup::PickupWasTaken()
{
	// ��������� ��������, �������� ��������� ���������������� � ���������
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	if (GetRootComponent())
	{
		GetRootComponent()->SetVisibility(false, true);
		// GetRootComponent()->SetVisibility() - ������ ��������� � ��������� ���������� ������, �� ���� ����� ����� ��� ���
		// false                               - ����� ��������� ��� ���
		// true                                - ��������� ����� �������� Visibility � �������� �����������
	}

	FTimerHandle RespawnTimerHandle;  // ������� ���������� �������
	GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &ASTUBasePickup::Respawn, RespawnTime);
	// RespawnTimerHandle      - ���������� �������
	// this                    - ������ � �������� �������� ������
	// ASTUBasePickup::Respawn - ������� ���������� ��� ������������ �������
	// RespawnTime             - ����� ����� ������� ����� ������� ������� ASTUBasePickup::Respawn
}

// ���������� �� ������������� ������� ��������, ������ ����� �������
void ASTUBasePickup::Respawn()
{
	// �������� ������������� �������� � ���������
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

	if (GetRootComponent())
	{
		GetRootComponent()->SetVisibility(true, true);
		// ������ ������ �������
	}

}

