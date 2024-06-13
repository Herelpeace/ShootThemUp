// My Shoot Them Up Game , All Rights Reserved
// � STUWeaponComponent.cpp


#include "Components/STUWeaponComponent.h"
#include "Weapon/STUBaseWeapon.h"                     // ��� ����� ������
#include "GameFramework/Character.h"                  // ��� ��������� ���� � �������� ������������� ������
#include "Animations/STUEquipFinishedAnimNotify.h"    // ��� ����� Notify 1
#include "Animations/STUReloadFinishedAnimNotify.h"   // notify �����������
#include "Animations/AnimUtils.h"                     // �������� ��������� ������� ������ notify � �������� ������

DEFINE_LOG_CATEGORY_STATIC(LogWeaponComponent, All, All);

// ���������� ����������, ���������� ������ � ���������
constexpr static int32 WeaponNum = 2;

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

	// �������� ��� � ��������� ����������� ��� ������ ������
	checkf(WeaponData.Num() == WeaponNum, TEXT("Our character can hold only %i weapon items"), WeaponNum);

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
	for (auto OneWeaponData : WeaponData)  // � OneWeaponData ���������� ����������� �������� ������� �������� WeaponData?
	{
		auto Weapon = GetWorld()->SpawnActor<ASTUBaseWeapon>(OneWeaponData.WeaponClass);
		// Spawn ������, ����� ������ CurrentWeapon ���������� ���� �������
		// ASTUBaseWeapon               - ����� ������
		// OneWeaponData.WeaponClass    - ���� ��������� OneWeaponData, ���� ASTUBaseWeapon
		// ��������� ��������� �� ����������� ������ � ���������� Weapon

		if (!Weapon)   continue;

		// ��� ������������ �������� OnClipEmpty ����� ������� ������� OnEmptyClip � ������ ������
		Weapon->OnClipEmpty.AddUObject(this, &USTUWeaponComponent::OnEmptyClip);

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
	// �������� ������������ ������� �������
	if (WeaponIndex < 0 || WeaponIndex >= Weapons.Num())
	{
		UE_LOG(LogWeaponComponent, Warning, TEXT("Invalid Weapon Index"))
		return;
	}

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

	// ������ �������� �����������, ����� �������� ����������� ��� ���������� �������
	//CurrentReloadAnimMontage = WeaponData[WeaponIndex].ReloadAnimMontage;
	// WeaponData[WeaponIndex] - ������ ��������� � ������� ���������� ����� �������� ������ � ��� �������� �����������

	// ����� �������� ������, ��������� �� ������� �� ����������� WeaponData � ���� ���������
	// ������� ������������� �������� ������ ������
	// ����� ���������� ��������� ����� �� ��� �������� �����������

	const auto CurrentWeaponData = WeaponData.FindByPredicate([&](const FWeaponData& Data) { return Data.WeaponClass == CurrentWeapon->GetClass(); });
	// � WeaponData ���� ��������� ������� ����� ����� CurrentWeapon->GetClass(); ,�������� ������ ������
	// CurrentWeaponData - ���������� ��� ���������� ��������� ���������
	// FindByPredicate   - ������� �������, ������� ���� � ������� ������� �� �������� ���������� 
	// [&]               - ����� ����� ��������� ������� ���������� CurrentWeapon
	// [&](const FWeaponData& Data) { return Data.WeaponClass == CurrentWeapon->GetClass() - ������ ���������
	// ��� ������ ���������� � ��������� �������,�������� ��������� �� ���� �������

	// � ���������� ������� �������� ����������� �������� �������� ������ ���������� � �������
	CurrentReloadAnimMontage = CurrentWeaponData ? CurrentWeaponData->ReloadAnimMontage : nullptr;

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
	/*
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

	*/
	
	// ��������� ������� ������� ���� notify 
	auto EquipFinishedNotify = AnimUtils::FindNotifyByClass<USTUEquipFinishedAnimNotify>(EquipAnimMontage);

	// �������� ������� ���� Notify ������
	if (EquipFinishedNotify)
	{
		// ������ ������� �� �������
		EquipFinishedNotify->OnNotified.AddUObject(this, &USTUWeaponComponent::OnEquipFinished);
	}
	else
	{
		UE_LOG(LogWeaponComponent, Error, TEXT("Equip anim notify is forgotten to set"));  // �� ���������� notify � �������� ����� ������
		checkNoEntry();
	}

	for (auto OneWeaponData : WeaponData)
	{
		// ��������� ������� ������� ���� notify 
		auto ReloadFinishedNotify = AnimUtils::FindNotifyByClass<USTUReloadFinishedAnimNotify>(OneWeaponData.ReloadAnimMontage);
		// ���� ������ �� ����� ��������� � ���������� ��������
		if (!ReloadFinishedNotify)
		{
			UE_LOG(LogWeaponComponent, Error, TEXT("Reload anim notify is forgotten to set"));  // �� ���������� notify � �������� ����������� ������
			checkNoEntry();
		}

		// ������ ������� ��������� ����������� �� �������
		ReloadFinishedNotify->OnNotified.AddUObject(this, &USTUWeaponComponent::OnReloadFinished);
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

// callback ������� ������ �� ������� OnNotified, �������� � ���� ��� Charactera, ����� ������ �� ������� Notify ����������� ������ � ��������� 
void USTUWeaponComponent::OnReloadFinished(USkeletalMeshComponent* MeshComponent)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character || MeshComponent != Character->GetMesh()) return;

	// ����� ������������ ��������� ���������� ���� � ������� ���������
	ReloadAnimProgress = false;
}


