// My Shoot Them Up Game , All Rights Reserved
// � STUWeaponFXComponent.cpp


#include "Weapon/Components/STUWeaponFXComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Kismet/GameplayStatics.h"
#include "Components/DecalComponent.h"


USTUWeaponFXComponent::USTUWeaponFXComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// ����������� ������ Niagara ��� ��������
void USTUWeaponFXComponent::PlayImpactFX(const FHitResult& Hit)
{
	auto ImpactData = DefaultImpactData;             // ���������� ������ � ����������

	if (Hit.PhysMaterial.IsValid())                  // �������� ��� � ������� ���� ���������� ��������
	{
		const auto PhysMat = Hit.PhysMaterial.Get(); // �������� ���������� ��������

		if (ImpactDataMap.Contains(PhysMat))         // � ���������� ������� ������� Contains(key) - �������� ���� �� ���� � ����������
		{
			ImpactData = ImpactDataMap[PhysMat];     // ���������� ������ ������� ������������� ���������� �����
		}
	}

	// ������ ������� niagara � ���
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(),ImpactData.NiagaraEffect, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
	// � ��������� ��������� ImpactData �������� ������ niagara
	// GetWorld()                  - ��������� �� ���, ����� �������� ��� GetWorld() ��� � this
	// Effect                      - ��������� �� ���������� niagara �������� (UNiagaraSystem* Effect)
	// Hit.ImpactPoint             - ���������� � ������� ���������� �����
	// Hit.ImpactNormal.Rotation() - ���������� � ������������ (��������� �������� �������)
	// bool bAutoDestroy           - �������������� ��������, ������������ ������� ����� ������������, �� ��������� ����� � true
	// �������� GetWorld() � Effect �� null ���� ������ �������

	// �  FHitResult ��������� ������ ���������� ��� ������ ������� (��������� � ����, ������� � �.�.)

	// ����� �������
	auto DecalComponent = UGameplayStatics::SpawnDecalAtLocation(GetWorld(), ImpactData.DecalData.Material, ImpactData.DecalData.Size, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
	// SpawnDecalAtLocation - ������ ������� ������ 
	// SpawnDecalAttached   - ������� ������ � ������������ � scene Component�
	// ����� ������ ������� ���������� ��������� �� DecalComponent, ������ ��������� �����
	
	// GetWorld()                     - ��������� �� ���
	// ImpactData->DecalData.Material - �������� ������
	// ImpactData->DecalData.Size     - ������ ������
	// Hit.ImpactPoint                - ������� � ����
	// Hit.ImpactNormal.Rotation()    - �������� ������
	// ��������� ������� �� ���������

	if (DecalComponent)
	{
		DecalComponent->SetFadeOut(ImpactData.DecalData.LifeTime, ImpactData.DecalData.FadeOutTime);
		// ImpactData->DecalData.LifeTime     - ����� ����� ����� ���������� �������� ������������ ������
		// ImpactData->DecalData.FadeOutTime  - ������� ������� ����� ������� �������� (������������)
		// 3 ������� ���������� ������� �� �������� ownera ������, ����� ����� ��� ������ �������������� SpawnDecalAttached 
	}
}

