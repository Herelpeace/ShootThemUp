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
	USphereComponent* CollisionComponent;  // коллизия сферы
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
	float RespawnTime = 5.0f;  // время респавна после взятия объекта


	virtual void BeginPlay() override;
	
	// функция вызвается при пересечении Overlap акторов
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	// переопредляем в нашем классе, будет вызваться при пересечении сферы


public:	
	virtual void Tick(float DeltaTime) override;

	// если можем взять пикап то вернет true
	bool CouldBeTaken() const;

private:
	// угол вращения объекта
	float RatationYaw = 0.0f;

	FTimerHandle RespawnTimerHandle;  // создаем переменную таймера

	// для классов наследников
	virtual bool GivePickupTo(APawn* PlayerPawn);
	// true   - подобрали объект, false - объект не взят
	// APawn* - указатель на Pawn, через него полуачаем доступ к компонентам здоровья и оружия
	
	void PickupWasTaken();  // вызывается псле взятия объекта, скрываем объект
	void Respawn();         // вызывается по срабатываению таймера респавна, делаем актор видимым

	// функция вычиляет рандомный угол вращения
	void GenerateRataionYaw();
		 

};
