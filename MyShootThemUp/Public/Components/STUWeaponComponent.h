// My Shoot Them Up Game , All Rights Reserved
// STUWeaponComponent.h

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

    void Fire(); // �������� ������ 

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")  // ����� ������ ������� ����� ����������
	TSubclassOf<ASTUBaseWeapon>	WeaponClass;          // WeaponClass - ���������� � ������� �������� ������� ������ ASTUBaseWeapon

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponAttachPointName = "WeaponSocket";



private:
	UPROPERTY()
    // ��������� �� ������� ������, ���������� ������ �������
	ASTUBaseWeapon* CurrentWeapon = nullptr;

	void SpawnWeapon(); // ������� ������ � ������������� ������ ������ � Mesh ���������		
};


