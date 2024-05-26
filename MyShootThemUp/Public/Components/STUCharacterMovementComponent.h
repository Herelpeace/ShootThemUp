// My Shoot Them Up Game , All Rights Reserved
// STUCharacterMovementComponent.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "STUCharacterMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class MYSHOOTTHEMUP_API USTUCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement", meta = (ClampMin = "1.5", ClampMax = "10.0"))
	float RunModifier = 2.0f;

	// для того чтобы случайно не установили 0 в БП (тогда персонаж не будет двигаться), добавляем мета ограничения
	// ClampMin = "1.5"  - минимальное значение для переменной
	// ClampMax = "10.0" - максимальное значение для переменной 


	virtual float GetMaxSpeed() const override;  // переопределяем функцию GetMaxSpeed()
	
};
