// My Shoot Them Up Game , All Rights Reserved
// ����� ������ ��� Launchera 
// � STUProjectile.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUProjectile.generated.h"

class USphereComponent;    // forward declaration
class UProjectileMovementComponent; // forward declaration
class USTUWeaponFXComponent;

UCLASS()
class MYSHOOTTHEMUP_API ASTUProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	ASTUProjectile();

	// ������� ������ ������ ����������� ������
	void SetShootDirection(const FVector& Direction) { ShotDirection = Direction; }

protected:
	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	USphereComponent* CollisionComponent;               // ������� ����� �����, ������� ���������� � �������� ���� ��� ������

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	UProjectileMovementComponent* MovementComponent;
	// UProjectileMovementComponent - ��������� �������� ��������� ������ �� ���, � ����������� �� �������� ����������.(������� ��������)
	// ���� � CharacterMovementComponent
	// ����� ������� ��������������� �����
	// ������� ������ ���������� �������� ��� ������������ � ������� ���������

	UPROPERTY(VisibleAnywhere, Category = "VFX") // ��������� ������ VFX � ������� ���������� ���� �������� � USTUWeaponFXComponent
	USTUWeaponFXComponent* WeaponFXComponent;    // �������� FX � ��������� �� ������ ��� �����������

	// ������ ���������
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon");
	float DamageRadius = 200.0f;

	// ���������� ���������� Damage
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float DamageAmount = 50.0f;

	// ���� �������� ��� ������� �� ����������� � ������
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	bool DoFullDamage = false;

	// ���������� ��� ������� �����
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float LifeSecond = 5.0f;


	virtual void BeginPlay() override;

private:
	FVector ShotDirection; // ���������� ��� �������� ����������� ��������

	// ������� �������� �������� CollisionComponent->OnComponentHit
	UFUNCTION()
	void OnProjectileHit ( UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit );

	// ������� ��������� ��������� �� ������� ���������� (��� �������� ����������)
	AController* GetController() const;

};
