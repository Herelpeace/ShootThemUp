// My Shoot Them Up Game , All Rights Reserved
// В STUBasePickup.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUBasePickup.generated.h"

class USphereComponent;  // т.к тип данных указатель на класс

UCLASS()
class MYSHOOTTHEMUP_API ASTUBasePickup : public AActor
{
	GENERATED_BODY()
	
public:	
	ASTUBasePickup();

protected:
	UPROPERTY(VisibleAnywhere, Category = "Pickup")
	USphereComponent* CollisionComponent;
	// коллизия сферы

	virtual void BeginPlay() override;
	
	// функция вызвается при пересечении Overlap акторов
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	// переопредляем в нашем классе, будет вызваться при пересечении сферы


public:	
	virtual void Tick(float DeltaTime) override;

};
