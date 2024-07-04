#pragma once


class STUUtils
{
public:
	// ��������� ������� ���������� ��������� �� �������� (HealthComponent, WeaponComponent)
	// ��������� ��������� �� Pawn, ��������� �� ����� �.� GetComponentByClass ��� ������� ������ � �� ����� 
	// ���� ���������� ������� FindComponentByClass(), ����� ������������ ��
	template <typename T>
	static T* GetSTPlayerComponent(AActor* PlayerPawn)
	{
		if (!PlayerPawn) return nullptr;

		// �������� ��������� �� ��������� ������
		const auto Component = PlayerPawn->GetComponentByClass(T::StaticClass());
		// GetComponentByClass             - ���������� ��������� �� UActor ��������, ��������� ��� ����� ���������� ������� ����� �����
		// T::StaticClass()                - �.�. T ����� ������ C++ ������, �� ���������� ������ ������                                                    
		return Cast<T>(Component);
	}

};