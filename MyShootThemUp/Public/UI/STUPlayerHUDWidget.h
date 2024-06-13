// My Shoot Them Up Game , All Rights Reserved
// В STUPlayerHUDWidget.h

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
	
	// функция которую будем вызывать в БП и получать текущий уровень здоровья
	UFUNCTION(BlueprintCallable, Category = "UI")
	float GetHealthPercent() const;


	// возвращает UIData текущего оружия, будем вызывать в БП
	UFUNCTION(BlueprintCallable, Category = "UI")
	bool GetCurrentWeaponUIData(FWeaponUIData& UIData) const;


	// возвращает значение структуры CurrentAmmo (патроны, магазины) текущего оружия
	UFUNCTION(BlueprintCallable, Category = "UI")
	bool GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const;

private:
	// т.к для виджетов нужен WeaponComponent чтобы в каждом не писать лишний код сделали общую функцию
	USTUWeaponComponent* GetWeaponComponent() const;
	
};
