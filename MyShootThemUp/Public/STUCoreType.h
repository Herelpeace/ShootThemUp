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
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float);