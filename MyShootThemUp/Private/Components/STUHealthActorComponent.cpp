// My Shoot Them Up Game , All Rights Reserved
// � STUHealthActorComponent.cpp


#include "Components/STUHealthActorComponent.h"
#include "GameFramework/Actor.h"                // ��� ��������� ������ �� Actora �������� ����������� ������ �����
#include "GameFramework/Pawn.h"
#include "GameFramework/Controller.h"
#include "Engine/World.h"   // ����� �������� ������ �� ���, �������������� ��������� � ������� ����
#include "TimerManager.h"   // ��� �������
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

	check(MaxHealth>0);  // ����� � ��������� �� ��������� ����, �.� �� ��� ���������� ���������� �������

	// �� ������ ���� ��� ��� ������ ������������� �������� �������� �� 100
	SetHealth(MaxHealth);  

	// �������� ������ �� Actor �������� ����������� ������ �����
	AActor* ComponentOwner = GetOwner();  
	if (ComponentOwner) // �������� �� null
	{
	    // ������������� �� ������� OnTakeAnyDamage � ������ �������
	    ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &USTUHealthActorComponent::OnTakeAnyDamage);
	    // this - ��������� �� ������� instance
	    // ASTUBaseCharacter::OnTakeAnyDamageHandle - ������� �����, ���������������� �������
	}

}


// ������� ������� ����� ���������� ��� ��������� �����
void USTUHealthActorComponent::OnTakeAnyDamage(
    AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	//UE_LOG(LogHealthComponent, Warning, TEXT(" ������� ����!!"));
	// ���� ���� ����� 0 ���  isDead() = 0 ��� ������ �� ��� - null (��� �������) ������ �� ������ �������
	if (Damage <= 0.0f || isDead() || !GetWorld())   return;

	// ������������� ������� �������� � ����������� �� �������� Damage
	SetHealth(Health - Damage);

	// ������� ��������� ������� �������������� ��������
	GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);

	// ����� ��������� ��� �� ��������
	if (isDead())
	{
		// ����� ������� ��������� ���� ��� � ��������� �� �������� ��������
	    onDeath.Broadcast();
	}
	else 
	if (AutoHeal)  //TimerManager ��������� � ������� UWorld, ��� ���� - ��� ������� � �������
	{
		// ������ ����� �������� ������� HealUpdate
	    GetWorld()->GetTimerManager().SetTimer(HealTimerHandle, this, &USTUHealthActorComponent::HealUpdate, HealUpdateTime, true,HealDelay);

		// HealTimerHandle                       - ������ ���� FTimerHandle
		// this                                  - ��������� �� ������ � ������� ����� ���������� ������� 
	    // &USTUHealthActorComponent::HealUpdate - ������ �� ���������� �������
		// HealUpdateTime                        - ������� ���������� �������
		// true                                  - ���������� �� ������ ��������
		// HealDelay                             - �������� ����� ������ �������
	}  

	PlayCameraShakee();  // ������ ������	     

}
// OnTakeAnyDamageHandle ������� �����

// ������� �������������� ��������
void USTUHealthActorComponent::HealUpdate() 
{
	SetHealth(Health + HealModifier);

	// ������������� ������ ����� �������� �������� ���������
	// ��������� ����� �� �������� �������������, �������� ���� �� null
	if (IsHealthFull() && GetWorld())
	{
		// ������� ��������� �������
	    GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
	}
}
//HealUpdate() 

// ������� ������������ ��������
void USTUHealthActorComponent::SetHealth(float NewHealth) 
{
	const auto NextHealth  = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
	const auto HealthDelta = NextHealth - Health; // ������� ����� ��������� ��������� �������� � �������

	// ������������� ����� �������� ��������
	Health = NextHealth;

	// ������ ��� ��� ��������� �������� �������� �������, �������� � ���� 2 ���������
	// ������� ����������� �� ������ ������� ��� �� ��������� 2 ���������
	OnHealthChanged.Broadcast(Health, HealthDelta);
}

// ��������� �������� ��� �������
bool USTUHealthActorComponent::TryToAddHealth(float HealthAmount)
{
	// ���� dead ���� ������ ��������, �� ������ �� ����������, �������
	if (isDead() || IsHealthFull()) return false;

	SetHealth(Health+ HealthAmount);

	return true;
}

// true - �������� ��������
bool USTUHealthActorComponent::IsHealthFull() const
{
	// �������� ����� �� ����� ����� ���������� Health � MaxHealth
	return FMath::IsNearlyEqual(Health, MaxHealth);
}


// ������������ ������� ������
void USTUHealthActorComponent::PlayCameraShakee()
{
	if (isDead()) return;

	// �������� ��������� �� Pawn
	const auto Player = Cast<APawn>(GetOwner());
	// ������ Cast ��������� ������� ���������� GetOwner() � ������ Pawn
	// ��������� �� ���������� ��������� � Pawn, ������� ��� ������ ������� �� Charactera

	if (!Player) return;

	// �������� ��������� �� ����������
	const auto Controller = Player->GetController<APlayerController>();

	if (!Controller || !Controller->PlayerCameraManager) return;


	// �������� ������ ������, �������� � ������� ���������� ���� UCameraShakeBase
	Controller->PlayerCameraManager->StartCameraShake(CameraShake);

}


