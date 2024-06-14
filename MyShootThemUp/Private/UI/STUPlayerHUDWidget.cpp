// My Shoot Them Up Game , All Rights Reserved
// � STUPlayerHUDWidget.cpp


#include "UI/STUPlayerHUDWidget.h"
#include "Components/STUHealthActorComponent.h"  
#include "Components/STUWeaponComponent.h"  


// ������� ��� ������ � ��, ���������� ������� �������� ���������
float USTUPlayerHUDWidget::GetHealthPercent() const
{
	const auto HealthComponent = GetHealthComponent();

	if (!HealthComponent) return 0.0f;

	return HealthComponent->GetHealthPercent();

}


// ������� ��� ������ � ��, ���������� ��������� FWeaponUIDat ���������� ������ ������ � �������
bool USTUPlayerHUDWidget::GetCurrentWeaponUIData(FWeaponUIData& UIData) const
{
	// �������� ��������� �� weaponComponent
	const auto WeaponComponent = GetWeaponComponent();

	if (!WeaponComponent) return false;

	return WeaponComponent->GetCurrentWeaponUIData(UIData);
}


bool USTUPlayerHUDWidget::GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const
{
	// �������� ��������� �� weaponComponent
	const auto WeaponComponent = GetWeaponComponent();

	if (!WeaponComponent) return false;

	return WeaponComponent->GetCurrentWeaponAmmoData(AmmoData);

}

USTUWeaponComponent* USTUPlayerHUDWidget::GetWeaponComponent() const
{
	// �������� ��������� �� ������ ������
	const auto Player = GetOwningPlayerPawn();
	// GetOwningPlayerPawn() - ������� ���������� ��������� �� Pawna, � ��������

	if (!Player) return nullptr;

	// �������� ��������� �� ��������� ������
	const auto Component = Player->GetComponentByClass(USTUWeaponComponent::StaticClass());
	// GetComponentByClass                     - ���������� ��������� �� UActor ��������, ��������� ��� ����� ���������� ������� ����� �����
	// USTUWeaponComponent::StaticClass()      - �.�. WeaponComponent ����� ������ C++ ������, �� ���������� ������ ������                                                    

	// ��������� ��������� �� UActor � ��������� ����������� ����������
	const auto WeaponComponent = Cast<USTUWeaponComponent>(Component);
	// USTUWeaponComponent     - ��������� ��������� �������� ����� ��������
	// Component                - UActor ���������, ������� ����������

	return WeaponComponent;
}

// ����� ������� ��������� HealthComponent
USTUHealthActorComponent* USTUPlayerHUDWidget::GetHealthComponent() const
{
	// �������� ��������� �� ������ ������
	const auto Player = GetOwningPlayerPawn();
	// GetOwningPlayerPawn() - ������� ���������� ��������� �� Pawna, � ��������

	if (!Player) return nullptr;

	// �������� ��������� �� ��������� ������
	const auto Component = Player->GetComponentByClass(USTUHealthActorComponent::StaticClass());
	// GetComponentByClass                     - ���������� ��������� �� UActor ��������, ��������� ��� ����� ���������� ������� ����� �����
	// USTUWeaponComponent::StaticClass()      - �.�. WeaponComponent ����� ������ C++ ������, �� ���������� ������ ������                                                    

	// ��������� ��������� �� UActor � ��������� ����������� ����������
	const auto HealthComponent = Cast<USTUHealthActorComponent>(Component);
	// USTUHealthComponent      - ��������� ��������� �������� ����� ��������
	// Component                - UActor ���������, ������� ����������

	return HealthComponent;

}


// true ����� �������� ���, ��� ��������
bool USTUPlayerHUDWidget::IsPlayerAlive() const
{
	// �������� �������� �������� charactera
	const auto HealthComponent = GetHealthComponent();

	return HealthComponent && !HealthComponent->isDead();
	// ��������� �� null � �������� ����� IsDead, ���� �� false ������ �������� ��� 
	// IsDead ������� �� ����� true ������ ��� ����� ������ charactera ���������� �������������
	// ���������� Pawna
	// � ��� ��� �������� ��������� ����� 0 ������ ���� HealthComponent = false

}

// true � ������ �����������, ��� ��������
bool USTUPlayerHUDWidget::IsPlayerSpectating() const
{
	// ��������� �������� ����������� ������ � ��������
	const auto Controller = GetOwningPlayer();

	return Controller && Controller->GetStateName() == NAME_Spectating;

	// � STUBaseCharacter ����� ������ ��������� �� ������ ���������� �� NAME_Spectating (���������� unreal)
	// � ������ ������ ��������� �������� �� ��� ����������� NAME_Spectating

}


