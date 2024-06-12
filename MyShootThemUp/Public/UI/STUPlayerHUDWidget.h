// My Shoot Them Up Game , All Rights Reserved
// � STUPlayerHUDWidget.h

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUCoreType.h"
#include "STUPlayerHUDWidget.generated.h"


UCLASS()
class MYSHOOTTHEMUP_API USTUPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	
	// ������� ������� ����� �������� � �� � �������� ������� ������� ��������
	UFUNCTION(BlueprintCallable, Category = "UI")
	float GetHealthPercent() const;


	// ���������� UIData �������� ������, ����� �������� � ��
	UFUNCTION(BlueprintCallable, Category = "UI")
	bool GetWeaponUIData(FWeaponUIData& UIData) const;

	
};
