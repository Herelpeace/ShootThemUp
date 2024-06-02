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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite);
    FName MuzzleSocketName = "MuzzleSocket";   // ��� ������

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    float TraceMaxDistance = 1500.0f; // ���������� �������� 1500 �� = 15�



	virtual void MakeShot();

	// ��������� ��������� � �������� ���������� ��� �������� �����
	virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;

	virtual void BeginPlay() override;

	//������ ���������� ��������� �� ���������� �������� ������
	APlayerController* GetPlayerController() const;  

	// �������� ���������� � �������� ������
	bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;

	// ������� ���������� ��������� ������
	FVector GetMuzzleWorldLocation() const;

	// �������� ������ � ����������� (������������)
	void MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd); 

};
