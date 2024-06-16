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

    // ����� ���� ��� check ������ ��� ����� ������� �����
	// �� ������ ���� � �� ���������� ������������ ���������� ���� � ��������
	checkf(DefaultAmmo.Bullets>0,TEXT("Bullets count couldn't be less or equal zero"));  // ������������ ���������� ����
	checkf(DefaultAmmo.Clips>0,  TEXT("Clips count couldn't be less or equal zero"));    // ������������ ���������� ���������

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
	// ���� ���������� ��������� ����� 0, ������� ���������,�������
	if (CurrentAmmo.Bullets == 0)
	{
		UE_LOG(LogBaseWeapon, Warning, TEXT("Clip is empty!"));
		return;
	}

	CurrentAmmo.Bullets--;
	
	// ������ ������� ���� ���������� �������� � �������� ����� 0 � ���������� �������� � �������� �� ����� 0
	// �������� �������
	if (IsClipEmpty() && !IsAmmoEmpty())
	{
		// ������������� ��������
		StopFire();
		// �������� ������� 
		OnClipEmpty.Broadcast(this);
	}
	// ������ �������, ��������� ������, �������� 1 ������, �������� �������, ����� ���� ����������� ����������� 
	// (���� ���������� ���� = 0), ����������� ����� ������ ����� ��������� �������� � � ������� ������������ �������
	// ������� �� ������, ������� ������ ���������� �������� �� ����� ����������� 
	// ������� ������� StopFire(); � ��� ������ ���������
	// � ������ STURifleWeapon ������ ������� ������ ������� � ������� MakeShot()
	// ����� StopFire() �� ������� �������� TimerHandle
	// ������� ������� ������ ����� ��������, � ���� ���� ��� �� ������� ������
	// � ����� ����, ������� ��������, ���� ��� - ������� ������, � �� �� ������

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
	// ���� ���������� ��������� �� �����������
	if (!CurrentAmmo.Infinite)
	{
		// ���� ���������� ��������� ����� 0, ������� ���������,�������
		if (CurrentAmmo.Clips==0)
		{
			UE_LOG(LogBaseWeapon, Warning, TEXT("No More Clips"));
			return;
		}
		CurrentAmmo.Clips--;
	}

	// ���������� ���� � �������� ����� ����������
	CurrentAmmo.Bullets = DefaultAmmo.Bullets;

	UE_LOG(LogBaseWeapon, Warning, TEXT("------Change Clip ------"));

}

// ����� �� ������ �����������
bool ASTUBaseWeapon::CanReload() const
{
	return CurrentAmmo.Bullets < DefaultAmmo.Bullets && CurrentAmmo.Clips>0;
	// ������ ����������� ���� ���������� �������� ������ ���������� � ��������� > 0
}


// ������� ��������� ��������� � �������
void ASTUBaseWeapon::LogAmmo()
{
	FString AmmoInfo = "Ammo: " + FString::FromInt(CurrentAmmo.Bullets) + " / ";
	AmmoInfo += " Magazine: ";
	AmmoInfo += CurrentAmmo.Infinite ? "Infinite" : FString::FromInt(CurrentAmmo.Clips);

	UE_LOG(LogBaseWeapon, Warning, TEXT("%s"),*AmmoInfo);

}

// true -  ������� ������
bool ASTUBaseWeapon::IsAmmoFull() const
{
	return CurrentAmmo.Clips == DefaultAmmo.Clips &&
		CurrentAmmo.Bullets == DefaultAmmo.Bullets;

}

// ��������� ������� � �������, ����� ��� �����������
bool  ASTUBaseWeapon::TryToAddAmmo(int32 ClipsAmount)
{
	// ���� ������� ����������, ������ ���������, ��� ������� 0 ���������
	if (CurrentAmmo.Infinite || IsAmmoFull() || ClipsAmount <= 0) return false;

	// ������� = 0, �������� = 0
	if (IsAmmoEmpty())
	{
		UE_LOG(LogBaseWeapon, Warning, TEXT(" Ammo was empty"));
		CurrentAmmo.Clips = FMath::Clamp(CurrentAmmo.Clips + ClipsAmount, 0, DefaultAmmo.Clips + 1);
		// CurrentAmmo.Clips + ClipsAmount - ������������ ����� ���������
		// 0                     - ������ ������� ���������
		// DefaultAmmo.Clips + 1 - ������� ������� ���������

		// ������������, ������� �����������
		OnClipEmpty.Broadcast(this);
	}
	else 
    // ���������� ��������� ������ �������������
	if (CurrentAmmo.Clips<DefaultAmmo.Clips)
	{
		// ��������� � ���������� ����� ���������� ��������
		const auto NextClipsAmount = CurrentAmmo.Clips + ClipsAmount;

		// ���� ��������� ��������� ������ ����������� ����������
		if (DefaultAmmo.Clips - NextClipsAmount >=0)
		{
			CurrentAmmo.Clips = NextClipsAmount;
			UE_LOG(LogBaseWeapon, Warning, TEXT(" Clips were added"));
		}
		else
		{
			CurrentAmmo.Clips = DefaultAmmo.Clips;
			CurrentAmmo.Bullets = DefaultAmmo.Bullets;
			UE_LOG(LogBaseWeapon, Warning, TEXT(" Ammo is full"));
		}

	}
	else // ���������� ��������� = ������������� �� ������� ������������
	{
		CurrentAmmo.Bullets = DefaultAmmo.Bullets;
		UE_LOG(LogBaseWeapon, Warning, TEXT(" Bullets were added"));
	}
	return true;

}
