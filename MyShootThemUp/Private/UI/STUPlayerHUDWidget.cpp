// My Shoot Them Up Game , All Rights Reserved
// � STUPlayerHUDWidget.cpp


#include "UI/STUPlayerHUDWidget.h"
#include "Components/STUHealthActorComponent.h"  

float USTUPlayerHUDWidget::GetHealthPercent() const
{
	// �������� ��������� �� ������ ������
	const auto Player = GetOwningPlayerPawn();
	// GetOwningPlayerPawn() - ������� ���������� ��������� �� Pawna, � ��������

	if (!Player) return 0.0f;

	// �������� ��������� �� ��������� ��������, Health Component
	const auto Component = Player->GetComponentByClass(USTUHealthActorComponent::StaticClass());
	// GetComponentByClass                     - ���������� ��������� �� UActor ��������, ��������� ��� ����� ���������� ������� ����� �����
	// USTUHealthActorComponent::StaticClass() - �.�. Health Component ����� ������ C++ ������, �� ���������� ������ ������                                                    

	// ��������� ��������� �� UActor � ��������� ����������� ����������
	const auto HealthComponent = Cast<USTUHealthActorComponent>(Component);
	// USTUHealthActorComponent - ��������� ��������� �������� ����� ��������
	// Component                - UActor ���������, ������� ����������

	if (!HealthComponent) return 0.0f;

	return HealthComponent->GetHealthPercent();

}

