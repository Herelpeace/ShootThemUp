#pragma once
#include "Player/STUPlayerState.h"



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

	bool static AreEnemies(AController* Controller1, AController* Controller2)
	{
		if (!Controller1 || !Controller2 || Controller1 == Controller2) return false;

		// �������� PlayerState ������� ���������
		const auto PlayerState1 = Cast<ASTUPlayerState>(Controller1->PlayerState);

		// PlayerState 2 ���������
		const auto PlayerState2 = Cast<ASTUPlayerState>(Controller2->PlayerState);

		return PlayerState1 && PlayerState2 && PlayerState1->GetTeamID() != PlayerState2->GetTeamID();
	}

	// ������� ����������� int32 � Text (�� int32 �������� String � �� ���� Text)
	static FText TextFromInt(int32 Number) { return FText::FromString(FString::FromInt(Number)); }

};