// My Shoot Them Up Game , All Rights Reserved
// � STUPlayerHUDWidget.h

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUCoreType.h"
#include "STUPlayerHUDWidget.generated.h"


class USTUWeaponComponent;  // forward declaration

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

private:
	// �.� ��� �������� ����� WeaponComponent ����� � ������ �� ������ ������ ��� ������� ����� �������
	USTUWeaponComponent* GetWeaponComponent() const;
	
};
