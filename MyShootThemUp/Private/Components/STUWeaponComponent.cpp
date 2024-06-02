// My Shoot Them Up Game , All Rights Reserved
// � STUWeaponComponent.cpp


#include "Components/STUWeaponComponent.h"
#include "Weapon/STUBaseWeapon.h"                     // ��� ����� ������
#include "GameFramework/Character.h"                  // ��� ��������� ���� � �������� ������������� ������

// Sets default values for this component's properties
USTUWeaponComponent::USTUWeaponComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void USTUWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentWeaponIndex = 0; // ������ �������� ������ � ������� Weapons

	// ����� ������ ��� ������ ����, �� ����� ���������
	SpawnWeapons();

	// ������������� ������� ������ � ����� ���������
	EquipWeapon(CurrentWeaponIndex);

}

// ������� ������ �� ����� ����� ����������� ���������
void USTUWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	CurrentWeapon = 0;

	for (auto Weapon:Weapons)
	{
		// ����������� ������ ������ �� ���������
		Weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform );
		// ������� ������ ������
		Weapon->Destroy();
	}

	// ������� ������
	Weapons.Empty();

	Super::EndPlay(EndPlayReason);

}


// ������� ������ ����� ������ � ������������ ��� � ��������� �� �����
void USTUWeaponComponent::SpawnWeapons()
{
	// �������� ��������� �� Character� � �������� ������������� ������
	ACharacter* Character = Cast<ACharacter>(GetOwner());

	if (!Character|| !GetWorld())	return;

	// ���������� �������� ������� ������ ����������� � ��������� � ������������ �� � ���������
	for (auto WeaponClass : WeaponClasses)  // � WeaponClass ���������� ����������� �������� ������� WeaponClasses?
	{
		auto Weapon = GetWorld()->SpawnActor<ASTUBaseWeapon>(WeaponClass);
		// Spawn ������, ����� ������ CurrentWeapon ���������� ���� �������
		// ASTUBaseWeapon - ����� ������
		// WeaponClass    - ���������� ���� ASTUBaseWeapon
		// ��������� ��������� �� ����������� ������ � ���������� Weapon

		if (!Weapon)   continue;

		// ������������ ������ ����������� ���������
		Weapon->SetOwner(Character);

		// ��������� ������������ ������ � ������ Weapons
		Weapons.Add(Weapon);

		// ������������ ������ ������ � ������ ��������� �� �����
		AttachWeaponToSocket(Weapon, Character->GetMesh(), WeaponArmorySocketName);
		// Weapon - ��������� �� ������ ������� ����� ������������ � ���������
		// Character->GetMesh() - �� ���������

	}

	// CurrentWeapon->SetOwner(GetOwner());
	//CurrentWeapon->SetOwner(Character);
	// ���������� CurrentWeapon, ��������� ���������, ����� ����� ���� �������� ������ � ������ � ��������� Line Trace
	// ������ ��������� ����� ����� ��������� GetOwner() ��� ����� ���������� Character ( ACharacter* Character = Cast<ACharacter>(GetOwner());)
}


// �������������� ������ ������ � ������ ���������
void USTUWeaponComponent::AttachWeaponToSocket(ASTUBaseWeapon* Weapon, USceneComponent* SceneComponent , const FName& SocketName )
{
	if (!Weapon || !SceneComponent) return;

	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	// ��������� ��������� ���� FAttachmentTransformRules, ��� �������� � �������� ��������� � �������
	// AttachToComponent()

	//CurrentWeapon->AttachToComponent(Character->GetMesh(), AttachmentRules, WeaponAttachPointName);  ������ ������� 
	
	// ������� ������������� ������ ������ � ������ ���������
	Weapon->AttachToComponent(SceneComponent, AttachmentRules, SocketName);
	// SceneComponent           - �������� ���, �� ���� ��� ������������ ����� ����. Character->GetMesh()
	// AttachmentRules          - ���������� Attachment rools
	// SocketName               - �������� ������, ������������
}

// ������� ������������� ������� ������ � ���� ���������, ��������� ������ ��� ������� Weapons
void USTUWeaponComponent::EquipWeapon(int32 WeaponIndex)
{
	// �������� ��������� �� Character� � �������� ������������� ������
	ACharacter* Character = Cast<ACharacter>(GetOwner());

	if (!Character) return;

	// ��� ��������� ������ ������� ������� ������� ������ �� �����
	if (CurrentWeapon)
	{
		// ������������� ��������
		CurrentWeapon->StopFire();

		// ������������ ������ ������ � ������ ��������� �� �����
		AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponArmorySocketName);
		// Weapon - ��������� �� ������ ������� ����� ������������ � ���������
		// Character->GetMesh() - �� ���������
	}

	// � CurrentWeapon ���������� ��������� �� ������� ������
	CurrentWeapon = Weapons[WeaponIndex];

	// ������������ ��� � ����� 
	AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(),WeaponEquipSocketName);
}


// ����� ��������
void USTUWeaponComponent::StartFire()
{
	if (!CurrentWeapon) return;

	// �� ������ STUBaseWeapon.h �������� ������� StartFire
	CurrentWeapon->StartFire();
}
// StartFire()


// ���� ��������
void USTUWeaponComponent::StopFire()
{
	if (!CurrentWeapon) return;

	// �� ������ STUBaseWeapon.h �������� ������� StopFire
	CurrentWeapon->StopFire();
}
// StopFire()

// ����� ������
void USTUWeaponComponent::NextWeapon()
{
	CurrentWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
	// ����������� ������ �������� ������ �� 1
	// ����� �� ������ �� ������ �������, ����� �� ����� �� ��� �������
	// Weapons.Num() - ���������� ��������� � ������� Weapons

	// ������ ������ �� ���������
	EquipWeapon(CurrentWeaponIndex);

}