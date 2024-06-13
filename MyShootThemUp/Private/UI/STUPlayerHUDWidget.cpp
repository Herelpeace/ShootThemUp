// My Shoot Them Up Game , All Rights Reserved
// � STUPlayerHUDWidget.cpp


#include "UI/STUPlayerHUDWidget.h"
#include "Components/STUHealthActorComponent.h"  
#include "Components/STUWeaponComponent.h"  


// ������� ��� ������ � ��, ���������� ������� �������� ���������
float USTUPlayerHUDWidget::GetHealthPercent() const
{
	// �������� ��������� �� ������ ������
	const auto Player = GetOwningPlayerPawn();
	// GetOwningPlayerPawn() - ������� ���������� ��������� �� Pawna, � ��������

	if (!Player) return 0.0f;

	// �������� ��������� �� ��������� ��������, Health Component
	const auto Component = Player->GetComponentByClass(USTUHealthActorComponent::StaticClass());
	// GetComponentByClass                     - ���������� ��������� �� UActor ��������, ��������� ��� ����� ���������� ������� ����� �����
	// USTUHealthActorComponent::StaticClass() - �.�. Health Component ����� ������ C++ ������, �� ���������� ������ ������                                                    

	// ��������� ��������� �� UActor � ��������� ����������� ����������
	const auto HealthComponent = Cast<USTUHealthActorComponent>(Component);
	// USTUHealthActorComponent - ��������� ��������� �������� ����� ��������
	// Component                - UActor ���������, ������� ����������

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