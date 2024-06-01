// My Shoot Them Up Game , All Rights Reserved
// � STUProjectile.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUProjectile.generated.h"

class USphereComponent;    // forward declaration
class UProjectileMovementComponent;

UCLASS()
class MYSHOOTTHEMUP_API ASTUProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	ASTUProjectile();

	// ������� ������ ������ ����������� ������
	void SetShootDirection(const FVector& Direction) { ShotDirection = Direction; }

protected:
	UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
	USphereComponent* CollisionComponent;               // ������� ����� �����, ������� ���������� � �������� ���� ��� ������

	UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
	UProjectileMovementComponent* MovementComponent;
	// UProjectileMovementComponent - ��������� �������� ��������� ������ �� ���, � ����������� �� �������� ����������.(������� ��������)
	// ���� � CharacterMovementComponent
	// ����� ������� ��������������� �����
	// ������� ������ ���������� �������� ��� ������������ � ������� ���������


	virtual void BeginPlay() override;

private:
	FVector ShotDirection; // ���������� ��� �������� ����������� ��������


};
