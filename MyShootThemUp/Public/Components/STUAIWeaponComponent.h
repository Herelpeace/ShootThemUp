// My Shoot Them Up Game , All Rights Reserved
// смена оружи€ если нет патронов, наследник от STUWeaponComponent
// ¬ STUAIWeaponComponent.h


#pragma once

#include "CoreMinimal.h"
#include "Components/STUWeaponComponent.h"
#include "STUAIWeaponComponent.generated.h"



UCLASS()
class MYSHOOTTHEMUP_API USTUAIWeaponComponent : public USTUWeaponComponent
{
	GENERATED_BODY()
public:
	virtual void StartFire()  override;		// старт стрельба мышкой
	virtual void NextWeapon() override;		// при смене оружи€
};
