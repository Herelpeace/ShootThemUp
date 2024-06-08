// My Shoot Them Up Game , All Rights Reserved
// � STUWeaponComponent.h

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUWeaponComponent.generated.h"


class ASTUBaseWeapon; // Forward Declaration ������ ������ ������

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYSHOOTTHEMUP_API USTUWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USTUWeaponComponent();

    void StartFire(); // ����� �������� ������ 
    void StopFire();  // ���� �������� ������ 
	void NextWeapon(); // ��� ����� ������

protected:
	virtual void BeginPlay() override;

	// ������� EndPlay ���������� � ������� ���������� ��� ������ � � ������������� ������ 
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")        // � ��������� ����� ������ � ������� ����� ��������� ��������
	TArray <TSubclassOf<ASTUBaseWeapon>>	WeaponClasses;  // WeaponClasses - ������ �� ������� ������

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponEquipSocketName = "WeaponSocket";       // ����� ��� ������������� ������ � ����

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponArmorySocketName = "ArmorySocket";       // ����� ��� ������������� ������ �� �����

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* EquipAnimMontage;                     // ��������� �� �������� ����� ������, ��� ��������� ��������� ��� �� ������������� �� �������
	                                                    // Notify �� ����� AnimMontage



private:
	UPROPERTY()
    // ��������� �� ������� ������, ���������� ������ �������
	ASTUBaseWeapon* CurrentWeapon = nullptr;

	UPROPERTY()
	TArray<ASTUBaseWeapon* > Weapons;
	// ������ ���������� �� ������ ���� ASTUBaseWeapon - ������ ������
	// ��� ����� ������ �� ������ �������� ��������� CurrentWeapon �� �������� ��������� �� ������� �������

	int32 CurrentWeaponIndex = 0;
	// ������ �������� ������� �� ������� � ������ ������ ��������� ��������� CurrentWeapon 

	// ����, ����� ����� �������� true ��� ����� ������ � ��������,�� �� �������� ���������� ����� ������ ������ ��� ��������
	bool EquipAnimProgress = false;

	void SpawnWeapons(); // ������� ������ � ������������� ������ ������ � Mesh ���������	

	// ������� ������������� ������ ������ � ������ ���������
	void AttachWeaponToSocket(ASTUBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName);

	// ������� ������������� ������� ������ � ���� ���������, ��������� ������ ��� ������� Weapons
	void EquipWeapon(int32 WeaponIndex);

	// ������������ ��������
	void PlayAnimMontage(UAnimMontage* Animation);

	// ������� Notify � ������������� �� ����
	void InitAnimations();

	// callback ������� ������ �� ������� OnNotified
	void OnEquipFinished(USkeletalMeshComponent* MeshComponent);

	// ������ true ����� ����� ��������
	bool CanFire() const;

	// ������ true ����� ����� ������ ������
	bool CanEquip() const;


};


