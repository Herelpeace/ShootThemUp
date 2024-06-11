// My Shoot Them Up Game , All Rights Reserved
// В STUHealthActorComponent.h

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUCoreType.h"
#include "STUHealthActorComponent.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYSHOOTTHEMUP_API USTUHealthActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USTUHealthActorComponent();

	// создаем объект делегата
	FOnDeathSignature onDeath;
	FOnHealthChangedSignature OnHealthChanged;

	UFUNCTION(BlueprintCallable) // делаем функцию доступной в BP
	bool isDead() const { return FMath::IsNearlyZero(Health); }; // функция вернет true когда здоровье = 0

	// возвращает количество жизни. Для полосы жизни
	UFUNCTION(BlueprintCallable, Category = "UI")
	float GetHealthPercent() const { return Health / MaxHealth; }



	float GetHealth() const { return Health; }

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,Category = "Health",  meta = (ClampMin = "0.0", ClampMax = "1000.0"))
    float MaxHealth = 100.0f;                          // максимальное значение жизни

	virtual void BeginPlay() override;

	// вкл/выкл автовосстановление здоровья
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal")
	bool AutoHeal = true;

	// скорость прибавления здоровья
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal", meta = (EditCondition = "AutoHeal"))
	float HealUpdateTime = 1.0f;      // 1 секунда

	// задержка перед восстановлением здоровья
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal", meta = (EditCondition = "AutoHeal"))
	float HealDelay = 3.0f;   // ждем 3 секунды и начинаем восстанавливать здоровье

	// количество здоровья прибавляемое за 1 раз
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal", meta = (EditCondition = "AutoHeal"))
	float HealModifier = 5.0f;


private:
	float Health = 0.0f;                                // переменная отвечающая за здоровье

	// объявляем переменную таймера
	FTimerHandle HealTimerHandle;

	UFUNCTION()                                        // функция нанесения урона
	void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType,
	    class AController* InstigatedBy, AActor* DamageCauser);

	void HealUpdate(); // функция прибавления здоровья при каждом срабатывании таймера

	// функция установки здоровья
	void SetHealth(float NewHealth);


		
};
