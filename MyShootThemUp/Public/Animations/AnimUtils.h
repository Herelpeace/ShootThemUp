#pragma once
 
// ���� ��� �������� ��������� ������� ������ notify � �������� ������ 
// ������������ � STUWeaponComponent.cpp � ������� InitAnimations()

class AnimUtils
{

public:

// ��������� ������� ������ notify � �������� ������
// template <typename T> - ���������� ��������� �������
// T*                    - ���������� ��������� �� ��� T
// FindNotifyByClass     - ��� �������
// UAnimSequenceBase*    - � ������ ������ ���������� ������ ���� notify
	template <typename T>
	static T* FindNotifyByClass(UAnimSequenceBase* Animation)
	{
		if (!Animation) return nullptr;

		// �������� �������� ������� �������� ������� Notifys. 	TArray<struct FAnimNotifyEvent> Notifies;
		// ������ ������������ �������
		const auto NotifyEvents = Animation->Notifies;

		// ���������� �������� �������
		for (auto NotifyEvent : NotifyEvents)
		{
			auto AnimNotify = Cast<T>(NotifyEvent.Notify);

			// EquipFinishedNotify - ��������� ��������� ��������� Notify, � ��������� ����������
			// NotifyEvent.Notify  - � ���� Notify ���������� Notify
			// Cast <>             - ������ Cast �� ������ ������, ���� Cast ������ ������� ������ Notify �� ������ ������

			// �������� ������� ���� Notify ������
			if (AnimNotify)
			{
				return AnimNotify;
			}
		}
		return nullptr;
	}


};