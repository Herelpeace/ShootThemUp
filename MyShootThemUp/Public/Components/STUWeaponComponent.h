// My Shoot Them Up Game , All Rights Reserved
// ¬ STUWeaponComponent.h

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUWeaponComponent.generated.h"


class ASTUBaseWeapon; // Forward Declaration нашего класса оружи€

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYSHOOTTHEMUP_API USTUWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USTUWeaponComponent();

    void StartFire(); // старт стрельба мышкой 
    void StopFire();  // стоп стрельба мышкой 
	void NextWeapon(); // при смене оружи€

protected:
	virtual void BeginPlay() override;

	// функци€ EndPlay вызываетс€ у каждого компонента при вызове еЄ у родительского актора 
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")        // в редакторе будет массив в который можем добавл€ть элементы
	TArray <TSubclassOf<ASTUBaseWeapon>>	WeaponClasses;  // WeaponClasses - массив из классов оружи€

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponEquipSocketName = "WeaponSocket";       // сокет дл€ присоединени€ оружи€ в руке

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponArmorySocketName = "ArmorySocket";       // сокет дл€ присоединени€ оружи€ на спине

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* EquipAnimMontage;                     // указатель на анимацию смены оружи€, все остальные персонажи так же подписываютс€ на событи€
	                                                    // Notify от этого AnimMontage



private:
	UPROPERTY()
    // указатель на текущее оружие, изначально делаем нулевым
	ASTUBaseWeapon* CurrentWeapon = nullptr;

	UPROPERTY()
	TArray<ASTUBaseWeapon* > Weapons;
	// массив указателей на акторы типа ASTUBaseWeapon - акторы оружи€
	// при смене оружи€ мы мен€ем значение указател€ CurrentWeapon на значение указател€ из данного массива

	int32 CurrentWeaponIndex = 0;
	// индекс элемента массива на который в данный момент ссылаетс€ указатель CurrentWeapon 

	void SpawnWeapons(); // функци€ спавна и присоединени€ соекта оружи€ к Mesh персонажа	

	// фцнкци€ присоединени€ модели оружи€ к модели персонажа
	void AttachWeaponToSocket(ASTUBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName);

	// функци€ устанавливает текущее оружие в руке персонажа, принимает индекс дл€ массива Weapons
	void EquipWeapon(int32 WeaponIndex);

	// проигрывание анимации
	void PlayAnimMontage(UAnimMontage* Animation);

	// находим Notify и подписываемс€ на него
	void InitAnimations();

	// callback который биндим на делегат OnNotified
	void OnEquipFinished(USkeletalMeshComponent* MeshComponent);


};


