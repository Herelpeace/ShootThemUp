// My Shoot Them Up Game , All Rights Reserved
// В STUHealthActorComponent.cpp


#include "Components/STUHealthActorComponent.h"
#include "GameFramework/Actor.h"                // для получения ссылки на Actora которому принадлежит данный класс
#include "Engine/World.h"   // чтобы получать ссылку на мир, ТаймерМенеджер находится в объекте мира
#include "TimerManager.h"   // для таймера

DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent,All, All);

// Sets default values for this component's properties
USTUHealthActorComponent::USTUHealthActorComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void USTUHealthActorComponent::BeginPlay()
{
	Super::BeginPlay();

	check(MaxHealth>0);  // чтобы в редакторе не выставили ноль, т.к на эту переменную происходит деление

	// на старте игры или при спавне устанавливаем значение здоровья на 100
	SetHealth(MaxHealth);  

	// получаем ссылку на Actor которому принадлежит данный класс
	AActor* ComponentOwner = GetOwner();  
	if (ComponentOwner) // проверка на null
	{
	    // подписываемся на делегат OnTakeAnyDamage и биндим функцию
	    ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &USTUHealthActorComponent::OnTakeAnyDamage);
	    // this - указатель на текущий instance
	    // ASTUBaseCharacter::OnTakeAnyDamageHandle - функция урона, переопределенный делегат
	}

}


// Функция которая будет вызываться при получении урона
void USTUHealthActorComponent::OnTakeAnyDamage(
    AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	//UE_LOG(LogHealthComponent, Warning, TEXT(" Нанесен урон!!"));
	// если урон равен 0 или  isDead() = 0 или ссылка на мир - null (для таймера) ничего не делаем выходим
	if (Damage <= 0.0f || isDead() || !GetWorld())   return;

	// устанавливаем уровень здоровья в зависимости от величины Damage
	SetHealth(Health - Damage);

	// функция остановки таймера восстановления здоровья
	GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);

	// снова проверяем жив ли персонаж
	if (isDead())
	{
		// через делегат оповещаем всех что у персонажа не осталось здоровья
	    onDeath.Broadcast();
	}
	else 
	if (AutoHeal)  //TimerManager находится в объекте UWorld, нет мира - нет доступа к таймеру
	{
		// таймер будет вызывать функцию HealUpdate
	    GetWorld()->GetTimerManager().SetTimer(HealTimerHandle, this, &USTUHealthActorComponent::HealUpdate, HealUpdateTime, true,HealDelay);

		// HealTimerHandle                       - объект типа FTimerHandle
		// this                                  - указатель на объект в котором будет вызываться функция 
	    // &USTUHealthActorComponent::HealUpdate - ссылка на вызываемую функцию
		// HealUpdateTime                        - частота обновления таймера
		// true                                  - вызывается ли таймер повторно
		// HealDelay                             - задержка перед первым вызовом
	}   
	     

}
// OnTakeAnyDamageHandle функция урона

// функция восстановления здоровья
void USTUHealthActorComponent::HealUpdate() 
{
	SetHealth(Health + HealModifier);

	// останавливаем таймер когда здоровье достигло максимума
	// проверяем чтобы здоровье не стало больше максимального, проверка мира на null
	if (FMath::IsNearlyEqual(Health,MaxHealth) && GetWorld())
	{
		// функция остановки таймера
	    GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
	}
}
//HealUpdate() 

// функция установления здоровья
void USTUHealthActorComponent::SetHealth(float NewHealth) 
{
	// устанавливаем здоровье, проверяем на мин/макс
	Health = FMath::Clamp(NewHealth,0.0f,MaxHealth);

	// каждый раз при изменении здоровья вызываем делегат
	OnHealthChanged.Broadcast(Health);
}




