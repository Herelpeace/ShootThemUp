// My Shoot Them Up Game , All Rights Reserved
// STUWeaponComponent.cpp


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

	// ����� ������ ��� ������ ����
	SpawnWeapon();

}

// ������� ������ ����� ����� � ������������ ��� � ���������
void USTUWeaponComponent::SpawnWeapon()
{
	if (!GetWorld())    return;

	// �������� ������ �� Character � �������� ������������� ������
	ACharacter* Character = Cast<ACharacter>(GetOwner());

	if (!Character)	return;



	CurrentWeapon = GetWorld()->SpawnActor<ASTUBaseWeapon>(WeaponClass);
	// Spawn ������, ����� ������ CurrentWeapon ���������� ���� �������
	// ASTUBaseWeapon - ����� ������
	// WeaponClass    - ���������� ���� ASTUBaseWeapon
	// ��������� ��������� �� ����������� ������ � ���������� Weapon

	if (!CurrentWeapon)   return;


	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	// ��������� ��������� ���� FAttachmentTransformRules, ��� �������� � �������� ��������� � �������
	// AttachToComponent()

	CurrentWeapon->AttachToComponent(Character->GetMesh(), AttachmentRules, WeaponAttachPointName);  
	// ������������� ������ � Mesh� ��������� ����� ����� WeaponSoket
	// SnapToTarget - ����� ��������� ������������� �� ���������� � �������� ��� ������������
	// false        - �������� bInWeldSimulatedBodies - �������� �� ���������� ��������� ����� ��� ����
	// ����������� ���� � �����
	// WeaponAttachPointName    - �������� ����������, ������ ��� ������
	// Character->GetMesh()     - ��������� �� SceletalMesh ��������� charactera
	// AttachmentRules          - ���������� Attachment rools
	// "WeaponSoket"            - �������� ������, ������������

	// CurrentWeapon->SetOwner(GetOwner());
	CurrentWeapon->SetOwner(Character);
	// ���������� CurrentWeapon, ��������� ���������, ����� ����� ���� �������� ������ � ������ � ��������� Line Trace
	// ������ ��������� ����� ����� ��������� GetOwner() ��� ����� ���������� Character ( ACharacter* Character = Cast<ACharacter>(GetOwner());)
}


void USTUWeaponComponent::Fire()
{
	if (!CurrentWeapon) return;

	// �� ������ STUBaseWeapon.h �������� ������� Fire
	CurrentWeapon->Fire();
}
// Fire()