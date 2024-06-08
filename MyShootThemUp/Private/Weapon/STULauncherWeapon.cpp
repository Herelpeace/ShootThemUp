// My Shoot Them Up Game , All Rights Reserved
// � STULauncherWeapon.cpp


#include "Weapon/STULauncherWeapon.h"
#include "Weapon/STUProjectile.h"

void ASTULauncherWeapon::StartFire()
{
	// ������� � ������� ��������
	MakeShot(); 

}

void ASTULauncherWeapon::MakeShot()
{
	// �������� ���� �� null, ��������� ����� IsAmmoEmpty() = true
	if (!GetWorld()||IsAmmoEmpty()) return;

	FVector TraceStart, TraceEnd;
	// ��������� � �������� ����� ��������

	if (!GetTraceData(TraceStart, TraceEnd)) return;

	FHitResult HitResult;
	// ��������� � ������� ��������� ���������� � ����������� LineTrace � ���������
	// ��������� FHitResult �������� ����: ����� �����������, ����� �����������, �������, ��������� �� ����� � �������
	// ����������� � �.�. ��� �� FHitResult �������� ���������� ���� ����������� ��� ���, ���������� bBlockingHit

	// ��������� ��������� HitResult
	MakeHit(HitResult, TraceStart, TraceEnd);

	// ���������� ���������� �������� ����� � ������� ������ ��������� ������
	const FVector EndPoint = HitResult.bBlockingHit ? HitResult.ImpactPoint : TraceEnd;
	// ���� ����������� ���� �� EndPoint = ���������� ����� �����������, ����� ���������� TraceEnd
	// bBlockingHit - ���� ��������� HitResult, ��������� true ���� ���� ����������� ������� � ����� ���� ��������
	// ImpactPoint  - ���� ��������� HitResult, ���������� ���������� ����� ����������� ��������

	// ���������� ������ ����������, ��� ����� �� �������� ����� �������� ���������
	const FVector Direction = (EndPoint - GetMuzzleWorldLocation()).GetSafeNormal();
    // ��� ����� ������ ������������, ������� ������� ������ ��������� ��� ������ ������� GetSafeNormal()


	// ������ �������������� ��������� ������, � ���������� SpawnTransform 
	const FTransform SpawnTransform(FRotator::ZeroRotator, GetMuzzleWorldLocation());
	// FRotator::ZeroRotator    - ��������, �������
	// GetMuzzleWorldLocation() - ������� � ������� ������,���������� FVector ���������� ��������� MuzzleSocket
	//                            �.�. ���������� ������ ������ ��������� � ���������� MuzzleSocket

	// ����� ������ ����� GetWorld, ������ ��������� �� ����� ������������� �������
	ASTUProjectile* Projectile = GetWorld()->SpawnActorDeferred<ASTUProjectile>(ProjectileClass, SpawnTransform);
	// TSubclassOf<ASTUProjectile> ProjectileClass - ����� ������ ������� ����� �������� ��� �������� Launchera
	if (Projectile)
	{
		// �������� ������ ����������� (Direction), ������������� ������ ������
		Projectile->SetShootDirection(Direction);
		// �� ���� �� ������� ������ ������ ASTUProjectile � �������� ��� � ����������
		// ����� ����� ��� ���������� ���������� � ������� ������ � ���� public, �������� ���� ������
		// ����� �� �������� �� ����� ���������� ��������� Damage ��� ����� ������ � ����� Projectile
		// ������� ���������� ������ � ����� �� ���������� � public ������� ������

		Projectile->SetOwner(GetOwner());
		// ����������� ��������� Projectil� �������� Charactera �.�. ������ ����� ������������ � Charactera


		// �������� �����
		Projectile->FinishSpawning(SpawnTransform);
	}

	// ��������� ���������� ��������
	DecreaseAmmo();


}
