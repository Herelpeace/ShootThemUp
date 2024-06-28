// My Shoot Them Up Game , All Rights Reserved
// В STUPlayerHUDWidget.h

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
	
	// функция которую будем вызывать в БП и получать текущий уровень здоровья
	UFUNCTION(BlueprintCallable, Category = "UI")
	float GetHealthPercent() const;

	// возвращает UIData текущего оружия, будем вызывать в БП
	UFUNCTION(BlueprintCallable, Category = "UI")
	bool GetCurrentWeaponUIData(FWeaponUIData& UIData) const;

	// возвращает значение структуры CurrentAmmo (патроны, магазины) текущего оружия
	UFUNCTION(BlueprintCallable, Category = "UI")
	bool GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const;

	// true когда персонаж жив, для виджетов
	UFUNCTION(BlueprintCallable, Category = "UI")
	bool IsPlayerAlive() const;

	// true в режиме наблюдателя, для виджетов
	UFUNCTION(BlueprintCallable, Category = "UI")
	bool IsPlayerSpectating() const;

	UFUNCTION(BlueprintImplementableEvent, Category = "UI")
	void OnTakeDamage(); // Event функция для вызова в БП, event срабатывает каждый раз при изменении здоровья

	virtual bool Initialize() override;  // подписываемся на делегат OnHealthChanged (float Health)

private:
	void OnHealthChanged(float Health, float HealthDelta );  // для бинда на делегат Health компонента
	
};
