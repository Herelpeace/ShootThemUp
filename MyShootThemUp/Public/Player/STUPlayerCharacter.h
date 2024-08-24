// My Shoot Them Up Game , All Rights Reserved
// В STUPlayerCharacter.h

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

	// функция вызывается делегатом, при 0 уровне здоровья
	virtual void OnDeath() override;

public:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual bool IsRunning() const override; // возвращает true если Shift нажат, const никакие данные внутри функция не меняет


private:
	bool WantsToRun = false;          // отслеживает нажата ли клавиша shift
	bool IsMovingForward = false;     // отслеживает нажата ли клавиша вперед (W или стрелка вверх)

	void MoveForward(float Amount);   // принимает значения 1, 0, -1
	void MoveRight(float Amount);     // принимает значения 1, 0, -1

	void OnStartRunning();            // вызывается при нажатии Left Shift
	void OnStopRunning();             // когда отпустли Left Shift



};
