// My Shoot Them Up Game , All Rights Reserved
// � STUBaseWeapon.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUCoreType.h"
#include "STUBaseWeapon.generated.h"


class USkeletalMeshComponent; // Forward declaration


UCLASS()
class MYSHOOTTHEMUP_API ASTUBaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	ASTUBaseWeapon();

	// ������ ��������, ��������� WeaponComponent � ��� ��� ����������� �������
	FOnClipEmptySignature OnClipEmpty;

	// ������ ����������� �.�. ��� ������ ������ (�����������) ����� �������������� ���� ������� 
	virtual	void StartFire(); // ����� �������� �� ������ 
	virtual	void StopFire();  // ���� �������� �� ������ 
	void ChangeClip();        // ������ ������� �� �����, WeaponComponent �������� ������� ���� ����� �����������

	bool CanReload() const;  // ����� �� ������ �����������

	FWeaponUIData GetUIData() const { return UIData; };
	// ������� ��� ��������� ��������� � �������� ������ �.� ��� ��������� � protected ������

	FAmmoData GetAmmoData() const { return CurrentAmmo; };
	// ������� �������� ������ ��������� ���������� ������� ���������� ��������, ��� ������ ����� widget

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
    USkeletalMeshComponent* WeaponMesh;        // ���������� ��� Mesh ������

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite);
    FName MuzzleSocketName = "MuzzleSocket";   // ��� ������

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    float TraceMaxDistance = 1500.0f; // ���������� �������� 1500 �� = 15�

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	FAmmoData DefaultAmmo {15,10,false};  // ������� ������ ��������� FAmmoData, ��������� ��� ���������� �������

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	FWeaponUIData UIData;   // FWeaponUIData ��������� ������ ������ ������ � �������
	                        // ��� ������� ���� ������ � �� �������������� ��������� �� ������
	
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

	// ��������� ���������� ��������, ���������� ����� ������� ��������
	void DecreaseAmmo();

	// true ����� ������� ��������� ������, ���������� ��������� � �������� = 0
	bool IsAmmoEmpty() const;

	// true ����� ������� ������� ������
	bool IsClipEmpty() const;

	// ������� ��������� ��������� � �������
	void LogAmmo();

private:
	// ������ ��� ������������� ������ c++ ������, �� ������ ���� ����� � ��
	// ������ ������� ���������� ��������, ���������
	FAmmoData CurrentAmmo;

};
