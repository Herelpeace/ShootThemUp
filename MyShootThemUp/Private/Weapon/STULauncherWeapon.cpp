// My Shoot Them Up Game , All Rights Reserved
// � STULauncherWeapon.cpp


#include "Weapon/STULauncherWeapon.h"
#include "Weapon/STUProjectile.h"
#include "Kismet/GameplayStatics.h"  // ��� ������ ������

void ASTULauncherWeapon::StartFire()
{
	// ������� � ������� ��������
	MakeShot(); 

}

void ASTULauncherWeapon::MakeShot()
{
	// ������ �������������� ��������� ������, � ���������� SpawnTransform 
	const FTransform SpawnTransform(FRotator::ZeroRotator, GetMuzzleWorldLocation());
	// FRotator::ZeroRotator    - ��������, �������
	// GetMuzzleWorldLocation() - ������� � ������� ������,���������� FVector ���������� ��������� MuzzleSocket
	//                            �.�. ���������� ������ ������ ��������� � ���������� MuzzleSocket

	// ��������� �� actor ������, ����� ������
	auto Projectile = UGameplayStatics::BeginDeferredActorSpawnFromClass(GetWorld(), ProjectileClass, SpawnTransform);
	// UGameplayStatics::BeginDeferredActorSpawnFromClass - ����� ������, ������� ���������� �� ������ BeginPlay, ��� ��������� ��������� ����� ����� ��������
	// GetWorld()      - ��������� �� ���
	// ProjectileClass - ���������� ������ ASTUProjectile, ����� ������� �������
	// SpawnTransform  - ������������� ������

	// �������������� ��������� ����� ������, ������� � ��������� �����

	// ��������� ��������� ����� ����� ����� ���� ���� ������� ������� BeginPlay
	UGameplayStatics::FinishSpawningActor(Projectile, SpawnTransform);
	// Projectile      - ��� ������������ �����
	// SpawnTransform  - ������������� ������
}
