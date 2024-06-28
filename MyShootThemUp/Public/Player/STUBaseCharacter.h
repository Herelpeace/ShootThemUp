// My Shoot Them Up Game , All Rights Reserved
// � STUBaseCharacter.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/InputComponent.h"
#include "Components/STUHealthActorComponent.h"
#include "Weapon/STUBaseWeapon.h"                // ��� ����� ������

#include "STUBaseCharacter.generated.h"



class UCameraComponent;
class USpringArmComponent;
class STUHealthActorComponent;    // Forward Declaration ������ ������ ��������
class UTextRenderComponent;       // Forward Declaration ������ ����������� ������
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
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USTUHealthActorComponent* HealthComponent;                                 // �������� ������ ������ STUHealthActorComponent, ��������

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")  
	UTextRenderComponent* HealthTextComponent;                                // ������ ����������� ������ �� ������, ��� ����������� ��������

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







	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Movement")
	bool IsRunning() const; // ���������� true ���� Shift �����, const ������� ������ ������ ������� �� ������

	UFUNCTION(BlueprintCallable, Category = "Movement")
	float GetMovementDirection() const; // ������� ��������� � ��������


private:
	void MoveForward(float Amount);   // ��������� �������� 1, 0, -1
    void MoveRight(float Amount);     // ��������� �������� 1, 0, -1

	bool WantsToRun = false;          // ����������� ������ �� ������� shift
    bool IsMovingForward = false;     // ����������� ������ �� ������� ������ (W ��� ������� �����)
	void OnStartRunning();            // ���������� ��� ������� Left Shift
    void OnStopRunning();             // ����� �������� Left Shift

	void OnDeath();                   // ������� ���������� ���������, ��� 0 ������ ��������

	void OnHealthChanged(float Health, float HealthDelta); // ������� ���������� ��������� ��� ��������� ��������

	UFUNCTION()
	void OnGroundLanded(const FHitResult& Hit);   // ������� ���������� ��������� ��� ������� � ������
	// const FHitResul - ��������� � ������� ���������� ��������� � �������������� 2-� �������� ( ����� ���������������, ������� � �.�.)


};
