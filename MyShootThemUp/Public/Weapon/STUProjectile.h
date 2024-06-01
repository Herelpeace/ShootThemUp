// My Shoot Them Up Game , All Rights Reserved
// � STUProjectile.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUProjectile.generated.h"

class USphereComponent;    // forward declaration ��� ������� ������

UCLASS()
class MYSHOOTTHEMUP_API ASTUProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	ASTUProjectile();

protected:
	UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
	USphereComponent* CollisionComponent;               // ������� ����� �����, ������� ���������� � �������� ���� ��� ������

	virtual void BeginPlay() override;
};
