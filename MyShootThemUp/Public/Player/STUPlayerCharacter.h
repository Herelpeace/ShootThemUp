// My Shoot Them Up Game , All Rights Reserved
// � STUPlayerCharacter.h

#pragma once

#include "CoreMinimal.h"
#include "Player/STUBaseCharacter.h"
#include "STUPlayerCharacter.generated.h"


class UCameraComponent;
class USpringArmComponent;


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

	// ������� ���������� ���������, ��� 0 ������ ��������
	virtual void OnDeath() override;

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



};
