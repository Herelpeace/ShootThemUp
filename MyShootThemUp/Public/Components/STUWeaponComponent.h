// My Shoot Them Up Game , All Rights Reserved
// В STUWeaponComponent.h

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUCoreType.h"
#include "STUWeaponComponent.generated.h"


class ASTUBaseWeapon; // Forward Declaration нашего класса оружия


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYSHOOTTHEMUP_API USTUWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USTUWeaponComponent();

    virtual void StartFire();  // старт стрельба мышкой 
    void StopFire();   // стоп стрельба мышкой 
	virtual void NextWeapon(); // при смене оружия
	void Reload();     // перезарядка
	bool GetCurrentWeaponUIData(FWeaponUIData& UIData) const; // возвращает UIData текущего оружия (внутри функции UIData присваивается значение)
	bool GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const; // возвращает структуру CurrentAmmo (внутри функции AmmoData присваивается значение)
	bool TryToAddAmmo(TSubclassOf<ASTUBaseWeapon> WeaponType, int32 ClipsAmount); // добавляем магазины, возвращает bool

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon") // в редакторе будет массив с кнопкой +
	TArray<FWeaponData> WeaponData;	     // массив структур хранящих класс оружия и его анимацию

	// функция EndPlay вызывается у каждого компонента при вызове её у родительского актора 
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponEquipSocketName = "WeaponSocket";       // сокет для присоединения оружия в руке

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponArmorySocketName = "ArmorySocket";       // сокет для присоединения оружия на спине

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* EquipAnimMontage;                     // указатель на анимацию смены оружия, все остальные персонажи так же подписываются на события
	                                                    // Notify от этого AnimMontage

	UPROPERTY()
	// указатель на текущее оружие, изначально делаем нулевым
	ASTUBaseWeapon* CurrentWeapon = nullptr;

	UPROPERTY()
	TArray<ASTUBaseWeapon* > Weapons;
	// массив указателей на акторы типа ASTUBaseWeapon - акторы оружия
	// при смене оружия мы меняем значение указателя CurrentWeapon на значение указателя из данного массива

	int32 CurrentWeaponIndex = 0;
	// индекс элемента массива на который в данный момент ссылается указатель CurrentWeapon 

	// вернет true когда можно стрелять
	bool CanFire() const;

	// вернет true когда можно менять оружие
	bool CanEquip() const;

	// функция устанавливает текущее оружие в руке персонажа, принимает индекс для массива Weapons
	void EquipWeapon(int32 WeaponIndex);


private:
	UPROPERTY()
	UAnimMontage* CurrentReloadAnimMontage = nullptr;
	// текущая анимация перезарядки 

	// флаг, будет иметь значение true при смене оружия и стрельбе,по ее значению определяем можно менять оружие или стрелять
	bool EquipAnimProgress = false;

	// флаг, будет иметь значение true при смене оружия и стрельбе,по ее значению определяем можно менять оружие или стрелять
	bool ReloadAnimProgress = false;

	void SpawnWeapons(); // функция спавна и присоединения соекта оружия к Mesh персонажа	

	// фцнкция присоединения модели оружия к модели персонажа
	void AttachWeaponToSocket(ASTUBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName);

	// проигрывание анимации
	void PlayAnimMontage(UAnimMontage* Animation);

	// находим Notify и подписываемся на него
	void InitAnimations();

	// callback который биндим на делегат OnNotified смены оружия
	void OnEquipFinished(USkeletalMeshComponent* MeshComponent);

	// callback который биндим на делегат OnNotified перезарядки
	void OnReloadFinished(USkeletalMeshComponent* MeshComponent);

	// вернет true когда можно перезаряжаться
	bool CanReload() const;

	// callback на делегат OnClipEmpty, передаем указатель на оружие требующее перезарядки
	void OnEmptyClip( ASTUBaseWeapon* AmmoEmptyWeapon);

	// вся логика перезарядки находится в этой функции
	void ChangeClip();

};


