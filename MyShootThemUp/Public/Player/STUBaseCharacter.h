// My Shoot Them Up Game , All Rights Reserved
// В STUBaseCharacter.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/InputComponent.h"
#include "Components/STUHealthActorComponent.h"
#include "Weapon/STUBaseWeapon.h"                // наш класс оружия

#include "STUBaseCharacter.generated.h"



class UCameraComponent;
class USpringArmComponent;
class STUHealthActorComponent;    // Forward Declaration нашего класса здоровья
class UTextRenderComponent;       // Forward Declaration класса отображения текста
class USTUWeaponComponent;        // наш класс работы с оружием


UCLASS()
class MYSHOOTTHEMUP_API ASTUBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASTUBaseCharacter( const FObjectInitializer& ObjInit);
	
	// ASTUBaseCharacter( const FObjectInitializer& ObjInit) - конструктор с параметром в котором передается объект инициализации


protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USTUHealthActorComponent* HealthComponent;                                 // объявили объект класса STUHealthActorComponent, здоровье

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")  
	UTextRenderComponent* HealthTextComponent;                                // объект отоброжения текста на экране, для отоброжения здоровья

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USTUWeaponComponent* WeaponComponent;                                      // создали объект нашего класса оружия

	UPROPERTY(EditDefaultsOnly, CAtegory = "Animation")        // доступен только в дефолтных настройках
	UAnimMontage* DeathAnimMontage;                            // переменная для AnimMontage, анимация вверх вниз

	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage")  
	float LifeSpanDeth = 5.0f;                                 // время через которое персонаж будет удален со сцены


	UPROPERTY(EditDefaultsOnly, Category = "Damage")                // доступен только в дефолтных настройках
	FVector2D LandedDamageVelocity = FVector2D(900.0f, 1200.0f);    // предельная скорость при которой наносится Damage                         
	                                                                // меньше 900 - нет урона, больше 1200 - забираем максимальное количество жизни

	UPROPERTY(EditDefaultsOnly, Category = "Damage")                // доступен только в дефолтных настройках
	FVector2D LandedDamage = FVector2D(10.0f, 100.0f);              // 10 - минимальный урон, 100 - максимальный урон 







	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Movement")
	bool IsRunning() const; // возвращает true если Shift нажат, const никакие данные внутри функция не меняет

	UFUNCTION(BlueprintCallable, Category = "Movement")
	float GetMovementDirection() const; // поворот персонажа в градусах


private:
	void MoveForward(float Amount);   // принимает значения 1, 0, -1
    void MoveRight(float Amount);     // принимает значения 1, 0, -1

	bool WantsToRun = false;          // отслеживает нажата ли клавиша shift
    bool IsMovingForward = false;     // отслеживает нажата ли клавиша вперед (W или стрелка вверх)
	void OnStartRunning();            // вызывается при нажатии Left Shift
    void OnStopRunning();             // когда отпустли Left Shift

	void OnDeath();                   // функция вызывается делегатом, при 0 уровне здоровья

	void OnHealthChanged(float Health, float HealthDelta); // функция вызываемая делегатом при изменении здоровья

	UFUNCTION()
	void OnGroundLanded(const FHitResult& Hit);   // функция вызываемая делегатом при падении с высоты
	// const FHitResul - структура в которой содержится иформация о взаимодействии 2-х объектов ( точки соприкосновения, нормали и т.д.)


};
