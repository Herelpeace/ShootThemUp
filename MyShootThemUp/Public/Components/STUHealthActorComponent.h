// My Shoot Them Up Game , All Rights Reserved
// STUHealthActorComponent.h

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
	bool isDead() const { return FMath::IsNearlyZero(Health); }; // функци€ вернет true когда здоровье = 0

	float GetHealth() const { return Health; }

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,Category = "Health",  meta = (ClampMin = "0.0", ClampMax = "1000.0"))
    float MaxHealth = 100.0f;                          // максимальное значение жизни

	virtual void BeginPlay() override;

	// вкл/выкл автовосстановление здоровь€
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal")
	bool AutoHeal = true;

	// скорость прибавлени€ здоровь€
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal", meta = (EditCondition = "AutoHeal"))
	float HealUpdateTime = 1.0f;      // 1 секунда

	// задержка перед восстановлением здоровь€
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal", meta = (EditCondition = "AutoHeal"))
	float HealDelay = 3.0f;   // ждем 3 секунды и начинаем восстанавливать здоровье

	// количество здоровь€ прибавл€емое за 1 раз
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal", meta = (EditCondition = "AutoHeal"))
	float HealModifier = 5.0f;


private:
	float Health = 0.0f;                                // переменна€ отвечающа€ за здоровье

	// объ€вл€ем переменную таймера
	FTimerHandle HealTimerHandle;

	UFUNCTION()                                        // функци€ нанесени€ урона
	void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType,
	    class AController* InstigatedBy, AActor* DamageCauser);

	void HealUpdate(); // функци€ прибавлени€ здоровь€ при каждом срабатывании таймера

	// функци€ установки здоровь€
	void SetHealth(float NewHealth);


		
};
