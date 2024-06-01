// My Shoot Them Up Game , All Rights Reserved
// � STULauncherWeapon.h

#pragma once

#include "CoreMinimal.h"
#include "Weapon/STUBaseWeapon.h"
#include "STULauncherWeapon.generated.h"

class ASTUProjectile;  // forward declaration

UCLASS()
class MYSHOOTTHEMUP_API ASTULauncherWeapon : public ASTUBaseWeapon
{
	GENERATED_BODY()

public:
	virtual	void StartFire() override;  // �������������� ����� �������� �� ������ 
	//virtual	void StopFire()  override;  // �������������� ���� �������� �� ������ 

protected:
	// ����� ������ ������� ����� �������� ��� �������� Launchera
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<ASTUProjectile> ProjectileClass;  // ������� ���������� STUProjectile �����
	                                              // ��������� �� ������ �������� ������ ��

	virtual void MakeShot() override;  // �������������� ������� ������ ��������
	
};