// ������ true ����� ����� ��������
bool USTUWeaponComponent::CanFire() const
{
	// ���� ��������� �� ������� ������ �� ������� � �� ������������� �������� ����� ��� ��������
	return CurrentWeapon && !EquipAnimProgress && !ReloadAnimProgress;

}

// ������ true ����� ����� ������ ������
bool USTUWeaponComponent::CanEquip() const
{
	return !EquipAnimProgress && !ReloadAnimProgress;
}

// ������ true ����� ����� ��������������
bool USTUWeaponComponent::CanReload() const
{
	// ���� ��������� �� ������� ������ �� ������� � �� ������������� �������� ����� ��� �������� ��� ����������� �  ���������� �������� ������ ���������� � ��������� > 0
	return CurrentWeapon && !EquipAnimProgress && !ReloadAnimProgress && CurrentWeapon->CanReload();
}

// ����������� �� ������� �������
void USTUWeaponComponent::Reload()
{
	ChangeClip();
}

// ����������� �� ��������, callback �� ������� OnClipEmpty
void USTUWeaponComponent::OnEmptyClip()
{
	ChangeClip();
}

// ��� ������ ����������� ��������� � ���� �������
void USTUWeaponComponent::ChangeClip()
{
	if (!CanReload()) return;

	CurrentWeapon->StopFire();

	// ������� ����������� � �������� ������ 
	CurrentWeapon->ChangeClip();

	// ��������� ���� �� ����� �����������
	ReloadAnimProgress = true;

	// ����������� �������� �����������
	PlayAnimMontage(CurrentReloadAnimMontage);
}


// ���������� UIData �������� ������, ������ �������, ���������� ��������� ������ �� ������
bool USTUWeaponComponent::GetCurrentWeaponUIData(FWeaponUIData& UIData) const
{
	if (CurrentWeapon)
	{
		UIData = CurrentWeapon->GetUIData();
		return true;
	}
	return false;
}

// ���������� Current AmmoData �������� ������, ������ �������, ���������� ��������� ������ �� ������
bool USTUWeaponComponent::GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const
{
	if (CurrentWeapon)
	{
		AmmoData = CurrentWeapon->GetAmmoData();
		return true;
	}
	return false;
}