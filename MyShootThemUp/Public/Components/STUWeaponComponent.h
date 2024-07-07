// My Shoot Them Up Game , All Rights Reserved
// � STUWeaponComponent.h

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUCoreType.h"
#include "STUWeaponComponent.generated.h"


class ASTUBaseWeapon; // Forward Declaration ������ ������ ������


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYSHOOTTHEMUP_API USTUWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USTUWeaponComponent();

    virtual void StartFire();  // ����� �������� ������ 
    void StopFire();   // ���� �������� ������ 
	virtual void NextWeapon(); // ��� ����� ������
	void Reload();     // �����������
	bool GetCurrentWeaponUIData(FWeaponUIData& UIData) const; // ���������� UIData �������� ������ (������ ������� UIData ������������� ��������)
	bool GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const; // ���������� ��������� CurrentAmmo (������ ������� AmmoData ������������� ��������)
	bool TryToAddAmmo(TSubclassOf<ASTUBaseWeapon> WeaponType, int32 ClipsAmount); // ��������� ��������, ���������� bool

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon") // � ��������� ����� ������ � ������� +
	TArray<FWeaponData> WeaponData;	     // ������ �������� �������� ����� ������ � ��� ��������

	// ������� EndPlay ���������� � ������� ���������� ��� ������ � � ������������� ������ 
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponEquipSocketName = "WeaponSocket";       // ����� ��� ������������� ������ � ����

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponArmorySocketName = "ArmorySocket";       // ����� ��� ������������� ������ �� �����

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* EquipAnimMontage;                     // ��������� �� �������� ����� ������, ��� ��������� ��������� ��� �� ������������� �� �������
	                                                    // Notify �� ����� AnimMontage

	UPROPERTY()
	// ��������� �� ������� ������, ���������� ������ �������
	ASTUBaseWeapon* CurrentWeapon = nullptr;

	UPROPERTY()
	TArray<ASTUBaseWeapon* > Weapons;
	// ������ ���������� �� ������ ���� ASTUBaseWeapon - ������ ������
	// ��� ����� ������ �� ������ �������� ��������� CurrentWeapon �� �������� ��������� �� ������� �������

	int32 CurrentWeaponIndex = 0;
	// ������ �������� ������� �� ������� � ������ ������ ��������� ��������� CurrentWeapon 

	// ������ true ����� ����� ��������
	bool CanFire() const;

	// ������ true ����� ����� ������ ������
	bool CanEquip() const;

	// ������� ������������� ������� ������ � ���� ���������, ��������� ������ ��� ������� Weapons
	void EquipWeapon(int32 WeaponIndex);


private:
	UPROPERTY()
	UAnimMontage* CurrentReloadAnimMontage = nullptr;
	// ������� �������� ����������� 

	// ����, ����� ����� �������� true ��� ����� ������ � ��������,�� �� �������� ���������� ����� ������ ������ ��� ��������
	bool EquipAnimProgress = false;

	// ����, ����� ����� �������� true ��� ����� ������ � ��������,�� �� �������� ���������� ����� ������ ������ ��� ��������
	bool ReloadAnimProgress = false;

	void SpawnWeapons(); // ������� ������ � ������������� ������ ������ � Mesh ���������	

	// ������� ������������� ������ ������ � ������ ���������
	void AttachWeaponToSocket(ASTUBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName);

	// ������������ ��������
	void PlayAnimMontage(UAnimMontage* Animation);

	// ������� Notify � ������������� �� ����
	void InitAnimations();

	// callback ������� ������ �� ������� OnNotified ����� ������
	void OnEquipFinished(USkeletalMeshComponent* MeshComponent);

	// callback ������� ������ �� ������� OnNotified �����������
	void OnReloadFinished(USkeletalMeshComponent* MeshComponent);

	// ������ true ����� ����� ��������������
	bool CanReload() const;

	// callback �� ������� OnClipEmpty, �������� ��������� �� ������ ��������� �����������
	void OnEmptyClip( ASTUBaseWeapon* AmmoEmptyWeapon);

	// ��� ������ ����������� ��������� � ���� �������
	void ChangeClip();

};


