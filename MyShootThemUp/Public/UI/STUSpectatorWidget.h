// My Shoot Them Up Game , All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUSpectatorWidget.generated.h"

/**
 * 
 */
UCLASS()
class MYSHOOTTHEMUP_API USTUSpectatorWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "UI")

	// true ���� ������ �������
	// int32& CountDownTime - ���������� ������ �� ��������
	bool GetRespawnTime(int32& CountDownTime) const;
	

};
