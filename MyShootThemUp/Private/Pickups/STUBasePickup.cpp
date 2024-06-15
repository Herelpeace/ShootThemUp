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
	
}

void ASTUBasePickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// ���������� ��� ������������ ������� overlap �� ������ (��������������)
void ASTUBasePickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	UE_LOG(LogBasePickup, Warning, TEXT(" Pickup was taken "));
	
	// ������� ��������� �����
	Destroy();
}

