// My Shoot Them Up Game , All Rights Reserved
// � STUHealthActorComponent.h

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

	// ������� ������ ��������
	FOnDeathSignature onDeath;
	FOnHealthChangedSignature OnHealthChanged;

	UFUNCTION(BlueprintCallable) // ������ ������� ��������� � BP
	bool isDead() const { return FMath::IsNearlyZero(Health); }; // ������� ������ true ����� �������� = 0

	// ���������� ���������� �����. ��� ������ �����
	UFUNCTION(BlueprintCallable, Category = "UI")
	float GetHealthPercent() const { return Health / MaxHealth; }



	float GetHealth() const { return Health; }

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,Category = "Health",  meta = (ClampMin = "0.0", ClampMax = "1000.0"))
    float MaxHealth = 100.0f;                          // ������������ �������� �����

	virtual void BeginPlay() override;

	// ���/���� ������������������ ��������
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal")
	bool AutoHeal = true;

	// �������� ����������� ��������
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal", meta = (EditCondition = "AutoHeal"))
	float HealUpdateTime = 1.0f;      // 1 �������

	// �������� ����� ��������������� ��������
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal", meta = (EditCondition = "AutoHeal"))
	float HealDelay = 3.0f;   // ���� 3 ������� � �������� ��������������� ��������

	// ���������� �������� ������������ �� 1 ���
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal", meta = (EditCondition = "AutoHeal"))
	float HealModifier = 5.0f;


private:
	float Health = 0.0f;                                // ���������� ���������� �� ��������

	// ��������� ���������� �������
	FTimerHandle HealTimerHandle;

	UFUNCTION()                                        // ������� ��������� �����
	void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType,
	    class AController* InstigatedBy, AActor* DamageCauser);

	void HealUpdate(); // ������� ����������� �������� ��� ������ ������������ �������

	// ������� ��������� ��������
	void SetHealth(float NewHealth);


		
};
