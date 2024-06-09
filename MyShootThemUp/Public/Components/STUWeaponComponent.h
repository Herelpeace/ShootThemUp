// My Shoot Them Up Game , All Rights Reserved
// В STUWeaponComponent.h

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUWeaponComponent.generated.h"


class ASTUBaseWeapon; // Forward Declaration нашего класса оружия

// структура в которой храним класс оружия и соответствующую ему анимацию перезарядки
// в редакторе будут поля в которые сможем устанавливать соостветствующие БП
USTRUCT(BlueprintType)
struct FWeaponData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")        // в редакторе будет ?
	TSubclassOf<ASTUBaseWeapon> WeaponClass;  // переменная класса оружия

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	UAnimMontage* ReloadAnimMontage;   // в переменной будем хранить анимацию перезарядки для данного оружия
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYSHOOTTHEMUP_API USTUWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USTUWeaponComponent();

    void StartFire();  // старт стрельба мышкой 
    void StopFire();   // стоп стрельба мышкой 
	void NextWeapon(); // при смене оружия
	void Reload();     // перезарядка

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



private:
	UPROPERTY()
    // указатель на текущее оружие, изначально делаем нулевым
	ASTUBaseWeapon* CurrentWeapon = nullptr;

	UPROPERTY()
	TArray<ASTUBaseWeapon* > Weapons;
	// массив указателей на акторы типа ASTUBaseWeapon - акторы оружия
	// при смене оружия мы меняем значение указателя CurrentWeapon на значение указателя из данного массива

	UPROPERTY()
	UAnimMontage* CurrentReloadAnimMontage = nullptr;
	// текущая анимация перезарядки 

	int32 CurrentWeaponIndex = 0;
	// индекс элемента массива на который в данный момент ссылается указатель CurrentWeapon 

	// флаг, будет иметь значение true при смене оружия и стрельбе,по ее значению определяем можно менять оружие или стрелять
	bool EquipAnimProgress = false;

	// флаг, будет иметь значение true при смене оружия и стрельбе,по ее значению определяем можно менять оружие или стрелять
	bool ReloadAnimProgress = false;

	void SpawnWeapons(); // функция спавна и присоединения соекта оружия к Mesh персонажа	

	// фцнкция присоединения модели оружия к модели персонажа
	void AttachWeaponToSocket(ASTUBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName);

	// функция устанавливает текущее оружие в руке персонажа, принимает индекс для массива Weapons
	void EquipWeapon(int32 WeaponIndex);

	// проигрывание анимации
	void PlayAnimMontage(UAnimMontage* Animation);

	// находим Notify и подписываемся на него
	void InitAnimations();

	// callback который биндим на делегат OnNotified смены оружия
	void OnEquipFinished(USkeletalMeshComponent* MeshComponent);

	// callback который биндим на делегат OnNotified перезарядки
	void OnReloadFinished(USkeletalMeshComponent* MeshComponent);

	// вернет true когда можно стрелять
	bool CanFire() const;

	// вернет true когда можно менять оружие
	bool CanEquip() const;

	// вернет true когда можно перезаряжаться
	bool CanReload() const;


	// шаблонная функция поиска notify в заданном классе
	// template <typename T> - объявление шаблонной функции
	// T*                    - возвращает указатель на тип T
	// FindNotifyByClass     - имя функции
	// UAnimSequenceBase*    - в данном классе содержится массив всех notify
	template <typename T>
	T* FindNotifyByClass(UAnimSequenceBase* Animation)
	{
		if (!Animation) return nullptr;

		// получаем значения массива структур эвентов Notifys. 	TArray<struct FAnimNotifyEvent> Notifies;
		// масиив анимационных эвентов
		const auto NotifyEvents = Animation->Notifies;

		// перебираем элементы массива
		for (auto NotifyEvent : NotifyEvents)
		{
			auto AnimNotify = Cast<T>(NotifyEvent.Notify);

			// EquipFinishedNotify - сохраняем найденный указатель Notify, в локальную переменную
			// NotifyEvent.Notify  - в поле Notify содержится Notify
			// Cast <>             - делаем Cast до нашего класса, если Cast прошел успешно значит Notify из нашего класса

			// вызываем делегат если Notify найден
			if (AnimNotify)
			{
				return AnimNotify;
			}
		}
		return nullptr;
	}



};


