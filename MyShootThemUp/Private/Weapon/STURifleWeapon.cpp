// My Shoot Them Up Game , All Rights Reserved
// � STURifleWeapon.cpp


#include "Weapon/STURifleWeapon.h"
#include "Engine/World.h"                        // 
#include "DrawDebugHelpers.h"                    // ��� ��������� ����� (Line Trace)
#include "Weapon/Components/STUWeaponFXComponent.h"


ASTURifleWeapon::ASTURifleWeapon()  // ����������� ������ ASTURifleWeapon, ����� ��� �������� ��������� STUWeaponFXComponent
{
	// � ���������� FX ��������� ���������� ��������� USTUWeaponFXComponent
	WeaponFXComponent = CreateDefaultSubobject<USTUWeaponFXComponent>("WeaponFXComponent");
}

void ASTURifleWeapon::BeginPlay()
{
	Super::BeginPlay();

	check(WeaponFXComponent);   // drbug �������� ���������� �� null
}

// ������� ����� ������ �����, ���������� �� Charactera �� ��� ��� ���� ������ ����� �� ��������
// ������ ��������
void ASTURifleWeapon::StartFire()
{
	// UE_LOG(LogBaseWeapon, Warning, TEXT(" StartFire!!! "));

	// ������ �������
	GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &ASTURifleWeapon::MakeShot, TimeBetweenShots, true);

	// ShotTimerHandle           - ��� ������������ �������
	// this                      - ��������� �� ������
	// &ASTUBaseWeapon::MakeShot - ������� ������� ����� ����������
	// TimeBetweenShots          - ����� ����� �������� ������� ( float ����������,�������� ��������)
	// true                      - ��������� ������ ������� ( false - ������������ ����� )

	// ������� ���������� �������
	MakeShot();
}


// ������� ����� ������ �����, ���������� �� Charactera, ���������� ����� ���� ��� ��������� ������ �����
// ����� ��������
void ASTURifleWeapon::StopFire()
{
	// UE_LOG(LogBaseWeapon, Warning, TEXT(" StopFire!!! "));

	// ��������� �������
	GetWorldTimerManager().ClearTimer(ShotTimerHandle);
}

// ������� �������� ��� ������ ��������
void ASTURifleWeapon::MakeShot()
{
	UE_LOG(LogTemp, Warning, TEXT("Make Shot"));

	// �������� ���� �� null, ��������� ����� IsAmmoEmpty() = true
	if (!GetWorld() || IsAmmoEmpty())
	{
		StopFire();
		return;
	}

	FVector TraceStart, TraceEnd;
	// ��������� � �������� ����� ��������

	if (!GetTraceData(TraceStart, TraceEnd))
	{
		StopFire();
		return;
	}

	FHitResult HitResult;
	// ��������� � ������� ��������� ���������� � ����������� LineTrace � ���������
	// ��������� FHitResult �������� ����: ����� �����������, ����� �����������, �������, ��������� �� ����� � �������
	// ����������� � �.�. ��� �� FHitResult �������� ���������� ���� ����������� ��� ���, ���������� bBlockingHit

	// ��������� ��������� HitResult
	MakeHit(HitResult, TraceStart, TraceEnd);


	// ���� ����������� ����, ������ � ����� ���� �����
	if (HitResult.bBlockingHit)
	{
		// ������� ��������� ����� ������
		MakeDamage(HitResult);


		// ������� ��������� �����,������� ��������� � ���� ���������� (��� ����� �������, ������������)
		//DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Green, false, 3.0f, 0, 3.0f);

		//DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), HitResult.ImpactPoint, FColor::Green, false, 3.0f, 0, 3.0f);

		// GetWorld()    - ��������� �� ���
		// TraceStart    - ���������� ������ ���������� �����
		// TraceEnd      - �������� �����
		// FColor::Green - ���� �����
		// false         - ����� �� �������� ��������, �������� ����� ����� �� �����
		// 3.0f          - ����� ����������� ����� �� ������������
		// 0             - ������� ��������� �������
		// 3.0f          - ������� �����

		// SocketTransform.GetLocation() - ���������� ������ ���������� �����
		// HitResult.ImpactPoint         - �������� �����


		// ������ ����� � ����� �����������
		//DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.0f, 24.0f, FColor::Green, false, 5.0f);

		// GetWorld()            - ��������� �� ���
		// HitResult.ImpactPoint - ����� �����, ���������� � ������� ������ �����, ����� ���������� ����� �����������
		// 10.0f                 - ������ �����
		// 24.0f                 - ���������� ���������
		// FColor::Green         - ���� �����
		// false                 - ?
		// 5.0f                  - ����� ����������� ����� ������

		// UE_LOG(LogBaseWeapon, Warning, TEXT(" Bone: %s "), *HitResult.BoneName.ToString());

		WeaponFXComponent->PlayImpactFX(HitResult);
		// �������� ������� ����������� FX, �������� Hit ������ (���������� �� ������������)

	}
	else
	{
		DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), TraceEnd, FColor::Green, false, 3.0f, 0, 3.0f);
		// ���� ������ �� ������ �� �������� ����� ������ � TraceEnd
	}

	// ��������� ���������� ��������
	DecreaseAmmo();
}
// MakeShot() 

