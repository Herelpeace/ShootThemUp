// My Shoot Them Up Game , All Rights Reserved
// � STUAIWeaponComponent.h

#pragma once

#include "CoreMinimal.h"
#include "Components/STUWeaponComponent.h"
#include "STUAIWeaponComponent.generated.h"



UCLASS()
class MYSHOOTTHEMUP_API USTUAIWeaponComponent : public USTUWeaponComponent
{
	GENERATED_BODY()
public:
	virtual void StartFire()  override;		// ����� �������� ������
	virtual void NextWeapon() override;		// ��� ����� ������
};
