// My Shoot Them Up Game , All Rights Reserved
// � STUWeaponFXComponent.cpp


#include "Weapon/Components/STUWeaponFXComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"



USTUWeaponFXComponent::USTUWeaponFXComponent()
{

	PrimaryComponentTick.bCanEverTick = true;


}


// Called when the game startsvoid USTUWeaponFXComponent::BeginPlay()
void USTUWeaponFXComponent::BeginPlay()
{
	Super::BeginPlay();


	
}



void USTUWeaponFXComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

// ����������� ������ Niagara ��� ��������
void USTUWeaponFXComponent::PlayImpactFX(const FHitResult& Hit)
{
	// ������� ������ ������� niagara � ���
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(),Effect, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
	// GetWorld()                  - ��������� �� ���, ����� �������� ��� GetWorld() ��� � this
	// Effect                      - ��������� �� ���������� niagara �������� (UNiagaraSystem* Effect)
	// Hit.ImpactPoint             - ���������� � ������� ���������� �����
	// Hit.ImpactNormal.Rotation() - ���������� � ������������ (��������� �������� �������)
	// bool bAutoDestroy           - �������������� ��������, ������������ ������� ����� ������������, �� ��������� ����� � true
	// �������� GetWorld() � Effect �� null ���� ������ �������
}

// �  FHitResult ��������� ������ ���������� ��� ������ ������� (��������� � ����, ������� � �.�.)