// ��������� ��������� � �������� ���������� ��� �������� �����
bool ASTURifleWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
	FVector  ViewLocation;  // ��� ���������� ���������
	FRotator ViewRotation;  // ��� ���������� ��������

	if (!GetPlayerViewPoint(ViewLocation, ViewRotation)) return false;


	// ������� ������������� ������
	// const FTransform SocketTransform = WeaponMesh->GetSocketTransform(MuzzleSocketName);

	// GetSocketTransform - �������� Transform ������, ��������� 2 ���������
	// MuzzleSocketName   - ��� ������
	// TypeCoordinate     - ��� ��������� � ������� ����� �������� �����. ��������
	// �� ������ ������ �������� ���������� � ������� ������� ���������

	// ����� ������ ��������, ���������� � ��� ��������� ������
	// ����� ������ ��������, ���������� � ��� ��������� ������
	TraceStart = ViewLocation; // SocketTransform.GetLocation();

	// ��������� ���� �������� � �������
	const auto HalfRad = FMath::DegreesToRadians(BulletSpread);

	// ������ ����������� �������� (���������)
	const FVector ShootDirection = FMath::VRandCone(ViewRotation.Vector(), HalfRad); //	SocketTransform.GetRotation().GetForwardVector();

	// SocketTransform.GetRotation() - �������� ���������� ����� ��������
	// GetForwardVector()            - ���������� Forward ������ ����������� (������ �������� �� ��� �)
	// ViewRotation.Vector()         - ���������� Forward ������
	// FMath::VRandCone()            - �������� ��������� ������ � ���������� ������������
	// ViewRotation.Vector()         - ����������� � ������� �������� �������
	// HalfRad                       - �������� ���� ����������� ������ ( � ��������)

	// �������� ����� ��������
	TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;

	// � ����� ������ ���������� ��������� ������ ����������� ���������� �� ����� �� �����, ������� ������ ������
	// �������

	return true;

}


// ����� HitResult ������� �� ������ � ��������� � ���� TakeDamage
void  ASTURifleWeapon::MakeDamage(FHitResult& HitResult)
{
	// �������� ��������� �� ������ � �������� ����� LineTrace
	const auto DamageActor = HitResult.GetActor();

	if (!DamageActor) return;

	DamageActor->TakeDamage(DamageAmount, FDamageEvent(), GetPlayerController(), this);

	// DamageAmount          - ���������� Damage
	// FDamageEvent()        - ��� Damage
	// GetPlayerController() - ��������� �� ���������� ������� ����� ����
	// this                  - ��������� �� ����� ������� ����� ����, ������� ������ this
}