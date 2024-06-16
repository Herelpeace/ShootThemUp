// My Shoot Them Up Game , All Rights Reserved
// � STUAmmoePickup.h

#pragma once

#include "CoreMinimal.h"
#include "Pickups/STUBasePickup.h"
#include "STUAmmoePickup.generated.h"

class ASTUBaseWeapon;  // forward declaration �.� �������� ���������� ������� ����
UCLASS()
class MYSHOOTTHEMUP_API ASTUAmmoePickup : public ASTUBasePickup
{
	GENERATED_BODY()

protected:
	// ���������� ��������� ������� ����� �����, �� 1 �� 10
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup", meta = (ClampMin = "1.0", ClampMax = "10"))
	int32 ClipsAmount = 10;

	// � ������ ������ ��������� ��������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
		TSubclassOf<ASTUBaseWeapon> WeaponType; // ���������� ���� ASTUBaseWeapon


private:
	// ��� ������� �����������
	virtual bool GivePickupTo(APawn* PlayerPawn) override;
	// true   - ��������� ������, false - ������ �� ����
	// APawn* - ��������� �� Pawn, ����� ���� ��������� ������ � ����������� �������� � ������
	
};
