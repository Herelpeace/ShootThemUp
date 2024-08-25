// My Shoot Them Up Game , All Rights Reserved
// В STUPlayerCharacter.h

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

	// функция вызывается делегатом, при 0 уровне здоровья
	virtual void OnDeath() override;

	virtual void BeginPlay() override;

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

	// Полные делегаты Begin и End Overlap
	//DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_SixParams(FComponentBeginOverlapSignature, UPrimitiveComponent, OnComponentBeginOverlap, UPrimitiveComponent*, OverlappedComponent, AActor*, OtherActor, UPrimitiveComponent*, OtherComp, int32, OtherBodyIndex, bool, bFromSweep, const FHitResult&, SweepResult);
	//DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_FourParams(FComponentEndOverlapSignature, UPrimitiveComponent, OnComponentEndOverlap, UPrimitiveComponent*, OverlappedComponent, AActor*, OtherActor, UPrimitiveComponent*, OtherComp, int32, OtherBodyIndex);

	// функция для бинда на делегат BeginOverlap
	UFUNCTION()
	void OnCameraCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// функция для бинда на делегат EndOverlap
	UFUNCTION()
	void OnCameraCollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	// Проверяем пересекаются ли коллизии сферы и капсулы
	void CheckCameraOverlap();

};
