// My Shoot Them Up Game , All Rights Reserved
// ¬ STUProjectile.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUProjectile.generated.h"

class USphereComponent;    // forward declaration
class UProjectileMovementComponent;

UCLASS()
class MYSHOOTTHEMUP_API ASTUProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	ASTUProjectile();

	// функци€ задает вектор направлени€ ракете
	void SetShootDirection(const FVector& Direction) { ShotDirection = Direction; }

protected:
	UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
	USphereComponent* CollisionComponent;               // создаем класс сферы, который используем в качестве мэша дл€ ракеты

	UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
	UProjectileMovementComponent* MovementComponent;
	// UProjectileMovementComponent - компонент измен€ет положение актора на тик, в зависимости от заданных параметров.(придает скорость)
	// схож с CharacterMovementComponent
	// можно сделать самонавод€щийс€ актор
	// сделать разное количество отскоков при столкновении с другими объектами


	virtual void BeginPlay() override;

private:
	FVector ShotDirection; // переменна€ дл€ хранени€ направлени€ движени€


};
