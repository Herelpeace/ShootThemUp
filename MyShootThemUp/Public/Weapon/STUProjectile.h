// My Shoot Them Up Game , All Rights Reserved
// класс ракеты дл€ Launchera 
// ¬ STUProjectile.h

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

	// функци€ задает вектор направлени€ ракете
	void SetShootDirection(const FVector& Direction) { ShotDirection = Direction; }

protected:
	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	USphereComponent* CollisionComponent;               // создаем класс сферы, который используем в качестве мэша дл€ ракеты

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	UProjectileMovementComponent* MovementComponent;
	// UProjectileMovementComponent - компонент измен€ет положение актора на тик, в зависимости от заданных параметров.(придает скорость)
	// схож с CharacterMovementComponent
	// можно сделать самонавод€щийс€ актор
	// сделать разное количество отскоков при столкновении с другими объектами

	UPROPERTY(VisibleAnywhere, Category = "VFX") // создаетс€ раздел VFX в котором по€вл€ютс€ пол€ заданные в USTUWeaponFXComponent
	USTUWeaponFXComponent* WeaponFXComponent;    // выбираем FX в редакторе Ѕѕ ракеты дл€ гранатомета

	// радиус поражени€
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon");
	float DamageRadius = 200.0f;

	// количество наносимого Damage
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float DamageAmount = 50.0f;

	// урон одинаков или зависит от приближени€ к центру
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	bool DoFullDamage = false;

	// переменна€ дл€ времени жизни
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float LifeSecond = 5.0f;


	virtual void BeginPlay() override;

private:
	FVector ShotDirection; // переменна€ дл€ хранени€ направлени€ движени€

	// функци€ делегата коллизии CollisionComponent->OnComponentHit
	UFUNCTION()
	void OnProjectileHit ( UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit );

	// функци€ получени€ указател€ на текущий контроллер (дл€ итоговой статистики)
	AController* GetController() const;

};
