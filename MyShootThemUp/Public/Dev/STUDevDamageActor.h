// My Shoot Them Up Game , All Rights Reserved
// STUDevDamageActor.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUDevDamageActor.generated.h"

UCLASS()
class MYSHOOTTHEMUP_API ASTUDevDamageActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASTUDevDamageActor();

	// объ€вл€ем SceneComponent, дл€ редактора
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	USceneComponent* SceneComponent;

	// переменна€ радиуса
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Radius = 300.f;

	// переменна€ цвета 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FColor SphereColor = FColor::Red;

	// переменна€ урона который наносит сфера
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage = 10.0f;

	// переменна€ вли€ет ли удаление от центра на величину урона
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool DoFullDamage = false;

	// класс урона от огн€
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UDamageType> DamageType;             // TSubclassOf<класс> »м€_объекта - позвол€ет создать переменную в которую мы можем передавать объекты указанного класса


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
