// My Shoot Them Up Game , All Rights Reserved
// � STURifleWeapon.h

#pragma once

#include "CoreMinimal.h"
#include "Weapon/STUBaseWeapon.h"
#include "STURifleWeapon.generated.h"

/**
 * 
 */
UCLASS()
class MYSHOOTTHEMUP_API ASTURifleWeapon : public ASTUBaseWeapon
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float TimeBetweenShots = 0.1f;    // ����� ����� ����������

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float BulletSpread = 1.5f;        // �������� ���� ������ �������� ��� ��������� (������ ���� = �������� �� 2)

	virtual	void StartFire() override;  // �������������� ����� �������� �� ������ 
	virtual	void StopFire()  override;  // �������������� ���� �������� �� ������ 

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float DamageAmount = 10.0f;       // Damage ��������� ������

	virtual void MakeShot() override;  // �������������� ������� ������ ��������

	// ��������� ��������� � �������� ���������� ��� �������� �����
	virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const override;

private:
	// ���������� ��� �������
	FTimerHandle ShotTimerHandle;

	// ��������� ����� Damage, ������
	void MakeDamage(FHitResult& HitResult);
	
};
