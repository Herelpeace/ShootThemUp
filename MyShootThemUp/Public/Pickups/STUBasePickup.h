// My Shoot Them Up Game , All Rights Reserved
// � STUBasePickup.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUBasePickup.generated.h"

class USphereComponent;  // �.� ��� ������ ��������� �� �����

UCLASS()
class MYSHOOTTHEMUP_API ASTUBasePickup : public AActor
{
	GENERATED_BODY()
	
public:	
	ASTUBasePickup();

protected:
	UPROPERTY(VisibleAnywhere, Category = "Pickup")
	USphereComponent* CollisionComponent;  // �������� �����
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
	float RespawnTime = 5.0f;  // ����� �������� ����� ������ �������


	virtual void BeginPlay() override;
	
	// ������� ��������� ��� ����������� Overlap �������
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	// ������������� � ����� ������, ����� ��������� ��� ����������� �����


public:	
	virtual void Tick(float DeltaTime) override;

	// ���� ����� ����� ����� �� ������ true
	bool CouldBeTaken() const;

private:
	// ���� �������� �������
	float RatationYaw = 0.0f;

	FTimerHandle RespawnTimerHandle;  // ������� ���������� �������

	// ��� ������� �����������
	virtual bool GivePickupTo(APawn* PlayerPawn);
	// true   - ��������� ������, false - ������ �� ����
	// APawn* - ��������� �� Pawn, ����� ���� ��������� ������ � ����������� �������� � ������
	
	void PickupWasTaken();  // ���������� ���� ������ �������, �������� ������
	void Respawn();         // ���������� �� ������������� ������� ��������, ������ ����� �������

	// ������� �������� ��������� ���� ��������
	void GenerateRataionYaw();
		 

};
