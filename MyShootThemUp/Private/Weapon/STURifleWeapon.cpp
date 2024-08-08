// My Shoot Them Up Game , All Rights Reserved
// � STURifleWeapon.cpp


#include "Weapon/STURifleWeapon.h"
#include "Engine/World.h"                        // 
#include "DrawDebugHelpers.h"                    // ��� ��������� ����� (Line Trace)
#include "Weapon/Components/STUWeaponFXComponent.h"
#include "NiagaraSystem.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"


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
	// ������ niagara
	InitMuzzleFX();

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
	// ��������� ��������� ������� niagara
	SetMuzzleFXVisibility(false);

	// UE_LOG(LogBaseWeapon, Warning, TEXT(" StopFire!!! "));

	// ��������� �������
	GetWorldTimerManager().ClearTimer(ShotTimerHandle);
}

// ������� �������� ��� ������ ��������
void ASTURifleWeapon::MakeShot()
{
	//UE_LOG(LogTemp, Warning, TEXT("Make Shot"));

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

	FVector TraceFXEnd = TraceEnd;

	// ���� ����������� ����, ������ � ����� ���� �����
	if (HitResult.bBlockingHit)
	{
		// ����� ������������ ���������� � TraceFXEnd 
		TraceFXEnd = HitResult.ImpactPoint;
		
		
		// ������� ��������� ����� ������
		MakeDamage(HitResult);

		WeaponFXComponent->PlayImpactFX(HitResult);
		// �������� ������� ����������� FX, �������� Hit ������ (���������� �� ������������)
	}

	// ����� ������� �� ���� �� ����� ������������
	SpawnTraceFX(GetMuzzleWorldLocation(), TraceFXEnd);

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

	DamageActor->TakeDamage(DamageAmount, FDamageEvent(), GetController(), this);

	// DamageAmount          - ���������� Damage
	// FDamageEvent()        - ��� Damage
	// GetPlayerController() - ��������� �� ���������� ������� ����� ����
	// this                  - ��������� �� ����� ������� ����� ����, ������� ������ this
}


// ������� niagara system
void ASTURifleWeapon::InitMuzzleFX()
{
	// ���� ������� ���, ������� ���. ��������� 1 ���, ����� ������ ������ ���������
	if (!MuzzleFXComponent)
	{
		MuzzleFXComponent = SpawnMuzzleFX();
	}

	// �������� ���������
	SetMuzzleFXVisibility(true);
}

// ������������� ��������� �������
void ASTURifleWeapon::SetMuzzleFXVisibility(bool Visibility)
{
	// �������� ��� ������ ����
	if (MuzzleFXComponent)
	{
		// ���������������� �������� niagara
		MuzzleFXComponent->SetPaused(!Visibility);

		// ��������/ ��������� ��������� �������
		MuzzleFXComponent->SetVisibility(Visibility, true);
		// Visibility - �������, ��������� � �������� ����������
		// false      - ��������� � �����������
	}
}

// ����� ������� �����������
void ASTURifleWeapon::SpawnTraceFX(const FVector& TraceStart, const FVector& TraceEnd)
{
	// ������� ������ � ����� ����
	const auto TraceFXComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), TraceFX, TraceStart);
	// GetWorld() - ��������� �� ���
	// TraceFX    - ��������� �� UNiagaraSystem
	// TraceStart - ���������� ������ � ����

	if (TraceFXComponent)
	{
		// �������� Vector3 � ������ niagara (�������� ����� ������)
		TraceFXComponent->SetNiagaraVariableVec3(TraceTargetName, TraceEnd);
		// TraceTargetName - ��� ����������
		// TraceEnd        - �������� ����������

		// ������� ��� �������� � niagara ��������� ����������
		// SetNiagaraVariableActor
		// SetNiagaraVariableBool
		// SetNiagaraVariableFloat
		// SetNiagaraVariableInt
		// SetNiagaraVariablerColor
		// SetNiagaraVariableVec2
		// SetNiagaraVariableVec3

	}

}


// �������� ������� ���������� (��� ����������)
AController* ASTURifleWeapon::GetController() const
{
	// �������� Pawn �� GetOwner
	const auto Pawn = Cast<APawn>(GetOwner());

	// �������� ���������� �� Pawna
	return Pawn ? Pawn->GetController() : nullptr;
}

