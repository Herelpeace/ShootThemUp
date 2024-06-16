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

	// ���������� ��������� ���� ��������
	GenerateRataionYaw();
}

void ASTUBasePickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// ������ �������� � ��������� �����������
	AddActorLocalRotation(FRotator(0.0f, RatationYaw,0.0f));
}

// ���������� ��� ������������ ������� overlap �� ������ (��������������)
void ASTUBasePickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	// �������� ��������� �� Pawn ������ OtherActor
	const auto Pawn = Cast<APawn>(OtherActor);
	
	// �� ���� ���������� ����� �� pickup
	if (GivePickupTo(Pawn))  // � �������� ������ GivePickupTo(Pawn) ������ ���������� false
	{                        // � ����������� ����� �������� �������� ���������� ���������� true
		// �������� ������
		PickupWasTaken();
	}

}

// �������������� � �����������,���� ��������� ������, ������ �������� � Charactera
bool ASTUBasePickup::GivePickupTo(APawn* PlayerPawn)
{
	return false;
}

// ���������� ����� ������ �������, �������� ������
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
	// ���������� ��������� ���� ��������
	GenerateRataionYaw();

	// �������� ������������� �������� � ���������
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

	if (GetRootComponent())
	{
		GetRootComponent()->SetVisibility(true, true);
		// ������ ������ �������
	}

}

// ������� �������� ��������� ���� ��������
void ASTUBasePickup::GenerateRataionYaw()
{
	const auto Direction = FMath::RandBool() ? 1.0f : -1.0f;
	RatationYaw = FMath::RandRange(1.0f, 5.0f)*Direction;
	//FMath::RandRange (n1, n2) - ���������� ��������� ����� ����� n1 � n 2

}

