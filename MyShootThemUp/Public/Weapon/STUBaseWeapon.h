// My Shoot Them Up Game , All Rights Reserved
// � STUBaseWeapon.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUBaseWeapon.generated.h"



class USkeletalMeshComponent; // Forward declaration

UCLASS()
class MYSHOOTTHEMUP_API ASTUBaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	ASTUBaseWeapon();

	// ������ ����������� �.�. ��� ������ ������ (�����������) ����� �������������� ���� ������� 
	virtual	void StartFire(); // ����� �������� �� ������ 
	virtual	void StopFire();  // ���� �������� �� ������ 

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
    USkeletalMeshComponent* WeaponMesh;        // ���������� ��� Mesh ������

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite);
    FName MuzzleSocketName = "MuzzleSocket";   // ��� ������

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    float TraceMaxDistance = 1500.0f; // ���������� �������� 1500 �� = 15�

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float DamageAmount = 10.0f;       // Damage ��������� ������

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float TimeBetweenShots = 0.1f;    // ����� ����� ����������

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float BulletSpread = 1.5f;        // �������� ���� ������ �������� ��� ��������� (������ ���� = �������� �� 2)

	void MakeShot();

	virtual void BeginPlay() override;

	//������ ���������� ��������� �� ���������� �������� ������
	APlayerController* GetPlayerController() const;  

	// �������� ���������� � �������� ������
	bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;

	// ������� ���������� ��������� ������
	FVector GetMuzzleWorldLocation() const;

	// ��������� ��������� � �������� ���������� ��� �������� �����
	bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;

	// �������� ������ � ����������� (������������)
	void MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd); 

	// ��������� ����� Damage, ������
	void MakeDamage(FHitResult& HitResult);


private:

	// ���������� ��� �������
	FTimerHandle ShotTimerHandle;

};
