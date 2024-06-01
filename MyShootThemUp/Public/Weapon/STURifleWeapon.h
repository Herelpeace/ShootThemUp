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
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float TimeBetweenShots = 0.1f;    // ����� ����� ����������

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float BulletSpread = 1.5f;        // �������� ���� ������ �������� ��� ��������� (������ ���� = �������� �� 2)

	virtual	void StartFire() override;  // �������������� ����� �������� �� ������ 
	virtual	void StopFire()  override;  // �������������� ���� �������� �� ������ 

protected:
	virtual void MakeShot() override;  // �������������� ������� ������ ��������

	// ��������� ��������� � �������� ���������� ��� �������� �����
	virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const override;

private:
	// ���������� ��� �������
	FTimerHandle ShotTimerHandle;

	
};
