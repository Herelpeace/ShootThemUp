// My Shoot Them Up Game , All Rights Reserved
// STUBaseWeapon.cpp


#include "Weapon/STUBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"    // ��� ���������� Mesh
#include "Engine/World.h"                        // 
#include "DrawDebugHelpers.h"                    // ��� ��������� ����� (Line Trace)
#include "GameFramework/Character.h"             // ����� Charactera
#include "GameFramework/Controller.h"            // ����� Controllera ����� ����� ���� �������� ������ � ������


DEFINE_LOG_CATEGORY_STATIC(LogBaseWeapon, All, All);


ASTUBaseWeapon::ASTUBaseWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	SetRootComponent(WeaponMesh);    // ������ �������� ��������
}


void ASTUBaseWeapon::BeginPlay()
{
	Super::BeginPlay();	

	check(WeaponMesh);  // ��������� Mash ������, ���� ��� ���, �� ������ �� ������������
}

// ������� ����� ������ �����, ���������� �� Charactera
void ASTUBaseWeapon::Fire() 
{
	UE_LOG(LogBaseWeapon, Warning, TEXT(" Fire!!! "));

	MakeShot();
}


// ������� �������� ��� ������ ��������
void ASTUBaseWeapon::MakeShot() 
{
	// �������� ���� �� null
	if (!GetWorld()) return;

	FVector TraceStart,TraceEnd;
	// ��������� � �������� ����� ��������

	if (!GetTraceData(TraceStart, TraceEnd)) return;


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

		DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), HitResult.ImpactPoint, FColor::Green, false, 3.0f, 0, 3.0f);

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
	    DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.0f, 24.0f, FColor::Green, false, 5.0f);

		// GetWorld()            - ��������� �� ���
		// HitResult.ImpactPoint - ����� �����, ���������� � ������� ������ �����, ����� ���������� ����� �����������
		// 10.0f                 - ������ �����
		// 24.0f                 - ���������� ���������
		// FColor::Green         - ���� �����
		// false                 - ?
		// 5.0f                  - ����� ����������� ����� ������

		UE_LOG(LogBaseWeapon, Warning, TEXT(" Bone: %s "), *HitResult.BoneName.ToString() );
	}
	else
	{
		DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), TraceEnd, FColor::Green, false, 3.0f, 0, 3.0f);
		// ���� ������ �� ������ �� �������� ����� ������ � TraceEnd
	}

}


// ������ ���������� ��������� �� ���������� �������� ������
APlayerController* ASTUBaseWeapon::GetPlayerController() const
{
	const auto Player = Cast<ACharacter>(GetOwner());
	// �������� ��������� �� ��������� ���������� STUBaseWeapon, �������� ��� � ���� ACharacter, ���������� �
	// ����������

	if (!Player) return nullptr;

	return Player->GetController<APlayerController>();
	// �� ��������� �� ��������� �������� ��������� �� Controller
}

// �������� ���������� � �������� ������
bool ASTUBaseWeapon::GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const
{
	const auto Controller = GetPlayerController();

	if (!Controller)  return false;

	//FVector ViewLocation;  // ��� ���������� ���������
	//FRotator ViewRotation; // ��� ���������� ��������

	Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);
	// ��������� ���������� ViewLocation, ViewRotation �������
	// �� ��������� �� Controller �������� ������� ������
	// ��������� �� ������ Charactera ViewLocation - ����������� ������, ViewRotation- �������� ������
	return true;
}


// ������� ���������� ��������� ������
FVector ASTUBaseWeapon::GetMuzzleWorldLocation() const
{
	return WeaponMesh->GetSocketLocation(MuzzleSocketName);
}

// ��������� ��������� � �������� ���������� ��� �������� �����
bool ASTUBaseWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
	FVector ViewLocation;  // ��� ���������� ���������
	FRotator ViewRotation; // ��� ���������� ��������

	if(!GetPlayerViewPoint(ViewLocation, ViewRotation)) return false;


	// ������� ������������� ������
	// const FTransform SocketTransform = WeaponMesh->GetSocketTransform(MuzzleSocketName);

	// GetSocketTransform - �������� Transform ������, ��������� 2 ���������
	// MuzzleSocketName   - ��� ������
	// TypeCoordinate     - ��� ��������� � ������� ����� �������� �����. ��������
	// �� ������ ������ �������� ���������� � ������� ������� ���������

	// ����� ������ ��������, ���������� � ��� ��������� ������
	// ����� ������ ��������, ���������� � ��� ��������� ������
	TraceStart = ViewLocation; // SocketTransform.GetLocation();

	// ������ ����������� �������� (���������)
	const FVector ShootDirection = ViewRotation.Vector(); //	SocketTransform.GetRotation().GetForwardVector();

	// SocketTransform.GetRotation() - �������� ���������� ����� ��������
	// GetForwardVector()            - ���������� Forward ������ ����������� (������ �������� �� ��� �)
	// ViewRotation.Vector()         - ���������� Forward ������

	// �������� ����� ��������
	TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;

	// � ����� ������ ���������� ��������� ������ ����������� ���������� �� ����� �� �����, ������� ������ ������
	// �������

	return true;

}


// �������� ������ � ����������� (������������)
void ASTUBaseWeapon::MakeHit( FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd) 
{
	if (!GetWorld()) return;

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetOwner()); // ��������� ���� AddIgnoredActor()

	// FCollisionQueryParams - ��������� � ������� ����� ������� ������������ ���������� ��� ������
	// AddIgnoredActor()     - ����� �������� ����� ������������, ����� ����� ����� �� ������� ��� � ���� ��� ��������


	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, CollisionParams);

	// LineTraceSingleByChannel()		 - ������ ���������� � ����������� �
	// ������ ��������
	// HitResult
	// - ��������� ������� �������� ���������� � ����������� TraceStart
	// - ���������� ������ ����� TraceEnd
	// - ���������� ����� ����� ECollisionChannel::ECC_Visibility - ��������������� ������� �� �����, �������� ������
	// � ��������� ������� ��������� ������ �����
	//                                     ��������� ������� ����� ��������������
	// ������� ��� �� ���������� true ���� ����������� ���� ��� false ���� ������
	// CollisionParams                   - ������������ ������. (�������� ������� �����, �� ����� �������� ���� �
	// ����)
}


void  ASTUBaseWeapon::MakeDamage(FHitResult& HitResult)
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

