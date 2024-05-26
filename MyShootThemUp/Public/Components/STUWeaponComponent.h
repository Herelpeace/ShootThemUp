// My Shoot Them Up Game , All Rights Reserved
// STUWeaponComponent.h

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

    void Fire(); // стрельба мышкой 

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")  // класс оружия которое хотим заспавнить
	TSubclassOf<ASTUBaseWeapon>	WeaponClass;          // WeaponClass - переменная в которую передаем объекты класса ASTUBaseWeapon

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponAttachPointName = "WeaponSocket";



private:
	UPROPERTY()
    // указатель на текущее оружие, изначально делаем нулевым
	ASTUBaseWeapon* CurrentWeapon = nullptr;

	void SpawnWeapon(); // функция спавна и присоединения соекта оружия к Mesh персонажа		
};


