// My Shoot Them Up Game , All Rights Reserved
// � STUBaseWeapon.cpp


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

	// ������� ���������� ��������� ����� ���������� ����������
	CurrentAmmo = DefaultAmmo;
}

// ������� ����� ������ �����, ���������� �� Charactera �� ��� ��� ���� ������ ����� �� ��������
// ������ ��������
void ASTUBaseWeapon::StartFire() 
{

}


// ������� ����� ������ �����, ���������� �� Charactera, ���������� ����� ���� ��� ��������� ������ �����
// ����� ��������
void ASTUBaseWeapon::StopFire()
{

}



// ������� �������� ��� ������ ��������
void ASTUBaseWeapon::MakeShot() 
{

}
// MakeShot() 


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
	const FVector ShootDirection = ViewRotation.Vector();  //FMath::VRandCone( ViewRotation.Vector(), HalfRad);

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

// ��������� ���������� ��������, ���������� ����� ������� ��������
void ASTUBaseWeapon::DecreaseAmmo()
{
	CurrentAmmo.Bullets--;
	
	LogAmmo();

	// ������ ������� ���� ���������� �������� � �������� ����� 0 � ���������� �������� � �������� �� ����� 0
	if (IsClipEmpty() && !IsAmmoEmpty())
	{
		// ������ �������
		ChangeClip();
	}

}

// true ����� ������� �� �����������, ��������� ������, ���������� ��������� � �������� = 0
bool ASTUBaseWeapon::IsAmmoEmpty() const
{
	return !CurrentAmmo.Infinite && CurrentAmmo.Clips == 0 && IsClipEmpty();

}

// true ����� ������� ������� ������
bool ASTUBaseWeapon::IsClipEmpty() const
{
	return CurrentAmmo.Bullets == 0;

}

// ������ ������� �� �����
void ASTUBaseWeapon::ChangeClip()
{
	CurrentAmmo.Bullets = DefaultAmmo.Bullets;

	// ���� ���������� ��������� �� �����������
	if (!CurrentAmmo.Infinite)
	{
		CurrentAmmo.Clips--;
	}

	UE_LOG(LogBaseWeapon, Warning, TEXT("------Change Clip ------"));

}

// ������� ��������� ��������� � �������
void ASTUBaseWeapon::LogAmmo()
{
	FString AmmoInfo = "Ammo: " + FString::FromInt(CurrentAmmo.Bullets) + " / ";
	AmmoInfo += " Magazine: ";
	AmmoInfo += CurrentAmmo.Infinite ? "Infinite" : FString::FromInt(CurrentAmmo.Clips);

	UE_LOG(LogBaseWeapon, Warning, TEXT("%s"),*AmmoInfo);

}

