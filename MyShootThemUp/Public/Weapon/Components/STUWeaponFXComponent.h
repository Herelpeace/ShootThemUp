// My Shoot Them Up Game , All Rights Reserved
// � STUWeaponFXComponent.h

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUCoreType.h"
#include "STUWeaponFXComponent.generated.h"

class UNiagaraSystem; // forward declaration
class UPhysicalMaterial;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYSHOOTTHEMUP_API USTUWeaponFXComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USTUWeaponFXComponent();

public:	
	void PlayImpactFX(const FHitResult& Hit);
	// �  FHitResult ��������� ������ ���������� ��� ������ ������� (��������� � ����, ������� � �.�.)

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")  // ����� ���� � ������� ����� ������� ������
	FImpactData DefaultImpactData;  // ��������� ������ �������� ��� niagar� ��� � ������

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	TMap<UPhysicalMaterial*, FImpactData > ImpactDataMap;      // ������������ ��� ������ � ������� ��������: �������� - ������ � ������ � ����

	// TMap - ������������� ���������, ��������� ���� ������ ����� � ��� ������� 
	// ������ �� � ���� ���������� ����� � �������� �.� ������ �� ����� ������������� �������� 
	// � �������� ����� ���������� ���������� ��������, � � �������� �������� niagara �������
};
