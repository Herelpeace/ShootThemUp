// My Shoot Them Up Game , All Rights Reserved
// � STUWeaponFXComponent.cpp


#include "Weapon/Components/STUWeaponFXComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "PhysicalMaterials/PhysicalMaterial.h"



USTUWeaponFXComponent::USTUWeaponFXComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// ����������� ������ Niagara ��� ��������
void USTUWeaponFXComponent::PlayImpactFX(const FHitResult& Hit)
{
	auto Effect = DefaultEffect;  // ���������� ������ � ����������

	if (Hit.PhysMaterial.IsValid())  // �������� ��� � ������� ���� ���������� ��������
	{
		const auto PhysMat = Hit.PhysMaterial.Get(); // �������� ���������� ��������

		if (EffectsMap.Contains(PhysMat))  // � ���������� ������� ������� Contains(key) - �������� ���� �� ���� � ����������
		{
			Effect = EffectsMap[PhysMat]; // ���������� ������ ������� ������������� ���������� �����
		}
	}

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