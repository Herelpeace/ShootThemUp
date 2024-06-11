// My Shoot Them Up Game , All Rights Reserved
// В STUPlayerHUDWidget.h

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUPlayerHUDWidget.generated.h"


UCLASS()
class MYSHOOTTHEMUP_API USTUPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	
	// функция которую будем вызывать в БП и получать текущий уровень здоровья
	UFUNCTION(BlueprintCallable, Category = "UI")
	float GetHealthPercent() const;

	
};
