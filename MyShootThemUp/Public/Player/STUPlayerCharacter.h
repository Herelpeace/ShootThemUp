// My Shoot Them Up Game , All Rights Reserved
// � STUPlayerCharacter.h

#pragma once

#include "CoreMinimal.h"
#include "Player/STUBaseCharacter.h"
#include "STUPlayerCharacter.generated.h"


class UCameraComponent;
class USpringArmComponent;
class USphereComponent;


UCLASS()
class MYSHOOTTHEMUP_API ASTUPlayerCharacter : public ASTUBaseCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASTUPlayerCharacter(const FObjectInitializer& ObjInit);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USphereComponent* CameraCollisionComponent;

	// ������� ���������� ���������, ��� 0 ������ ��������
	virtual void OnDeath() override;

	virtual void BeginPlay() override;

public:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual bool IsRunning() const override; // ���������� true ���� Shift �����, const ������� ������ ������ ������� �� ������


private:
	bool WantsToRun = false;          // ����������� ������ �� ������� shift
	bool IsMovingForward = false;     // ����������� ������ �� ������� ������ (W ��� ������� �����)

	void MoveForward(float Amount);   // ��������� �������� 1, 0, -1
	void MoveRight(float Amount);     // ��������� �������� 1, 0, -1

	void OnStartRunning();            // ���������� ��� ������� Left Shift
	void OnStopRunning();             // ����� �������� Left Shift

	// ������ �������� Begin � End Overlap
	//DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_SixParams(FComponentBeginOverlapSignature, UPrimitiveComponent, OnComponentBeginOverlap, UPrimitiveComponent*, OverlappedComponent, AActor*, OtherActor, UPrimitiveComponent*, OtherComp, int32, OtherBodyIndex, bool, bFromSweep, const FHitResult&, SweepResult);
	//DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_FourParams(FComponentEndOverlapSignature, UPrimitiveComponent, OnComponentEndOverlap, UPrimitiveComponent*, OverlappedComponent, AActor*, OtherActor, UPrimitiveComponent*, OtherComp, int32, OtherBodyIndex);

	// ������� ��� ����� �� ������� BeginOverlap
	UFUNCTION()
	void OnCameraCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// ������� ��� ����� �� ������� EndOverlap
	UFUNCTION()
	void OnCameraCollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	// ��������� ������������ �� �������� ����� � �������
	void CheckCameraOverlap();

};
