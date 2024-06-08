// My Shoot Them Up Game , All Rights Reserved
// � STUWeaponComponent.cpp


#include "Components/STUWeaponComponent.h"
#include "Weapon/STUBaseWeapon.h"                     // ��� ����� ������
#include "GameFramework/Character.h"                  // ��� ��������� ���� � �������� ������������� ������
#include "Animations/STUEquipFinishedAnimNotify.h"    // ��� ����� Notify

DEFINE_LOG_CATEGORY_STATIC(LogWeaponComponent, All, All);

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

	// ����������� �������� ����� ������
	InitAnimations();

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

	// ����� ������������� �������� ������ ��������� ����� �� true
	EquipAnimProgress = true;

	// �������� ����� ������
	PlayAnimMontage(EquipAnimMontage);
}

// ����� ��������
void USTUWeaponComponent::StartFire()
{
	// ��������, ������������� �� ��������
	if (!CanFire()) return;

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
	// ��������� ����� �� ������ ������ (������������� �� �������� ����� ������)
	if (!CanEquip()) return;
	CurrentWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
	// ����������� ������ �������� ������ �� 1
	// ����� �� ������ �� ������ �������, ����� �� ����� �� ��� �������
	// Weapons.Num() - ���������� ��������� � ������� Weapons

	// ������ ������ �� ���������
	EquipWeapon(CurrentWeaponIndex);
}

// ������������ ��������
void USTUWeaponComponent::PlayAnimMontage(UAnimMontage* Animation)
{
	// �������� ��������� �� Character �.� � ��� ���� ������� ������������ AnimMontage
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	
	if (!Character) return;

	// �������� ����� ������
	Character->PlayAnimMontage(Animation);
}

// ������� Notify � ������������� �� ����
void USTUWeaponComponent::InitAnimations()
{
	if (!EquipAnimMontage) return;

	// �������� �������� ������� �������� ������� Notifys. 	TArray<struct FAnimNotifyEvent> Notifies;
	// ������ ������������ �������
	const auto NotifyEvents = EquipAnimMontage->Notifies;

	// ���������� �������� �������
	for (auto NotifyEvent : NotifyEvents)
	{
		auto EquipFinishedNotify = Cast<USTUEquipFinishedAnimNotify>(NotifyEvent.Notify);

		// EquipFinishedNotify - ��������� ��������� ��������� Notify, � ��������� ����������
		// NotifyEvent.Notify  - � ���� Notify ���������� Notify
		// Cast <>             - ������ Cast �� ������ ������, ���� Cast ������ ������� ������ Notify �� ������ ������

		// �������� ������� ���� Notify ������
		if (EquipFinishedNotify)
		{
			// ������ ������� �� �������
			EquipFinishedNotify->OnNotified.AddUObject(this, &USTUWeaponComponent::OnEquipFinished);
			break;
		}
	}
}

// callback ������� ������ �� ������� OnNotified, �������� � ���� ��� Charactera, ����� ������ �� ������� Notify ����������� ������ � ��������� 
void USTUWeaponComponent::OnEquipFinished(USkeletalMeshComponent* MeshComponent)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character || MeshComponent != Character->GetMesh()) return;

	// ����� ������������ ��������� ���������� ���� � ������� ���������
	EquipAnimProgress = false;
}


// ������ true ����� ����� ��������
bool USTUWeaponComponent::CanFire() const
{
	// ���� ��������� �� ������� ������ �� ������� � �� ������������� �������� ����� ��� ��������
	return CurrentWeapon && !EquipAnimProgress;

}

// ������ true ����� ����� ������ ������
bool USTUWeaponComponent::CanEquip() const
{
	return !EquipAnimProgress;
}