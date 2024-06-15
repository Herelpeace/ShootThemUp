#pragma once


class STUUtils
{
public:
	// ��������� ������� ���������� ��������� �� �������� (HealthComponent, WeaponComponent)
	// ��������� ��������� �� Pawn
	template <typename T>
	static T* GetSTPlayerComponent(APawn* PlayerPawn)
	{
		if (!PlayerPawn) return nullptr;

		// �������� ��������� �� ��������� ������
		const auto Component = PlayerPawn->GetComponentByClass(T::StaticClass());
		// GetComponentByClass             - ���������� ��������� �� UActor ��������, ��������� ��� ����� ���������� ������� ����� �����
		// T::StaticClass()                - �.�. T ����� ������ C++ ������, �� ���������� ������ ������                                                    
		return Cast<T>(Component);
	}

};