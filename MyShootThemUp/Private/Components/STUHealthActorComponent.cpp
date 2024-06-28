// My Shoot Them Up Game , All Rights Reserved
// В STUHealthActorComponent.cpp


#include "Components/STUHealthActorComponent.h"
#include "GameFramework/Actor.h"                // для получения ссылки на Actora которому принадлежит данный класс
#include "GameFramework/Pawn.h"
#include "GameFramework/Controller.h"
#include "Engine/World.h"   // чтобы получать ссылку на мир, ТаймерМенеджер находится в объекте мира
#include "TimerManager.h"   // для таймера
#include "Camera/CameraShakeBase.h"

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

	PlayCameraShakee();  // тряска камеры	     

}
// OnTakeAnyDamageHandle функция урона

// функция восстановления здоровья
void USTUHealthActorComponent::HealUpdate() 
{
	SetHealth(Health + HealModifier);

	// останавливаем таймер когда здоровье достигло максимума
	// проверяем равно ли здоровье максимальному, проверка мира на null
	if (IsHealthFull() && GetWorld())
	{
		// функция остановки таймера
	    GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
	}
}
//HealUpdate() 

// функция установления здоровья
void USTUHealthActorComponent::SetHealth(float NewHealth) 
{
	const auto NextHealth  = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
	const auto HealthDelta = NextHealth - Health; // разница между следующим значением здоровья и текущим

	// устанавливаем новое значение здоровья
	Health = NextHealth;

	// каждый раз при изменении здоровья вызываем делегат, передаем в него 2 параметра
	// функции подписанные на данный делегат так же принимают 2 параметра
	OnHealthChanged.Broadcast(Health, HealthDelta);
}

// добавляет здоровье при подборе
bool USTUHealthActorComponent::TryToAddHealth(float HealthAmount)
{
	// либо dead либо полное здоровье, то ничего не прибавляем, выходим
	if (isDead() || IsHealthFull()) return false;

	SetHealth(Health+ HealthAmount);

	return true;
}

// true - здоровье максимум
bool USTUHealthActorComponent::IsHealthFull() const
{
	// проверят равны ли между собой переменные Health и MaxHealth
	return FMath::IsNearlyEqual(Health, MaxHealth);
}


// проигрывание эффекта тряски
void USTUHealthActorComponent::PlayCameraShakee()
{
	if (isDead()) return;

	// получаем указатель на Pawn
	const auto Player = Cast<APawn>(GetOwner());
	// делаем Cast указателя который возвращает GetOwner() к классу Pawn
	// указатель на контроллер находится в Pawn, поэтому нет смысла кастить до Charactera

	if (!Player) return;

	// получаем указатель на контроллер
	const auto Controller = Player->GetController<APlayerController>();

	if (!Controller || !Controller->PlayerCameraManager) return;


	// вызываем эффект тряски, передаем в функцию переменную типа UCameraShakeBase
	Controller->PlayerCameraManager->StartCameraShake(CameraShake);

}


