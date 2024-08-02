#pragma once

// � STUCoreType.h

#include "STUCoreType.generated.h"
// �������� ������������ ����� �������� � ��������

class ASTUBaseWeapon;  // forward declaration

// ��� STUBaseWeapon
// ������� ��������� WeaponComponent � ��� ��� ����������� �������
// ��� ������ �������� �������� ��������� �� ������ ������ ���������� �����������
DECLARE_MULTICAST_DELEGATE_OneParam(FOnClipEmptySignature, ASTUBaseWeapon*)


// ��� STUBaseWeapon
// ��������� � ������� ������ ���������� �������� � ��������
USTRUCT(BlueprintType)
struct FAmmoData
{
	GENERATED_USTRUCT_BODY()

	// ���������� �������� � ��������, ���������� ����� ������� ��������������
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	int32 Bullets;

	// ���������� ��������� � �������� ������, ���������� �����������
	// �������� ��� �������������� ����� Infinite = false, �.� ����� ��������� ����������
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon", meta = (EditCondition = "!Infinite"))
	int32 Clips;

	// �������� ����� ��������� ��� ���
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	bool Infinite;
};


// ��� STUWeaponComponent
// ��������� � ������� ������ ����� ������ � ��������������� ��� �������� �����������
// � ��������� ����� ���� � ������� ������ ������������� ���������������� ��
USTRUCT(BlueprintType)
struct FWeaponData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")        // � ��������� ����� ?
	TSubclassOf<ASTUBaseWeapon> WeaponClass;  // ���������� ������ ������

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	UAnimMontage* ReloadAnimMontage;   // � ���������� ����� ������� �������� ����������� ��� ������� ������
};

// ��������� ������ ������ ������ � �������
USTRUCT(BlueprintType)
struct FWeaponUIData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	UTexture2D* MainIcon;   // ���������� ��� ������ ������
	// UTexture2D - ��� ������ ��� �������� ��������

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	UTexture2D* CrossHairIcon;   // ���������� ��� ������ �������
};


// ��� STUHealthActorComponent
// ������� ��������� ��� �������� ��� ���
// �������� ������ � �++
// ��� �������� ���������� � ����� F
DECLARE_MULTICAST_DELEGATE(FOnDeathSignature);

// ��� STUHealthActorComponent
// ������� ������� � 1 ����������, ��� FOnHealthChanged, ��� ���������� float
// �������� ������� ����� ���������� ��������� Health
// �������� ��������� �������� �� 2 ���������, �������� float HealthDelta 
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnHealthChangedSignature, float, float);


// VFX

class UNiagaraSystem; 

// ������ �������� ��� ������� ������
USTRUCT(BlueprintType)
struct FDecalData
{
	GENERATED_USTRUCT_BODY()

	// �������� ������
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	UMaterialInterface* Material;

	// ������ ������
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	FVector Size = FVector(10.0f);
	// FVector(10.0f) - �����������, �������������� ��� ���������� FVectora ����� ���������

	// ����� ����� ������
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	float LifeTime = 5.0f;

	// ����� �� ������� ������ ����� ������������ (����������� ����������)
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	float FadeOutTime = 0.7f;

};

// ���������� niagara ������ � ������
USTRUCT(BlueprintType)
struct FImpactData
{
	GENERATED_USTRUCT_BODY()

	// ��������� �� niagara �������
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	UNiagaraSystem* NiagaraEffect;

	// c�������� � ����������� ������
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	FDecalData DecalData;

};

// ��������� GameMode
USTRUCT(BlueprintType)
struct FGameData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game", meta = (ClampMin = "1", CalampMax = "100"))
	int32 PlayersNum = 2;	// ���������� �������

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game", meta = (ClampMin = "1", ClampMax = "10"))
	int32 RoundNum = 4;		// ���������� �������


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game", meta = (ClampMin = "3", ClampMax = "300"))
	int32 RoundTime = 10;		// ����� ������ ������ � ��������



};