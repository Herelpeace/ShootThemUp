// My Shoot Them Up Game , All Rights Reserved
// � STURifleWeapon.h

#pragma once

#include "CoreMinimal.h"
#include "Weapon/STUBaseWeapon.h"
#include "STURifleWeapon.generated.h"

class USTUWeaponFXComponent;

UCLASS()
class MYSHOOTTHEMUP_API ASTURifleWeapon : public ASTUBaseWeapon
{
	GENERATED_BODY()

public:
	ASTURifleWeapon(); // ����������� ������, ����� ��� ��������� USTUWeaponFXComponent

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float TimeBetweenShots = 0.1f;    // ����� ����� ����������

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float BulletSpread = 1.5f;        // �������� ���� ������ �������� ��� ��������� (������ ���� = �������� �� 2)

	virtual void BeginPlay() override;  // �������������� ������� BeginPlay, ��� Check ���������� WeaponFXComponent
	virtual	void StartFire() override;  // �������������� ����� �������� �� ������ 
	virtual	void StopFire()  override;  // �������������� ���� �������� �� ������ 

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float DamageAmount = 10.0f;       // Damage ��������� ������

	UPROPERTY(VisibleAnywhere, Category = "VFX") // ��������� ������ VFX � ������� ���������� ���� �������� � USTUWeaponFXComponent
	USTUWeaponFXComponent* WeaponFXComponent;     // �������� FX � ��������� �� ��������

	virtual void MakeShot() override;  // �������������� ������� ������ ��������

	// ��������� ��������� � �������� ���������� ��� �������� �����
	virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const override;

private:
	// ���������� ��� �������
	FTimerHandle ShotTimerHandle;

	// ��������� ����� Damage, ������
	void MakeDamage(FHitResult& HitResult);
	
};
