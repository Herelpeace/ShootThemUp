// My Shoot Them Up Game , All Rights Reserved
// � STUPlayerHUDWidget.h

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUCoreType.h"
#include "STUPlayerHUDWidget.generated.h"


UCLASS()
class MYSHOOTTHEMUP_API USTUPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	
	// ������� ������� ����� �������� � �� � �������� ������� ������� ��������
	UFUNCTION(BlueprintCallable, Category = "UI")
	float GetHealthPercent() const;

	// ���������� UIData �������� ������, ����� �������� � ��
	UFUNCTION(BlueprintCallable, Category = "UI")
	bool GetCurrentWeaponUIData(FWeaponUIData& UIData) const;

	// ���������� �������� ��������� CurrentAmmo (�������, ��������) �������� ������
	UFUNCTION(BlueprintCallable, Category = "UI")
	bool GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const;

	// true ����� �������� ���, ��� ��������
	UFUNCTION(BlueprintCallable, Category = "UI")
	bool IsPlayerAlive() const;

	// true � ������ �����������, ��� ��������
	UFUNCTION(BlueprintCallable, Category = "UI")
	bool IsPlayerSpectating() const;

	UFUNCTION(BlueprintImplementableEvent, Category = "UI")
	void OnTakeDamage(); // Event ������� ��� ������ � ��, event ����������� ������ ��� ��� ��������� ��������

	virtual bool Initialize() override;  // ������������� �� ������� OnHealthChanged (float Health)

private:
	void OnHealthChanged(float Health, float HealthDelta );  // ��� ����� �� ������� Health ����������
	
};
