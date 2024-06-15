#pragma once


class STUUtils
{
public:
	// шаблонная функция возвращает указатель на компонет (HealthComponent, WeaponComponent)
	// принимает указатель на Pawn
	template <typename T>
	static T* GetSTPlayerComponent(APawn* PlayerPawn)
	{
		if (!PlayerPawn) return nullptr;

		// получаем указатель на компонент оружия
		const auto Component = PlayerPawn->GetComponentByClass(T::StaticClass());
		// GetComponentByClass             - возвращает указатель на UActor компонет, принимает саб класс компонента который хотим найти
		// T::StaticClass()                - т.к. T имеет только C++ версию, то используем данный способ                                                    
		return Cast<T>(Component);
	}

};