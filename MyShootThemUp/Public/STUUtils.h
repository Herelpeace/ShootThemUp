#pragma once
#include "Player/STUPlayerState.h"



class STUUtils
{
public:
	// шаблонная функция возвращает указатель на компонет (HealthComponent, WeaponComponent)
	// принимает указатель на Pawn, испрвлено на актор т.к GetComponentByClass это функция актора а не павна 
	// есть встроенная фнукция FindComponentByClass(), можно пользоваться ею
	template <typename T>
	static T* GetSTPlayerComponent(AActor* PlayerPawn)
	{
		if (!PlayerPawn) return nullptr;

		// получаем указатель на компонент оружия
		const auto Component = PlayerPawn->GetComponentByClass(T::StaticClass());
		// GetComponentByClass             - возвращает указатель на UActor компонет, принимает саб класс компонента который хотим найти
		// T::StaticClass()                - т.к. T имеет только C++ версию, то используем данный способ                                                    
		return Cast<T>(Component);
	}

	bool static AreEnemies(AController* Controller1, AController* Controller2)
	{
		if (!Controller1 || !Controller2 || Controller1 == Controller2) return false;

		// получаем PlayerState первого персонажа
		const auto PlayerState1 = Cast<ASTUPlayerState>(Controller1->PlayerState);

		// PlayerState 2 персонажа
		const auto PlayerState2 = Cast<ASTUPlayerState>(Controller2->PlayerState);

		return PlayerState1 && PlayerState2 && PlayerState1->GetTeamID() != PlayerState2->GetTeamID();
	}

	// функция преобразует int32 в Text (из int32 получаем String а из него Text)
	static FText TextFromInt(int32 Number) { return FText::FromString(FString::FromInt(Number)); }

};