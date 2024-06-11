// My Shoot Them Up Game , All Rights Reserved
// � STUHealthActorComponent.cpp


#include "Components/STUHealthActorComponent.h"
#include "GameFramework/Actor.h"                // ��� ��������� ������ �� Actora �������� ����������� ������ �����
#include "Engine/World.h"   // ����� �������� ������ �� ���, �������������� ��������� � ������� ����
#include "TimerManager.h"   // ��� �������

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
	     

}
// OnTakeAnyDamageHandle ������� �����

// ������� �������������� ��������
void USTUHealthActorComponent::HealUpdate() 
{
	SetHealth(Health + HealModifier);

	// ������������� ������ ����� �������� �������� ���������
	// ��������� ����� �������� �� ����� ������ �������������, �������� ���� �� null
	if (FMath::IsNearlyEqual(Health,MaxHealth) && GetWorld())
	{
		// ������� ��������� �������
	    GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
	}
}
//HealUpdate() 

// ������� ������������ ��������
void USTUHealthActorComponent::SetHealth(float NewHealth) 
{
	// ������������� ��������, ��������� �� ���/����
	Health = FMath::Clamp(NewHealth,0.0f,MaxHealth);

	// ������ ��� ��� ��������� �������� �������� �������
	OnHealthChanged.Broadcast(Health);
}




