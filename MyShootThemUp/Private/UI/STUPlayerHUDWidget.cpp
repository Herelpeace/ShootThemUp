// My Shoot Them Up Game , All Rights Reserved
// � STUPlayerHUDWidget.cpp


#include "UI/STUPlayerHUDWidget.h"
#include "Components/STUHealthActorComponent.h"  
#include "Components/STUWeaponComponent.h" 
#include "STUUtils.h"


// ������� ��� ������ � ��, ���������� ������� �������� ���������
float USTUPlayerHUDWidget::GetHealthPercent() const
{
	const auto HealthComponent = STUUtils::GetSTPlayerComponent<USTUHealthActorComponent>(GetOwningPlayerPawn());
	// �������� ��������� �� �������� �������� Pawna ��� ������ ��������� �������

	if (!HealthComponent) return 0.0f;

	return HealthComponent->GetHealthPercent();

}


// ������� ��� ������ � ��, ���������� ��������� FWeaponUIDat ���������� ������ ������ � �������
bool USTUPlayerHUDWidget::GetCurrentWeaponUIData(FWeaponUIData& UIData) const
{
	const auto WeaponComponent = STUUtils::GetSTPlayerComponent<USTUWeaponComponent>(GetOwningPlayerPawn());
	// �������� ��������� �� �������� WeaponComponent Pawna ��� ������ ��������� �������

	if (!WeaponComponent) return false;

	return WeaponComponent->GetCurrentWeaponUIData(UIData);
}


bool USTUPlayerHUDWidget::GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const
{
	const auto WeaponComponent = STUUtils::GetSTPlayerComponent<USTUWeaponComponent>(GetOwningPlayerPawn());
	// �������� ��������� �� �������� WeaponComponent Pawna ��� ������ ��������� �������

	if (!WeaponComponent) return false;

	return WeaponComponent->GetCurrentWeaponAmmoData(AmmoData);

}


// true ����� �������� ���, ��� ��������
bool USTUPlayerHUDWidget::IsPlayerAlive() const
{
	const auto HealthComponent = STUUtils::GetSTPlayerComponent<USTUHealthActorComponent>(GetOwningPlayerPawn());
	// �������� ��������� �� �������� �������� Pawna ��� ������ ��������� �������

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


