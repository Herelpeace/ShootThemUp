#pragma once
 
// пока что содержит шаблонную функцию поиска notify в заданном классе 
// используетс€ в STUWeaponComponent.cpp в функции InitAnimations()

class AnimUtils
{

public:

// шаблонна€ функци€ поиска notify в заданном классе
// template <typename T> - объ€вление шаблонной функции
// T*                    - возвращает указатель на тип T
// FindNotifyByClass     - им€ функции
// UAnimSequenceBase*    - в данном классе содержитс€ массив всех notify
	template <typename T>
	static T* FindNotifyByClass(UAnimSequenceBase* Animation)
	{
		if (!Animation) return nullptr;

		// получаем значени€ массива структур эвентов Notifys. 	TArray<struct FAnimNotifyEvent> Notifies;
		// масиив анимационных эвентов
		const auto NotifyEvents = Animation->Notifies;

		// перебираем элементы массива
		for (auto NotifyEvent : NotifyEvents)
		{
			auto AnimNotify = Cast<T>(NotifyEvent.Notify);

			// EquipFinishedNotify - сохран€ем найденный указатель Notify, в локальную переменную
			// NotifyEvent.Notify  - в поле Notify содержитс€ Notify
			// Cast <>             - делаем Cast до нашего класса, если Cast прошел успешно значит Notify из нашего класса

			// вызываем делегат если Notify найден
			if (AnimNotify)
			{
				return AnimNotify;
			}
		}
		return nullptr;
	}


};