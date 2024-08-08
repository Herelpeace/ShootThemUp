// My Shoot Them Up Game , All Rights Reserved
// � STURifleWeapon.h

#pragma once

#include "CoreMinimal.h"
#include "Weapon/STUBaseWeapon.h"
#include "STURifleWeapon.generated.h"

class USTUWeaponFXComponent;
class UNiagaraSystem;
class UNiagaraComponent;



UCLASS()
class MYSHOOTTHEMUP_API ASTURifleWeapon : public ASTUBaseWeapon
{
	GENERATED_BODY()

public:
	ASTURifleWeapon(); // ����������� ������, ����� ��� ��������� USTUWeaponFXComponent

	virtual void BeginPlay() override;  // �������������� ������� BeginPlay, ��� Check ���������� WeaponFXComponent
	virtual	void StartFire() override;  // �������������� ����� �������� �� ������ 
	virtual	void StopFire()  override;  // �������������� ���� �������� �� ������ 

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float TimeBetweenShots = 0.1f;    // ����� ����� ����������

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float BulletSpread = 1.5f;        // �������� ���� ������ �������� ��� ��������� (������ ���� = �������� �� 2)

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float DamageAmount = 10.0f;       // Damage ��������� ������

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	UNiagaraSystem* TraceFX;          // '������ �����������

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	FString TraceTargetName = "TraceTarget";	// �������� ���������� � �������� ������ �������

	UPROPERTY(VisibleAnywhere, Category = "VFX") // ��������� ������ VFX � ������� ���������� ���� �������� � USTUWeaponFXComponent
	USTUWeaponFXComponent* WeaponFXComponent;     // �������� FX � ��������� �� ��������

	virtual void MakeShot() override;  // �������������� ������� ������ ��������

	// ��������� ��������� � �������� ���������� ��� �������� �����
	virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const override;

private:
	// ���������� ��� �������
	FTimerHandle ShotTimerHandle;

	UPROPERTY()
	UNiagaraComponent* MuzzleFXComponent;

	// ��������� ����� Damage, ������
	void MakeDamage(FHitResult& HitResult);
	
	// ������� niagara system
	void InitMuzzleFX();

	// ������������� ��������� �������
	void SetMuzzleFXVisibility(bool Visibility);

	// ����� ������� �����������
	void SpawnTraceFX(const FVector& TraceStart, const FVector& TraceEnd);

	// �������� ������� ���������� (��� ����������)
	AController* GetController() const;
	

};
