// My Shoot Them Up Game , All Rights Reserved
// � STUAmmoePickup.h

#pragma once

#include "CoreMinimal.h"
#include "Pickups/STUBasePickup.h"
#include "STUAmmoePickup.generated.h"

/**
 * 
 */
UCLASS()
class MYSHOOTTHEMUP_API ASTUAmmoePickup : public ASTUBasePickup
{
	GENERATED_BODY()

private:
	// ��� ������� �����������
	virtual bool GivePickupTo(APawn* Playerpawn) override;
	// true   - ��������� ������, false - ������ �� ����
	// APawn* - ��������� �� Pawn, ����� ���� ��������� ������ � ����������� �������� � ������
	
};
