// My Shoot Them Up Game , All Rights Reserved
// � STUWeaponComponent.h

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUWeaponComponent.generated.h"


class ASTUBaseWeapon; // Forward Declaration ������ ������ ������

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


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYSHOOTTHEMUP_API USTUWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USTUWeaponComponent();

    void StartFire();  // ����� �������� ������ 
    void StopFire();   // ���� �������� ������ 
	void NextWeapon(); // ��� ����� ������
	void Reload();     // �����������

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



private:
	UPROPERTY()
    // ��������� �� ������� ������, ���������� ������ �������
	ASTUBaseWeapon* CurrentWeapon = nullptr;

	UPROPERTY()
	TArray<ASTUBaseWeapon* > Weapons;
	// ������ ���������� �� ������ ���� ASTUBaseWeapon - ������ ������
	// ��� ����� ������ �� ������ �������� ��������� CurrentWeapon �� �������� ��������� �� ������� �������

	UPROPERTY()
	UAnimMontage* CurrentReloadAnimMontage = nullptr;
	// ������� �������� ����������� 

	int32 CurrentWeaponIndex = 0;
	// ������ �������� ������� �� ������� � ������ ������ ��������� ��������� CurrentWeapon 

	// ����, ����� ����� �������� true ��� ����� ������ � ��������,�� �� �������� ���������� ����� ������ ������ ��� ��������
	bool EquipAnimProgress = false;

	// ����, ����� ����� �������� true ��� ����� ������ � ��������,�� �� �������� ���������� ����� ������ ������ ��� ��������
	bool ReloadAnimProgress = false;

	void SpawnWeapons(); // ������� ������ � ������������� ������ ������ � Mesh ���������	

	// ������� ������������� ������ ������ � ������ ���������
	void AttachWeaponToSocket(ASTUBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName);

	// ������� ������������� ������� ������ � ���� ���������, ��������� ������ ��� ������� Weapons
	void EquipWeapon(int32 WeaponIndex);

	// ������������ ��������
	void PlayAnimMontage(UAnimMontage* Animation);

	// ������� Notify � ������������� �� ����
	void InitAnimations();

	// callback ������� ������ �� ������� OnNotified ����� ������
	void OnEquipFinished(USkeletalMeshComponent* MeshComponent);

	// callback ������� ������ �� ������� OnNotified �����������
	void OnReloadFinished(USkeletalMeshComponent* MeshComponent);

	// ������ true ����� ����� ��������
	bool CanFire() const;

	// ������ true ����� ����� ������ ������
	bool CanEquip() const;

	// ������ true ����� ����� ��������������
	bool CanReload() const;


	// ��������� ������� ������ notify � �������� ������
	// template <typename T> - ���������� ��������� �������
	// T*                    - ���������� ��������� �� ��� T
	// FindNotifyByClass     - ��� �������
	// UAnimSequenceBase*    - � ������ ������ ���������� ������ ���� notify
	template <typename T>
	T* FindNotifyByClass(UAnimSequenceBase* Animation)
	{
		if (!Animation) return nullptr;

		// �������� �������� ������� �������� ������� Notifys. 	TArray<struct FAnimNotifyEvent> Notifies;
		// ������ ������������ �������
		const auto NotifyEvents = Animation->Notifies;

		// ���������� �������� �������
		for (auto NotifyEvent : NotifyEvents)
		{
			auto AnimNotify = Cast<T>(NotifyEvent.Notify);

			// EquipFinishedNotify - ��������� ��������� ��������� Notify, � ��������� ����������
			// NotifyEvent.Notify  - � ���� Notify ���������� Notify
			// Cast <>             - ������ Cast �� ������ ������, ���� Cast ������ ������� ������ Notify �� ������ ������

			// �������� ������� ���� Notify ������
			if (AnimNotify)
			{
				return AnimNotify;
			}
		}
		return nullptr;
	}



};


