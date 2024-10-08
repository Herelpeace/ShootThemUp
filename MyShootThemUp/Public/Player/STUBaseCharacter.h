// My Shoot Them Up Game , All Rights Reserved
// � STUBaseCharacter.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/InputComponent.h"
#include "Components/STUHealthActorComponent.h"
#include "Weapon/STUBaseWeapon.h"                // ��� ����� ������

#include "STUBaseCharacter.generated.h"


class STUHealthActorComponent;    // Forward Declaration ������ ������ ��������
class USTUWeaponComponent;        // ��� ����� ������ � �������


UCLASS()
class MYSHOOTTHEMUP_API ASTUBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASTUBaseCharacter( const FObjectInitializer& ObjInit);
	
	// ASTUBaseCharacter( const FObjectInitializer& ObjInit) - ����������� � ���������� � ������� ���������� ������ �������������


protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USTUHealthActorComponent* HealthComponent;                                 // �������� ������ ������ STUHealthActorComponent, ��������

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USTUWeaponComponent* WeaponComponent;                                      // ������� ������ ������ ������ ������

	UPROPERTY(EditDefaultsOnly, CAtegory = "Animation")        // �������� ������ � ��������� ����������
	UAnimMontage* DeathAnimMontage;                            // ���������� ��� AnimMontage, �������� ����� ����

	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage")  
	float LifeSpanDeth = 5.0f;                                 // ����� ����� ������� �������� ����� ������ �� �����


	UPROPERTY(EditDefaultsOnly, Category = "Damage")                // �������� ������ � ��������� ����������
	FVector2D LandedDamageVelocity = FVector2D(900.0f, 1200.0f);    // ���������� �������� ��� ������� ��������� Damage                         
	                                                                // ������ 900 - ��� �����, ������ 1200 - �������� ������������ ���������� �����

	UPROPERTY(EditDefaultsOnly, Category = "Damage")                // �������� ������ � ��������� ����������
	FVector2D LandedDamage = FVector2D(10.0f, 100.0f);              // 10 - ����������� ����, 100 - ������������ ���� 

	UPROPERTY(EditDefaultsOnly, Category = "Material")
	FName MaterialColorName = "Paint Color";


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// ������� ���������� ���������, ��� 0 ������ ��������
	virtual void OnDeath();                   


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Movement")
	virtual bool IsRunning() const; // ���������� true ���� Shift �����, const ������� ������ ������ ������� �� ������

	UFUNCTION(BlueprintCallable, Category = "Movement")
	float GetMovementDirection() const; // ������� ��������� � ��������

	// ������������� ����, ����� ������� �� Charactera 
	void SetPlayerColor(const FLinearColor& Color);


private:
	void OnHealthChanged(float Health, float HealthDelta); // ������� ���������� ��������� ��� ��������� ��������

	UFUNCTION()
	void OnGroundLanded(const FHitResult& Hit);   // ������� ���������� ��������� ��� ������� � ������
	// const FHitResul - ��������� � ������� ���������� ��������� � �������������� 2-� �������� ( ����� ���������������, ������� � �.�.)


};
