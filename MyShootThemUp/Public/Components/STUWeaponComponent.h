// My Shoot Them Up Game , All Rights Reserved
// В STUWeaponComponent.h

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUWeaponComponent.generated.h"


class ASTUBaseWeapon; // Forward Declaration нашего класса оружия

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYSHOOTTHEMUP_API USTUWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USTUWeaponComponent();

    void StartFire(); // старт стрельба мышкой 
    void StopFire();  // стоп стрельба мышкой 
	void NextWeapon(); // при смене оружия

protected:
	virtual void BeginPlay() override;

	// функция EndPlay вызывается у каждого компонента при вызове её у родительского актора 
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")        // в редакторе будет массив в который можем добавлять элементы
	TArray <TSubclassOf<ASTUBaseWeapon>>	WeaponClasses;  // WeaponClasses - массив из классов оружия

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponEquipSocketName = "WeaponSocket";       // сокет для присоединения оружия в руке

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponArmorySocketName = "ArmorySocket";       // сокет для присоединения оружия на спине



private:
	UPROPERTY()
    // указатель на текущее оружие, изначально делаем нулевым
	ASTUBaseWeapon* CurrentWeapon = nullptr;

	UPROPERTY()
	TArray<ASTUBaseWeapon* > Weapons;
	// массив указателей на акторы типа ASTUBaseWeapon - акторы оружия
	// при смене оружия мы меняем значение указателя CurrentWeapon на значение указателя из данного массива

	int32 CurrentWeaponIndex = 0;
	// индекс элемента массива на который в данный момент ссылается указатель CurrentWeapon 

	void SpawnWeapons(); // функция спавна и присоединения соекта оружия к Mesh персонажа	

	// фцнкция присоединения модели оружия к модели персонажа
	void AttachWeaponToSocket(ASTUBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName);

	// функция устанавливает текущее оружие в руке персонажа, принимает индекс для массива Weapons
	void EquipWeapon(int32 WeaponIndex);


};


