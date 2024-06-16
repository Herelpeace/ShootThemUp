// My Shoot Them Up Game , All Rights Reserved
// � STUHealthPickup.h

#pragma once

#include "CoreMinimal.h"
#include "Pickups/STUBasePickup.h"
#include "STUHealthPickup.generated.h"


UCLASS()
class MYSHOOTTHEMUP_API ASTUHealthPickup : public ASTUBasePickup
{
	GENERATED_BODY()
private:
	// ��� ������� �����������
	virtual bool GivePickupTo(APawn* PlayerPawn) override;
	// true   - ��������� ������, false - ������ �� ����
	// APawn* - ��������� �� Pawn, ����� ���� ��������� ������ � ����������� �������� � ������
	
};
