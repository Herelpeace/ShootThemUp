// My Shoot Them Up Game , All Rights Reserved
// В STUWeaponComponent.cpp


#include "Components/STUWeaponComponent.h"
#include "Weapon/STUBaseWeapon.h"                     // наш класс оружия
#include "GameFramework/Character.h"                  // для получения мэша к которому приаттачиваем оружие
#include "Animations/STUEquipFinishedAnimNotify.h"    // наш класс Notify 1
#include "Animations/STUReloadFinishedAnimNotify.h"   // notify перезарядки
#include "Animations/AnimUtils.h"                     // содержит шаблонную функцию поиска notify в заданном классе

DEFINE_LOG_CATEGORY_STATIC(LogWeaponComponent, All, All);

// глобальная переменная, количество оружия у персонажа
constexpr static int32 WeaponNum = 2;

// Sets default values for this component's properties
USTUWeaponComponent::USTUWeaponComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void USTUWeaponComponent::BeginPlay()
{

	Super::BeginPlay();

	// проверка что у персонажа установлены обе модели оружия
	checkf(WeaponData.Num() == WeaponNum, TEXT("Our character can hold only %i weapon items"), WeaponNum);

	CurrentWeaponIndex = 0; // индекс текущего оружия в массиве Weapons

	// проигрываем анимацию смены оружия
	InitAnimations();

	// спавн оружия при старте игры, на спине персонажа
	SpawnWeapons();

	// устанавливаем текущее оружие в руках персонажа
	EquipWeapon(CurrentWeaponIndex);

}

// удаляем оружие со сцены после уничтожения персонажа
void USTUWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	CurrentWeapon = 0;

	for (auto Weapon:Weapons)
	{
		// отсоединяем модель оружия от персонажа
		Weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform );
		// удаляем актора оружия
		Weapon->Destroy();
	}

	// очищаем массив
	Weapons.Empty();

	Super::EndPlay(EndPlayReason);

}

// функция делает спавн оружия и присоединяет его к персонажу за спину
void USTUWeaponComponent::SpawnWeapons()
{
	// получаем указатель на Characterа к которому приаттачиваем оружие
	ACharacter* Character = Cast<ACharacter>(GetOwner());

	if (!Character|| !GetWorld())	return;

	// перебираем элементы массива оружия заполненные в редакторе и присоединяем их к персонажу
	for (auto OneWeaponData : WeaponData)  // в OneWeaponData поочередно присваиваем элементы массива структур WeaponData?
	{
		auto Weapon = GetWorld()->SpawnActor<ASTUBaseWeapon>(OneWeaponData.WeaponClass);
		// Spawn оружия, после спавна CurrentWeapon перестанет быть нулевым
		// ASTUBaseWeapon               - класс оружия
		// OneWeaponData.WeaponClass    - поле структуры OneWeaponData, типа ASTUBaseWeapon
		// Сохраняем указатель на соспавненый объект в переменную Weapon

		if (!Weapon)   continue;

		// при срабатывании делегата OnClipEmpty будет вызвана функция OnEmptyClip в данном классе
		Weapon->OnClipEmpty.AddUObject(this, &USTUWeaponComponent::OnEmptyClip);

		// Заспавненому оружию присваиваем владельца
		Weapon->SetOwner(Character);

		// добавляем заспавненное оружие в массив Weapons
		Weapons.Add(Weapon);

		// присоединяем модель оружия к модели персонажа за спину
		AttachWeaponToSocket(Weapon, Character->GetMesh(), WeaponArmorySocketName);
		// Weapon - указатель на оружие которое хотим присоединить к персонажу
		// Character->GetMesh() - эш персонажа

	}

	// CurrentWeapon->SetOwner(GetOwner());
	//CurrentWeapon->SetOwner(Character);
	// Компоненту CurrentWeapon, указываем владельца, чтобы через него получить доступ к камере в отрисовке Line Trace
	// Задать владельца можно двумя способами GetOwner() или через переменную Character ( ACharacter* Character = Cast<ACharacter>(GetOwner());)
}

// присоединеняем модель оружия к модели персонажа
void USTUWeaponComponent::AttachWeaponToSocket(ASTUBaseWeapon* Weapon, USceneComponent* SceneComponent , const FName& SocketName )
{
	if (!Weapon || !SceneComponent) return;

	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	// заполняем структуру типа FAttachmentTransformRules, для передачи в качестве параметра в функцию
	// AttachToComponent()

	//CurrentWeapon->AttachToComponent(Character->GetMesh(), AttachmentRules, WeaponAttachPointName);  старая функция 
	
	// функция присоединения модели оружия к модели персонажа
	Weapon->AttachToComponent(SceneComponent, AttachmentRules, SocketName);
	// SceneComponent           - получаем мэш, по сути это родительский класс мэша. Character->GetMesh()
	// AttachmentRules          - переменная Attachment rools
	// SocketName               - название сокета, опциональный
}

// функция устанавливает текущее оружие в руке персонажа, принимает индекс для массива Weapons
void USTUWeaponComponent::EquipWeapon(int32 WeaponIndex)
{
	// проверка корректности индекса массива
	if (WeaponIndex < 0 || WeaponIndex >= Weapons.Num())
	{
		UE_LOG(LogWeaponComponent, Warning, TEXT("Invalid Weapon Index"))
		return;
	}

	// получаем указатель на Characterа к которому приаттачиваем оружие
	ACharacter* Character = Cast<ACharacter>(GetOwner());

	if (!Character) return;

	// при повторном вызове функции убираем текущее оружие за спину
	if (CurrentWeapon)
	{
		// останавливаем стрельбу
		CurrentWeapon->StopFire();

		// присоединяем модель оружия к модели персонажа за спину
		AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponArmorySocketName);
		// Weapon - указатель на оружие которое хотим присоединить к персонажу
		// Character->GetMesh() - эш персонажа
	}

	// в CurrentWeapon записываем указатель на текущее оружие
	CurrentWeapon = Weapons[WeaponIndex];

	// меняем анимацию перезарядки, может работать некорректно при сортировке массива
	//CurrentReloadAnimMontage = WeaponData[WeaponIndex].ReloadAnimMontage;
	// WeaponData[WeaponIndex] - индекс структуры в которой содержится класс текущего оружия и его анимация перезарядки

	// более надежный способ, пробегаем по массиву со структурами WeaponData и ищем структуру
	// которая соответствует текущему классу оружия
	// после нахождения структуры берем из нее анимацию перезарядки

	const auto CurrentWeaponData = WeaponData.FindByPredicate([&](const FWeaponData& Data) { return Data.WeaponClass == CurrentWeapon->GetClass(); });
	// в WeaponData ищем структуру которая будет равна CurrentWeapon->GetClass(); ,текущему классу оружия
	// CurrentWeaponData - переменная для сохранения найденной структуры
	// FindByPredicate   - функция массива, которая ищет в массиве элемент по заданным параметрам 
	// [&]               - нужен чтобы захватить внешнюю переменную CurrentWeapon
	// [&](const FWeaponData& Data) { return Data.WeaponClass == CurrentWeapon->GetClass() - лямбда выражение
	// при первом совпадении с элементом массива,вернется указатель на этот элемент

	// в переменную текущей анимации присваиваем анимацию текущего оружия найденного в массиве
	CurrentReloadAnimMontage = CurrentWeaponData ? CurrentWeaponData->ReloadAnimMontage : nullptr;

	// присоединяем его к рукам 
	AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(),WeaponEquipSocketName);

	// перед проигрыванием анимации меняем состояние флага на true
	EquipAnimProgress = true;

	// анимация смены оружия
	PlayAnimMontage(EquipAnimMontage);
}

// старт стрельбы
void USTUWeaponComponent::StartFire()
{
	// проверка, проигрывается ли анимация
	if (!CanFire()) return;

	// из класса STUBaseWeapon.h вызыавем функциб StartFire
	CurrentWeapon->StartFire();
}
// StartFire()

// стоп стрельбы
void USTUWeaponComponent::StopFire()
{
	if (!CurrentWeapon) return;

	// из класса STUBaseWeapon.h вызыавем функциб StopFire
	CurrentWeapon->StopFire();
}
// StopFire()

// смена оружия
void USTUWeaponComponent::NextWeapon()
{
	// проверяем можно ли менять оружие (проигрывается ли анимация смены оружия)
	if (!CanEquip()) return;
	CurrentWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
	// увеличиваем индекс текущего оружия на 1
	// берем по модулю от длинны массива, чтобы не выйти за его границы
	// Weapons.Num() - количество элементов в массиве Weapons

	// меняем оружие на следующее
	EquipWeapon(CurrentWeaponIndex);
}

// проигрывание анимации
void USTUWeaponComponent::PlayAnimMontage(UAnimMontage* Animation)
{
	// получаем указатель на Character т.к в нем есть функция проигрывания AnimMontage
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	
	if (!Character) return;

	// анимация смены оружия
	Character->PlayAnimMontage(Animation);
}

// находим Notify и подписываемся на него
void USTUWeaponComponent::InitAnimations()
{
	/*
	if (!EquipAnimMontage) return;

	// получаем значения массива структур эвентов Notifys. 	TArray<struct FAnimNotifyEvent> Notifies;
	// масиив анимационных эвентов
	const auto NotifyEvents = EquipAnimMontage->Notifies;

	// перебираем элементы массива
	for (auto NotifyEvent : NotifyEvents)
	{
		auto EquipFinishedNotify = Cast<USTUEquipFinishedAnimNotify>(NotifyEvent.Notify);

		// EquipFinishedNotify - сохраняем найденный указатель Notify, в локальную переменную
		// NotifyEvent.Notify  - в поле Notify содержится Notify
		// Cast <>             - делаем Cast до нашего класса, если Cast прошел успешно значит Notify из нашего класса

		// вызываем делегат если Notify найден
		if (EquipFinishedNotify)
		{
			// биндим функцию на делегат
			EquipFinishedNotify->OnNotified.AddUObject(this, &USTUWeaponComponent::OnEquipFinished);
			break;
		}
	}

	*/
	
	// шаблонная функция которая ищет notify 
	auto EquipFinishedNotify = AnimUtils::FindNotifyByClass<USTUEquipFinishedAnimNotify>(EquipAnimMontage);

	// вызываем делегат если Notify найден
	if (EquipFinishedNotify)
	{
		// биндим функцию на делегат
		EquipFinishedNotify->OnNotified.AddUObject(this, &USTUWeaponComponent::OnEquipFinished);
	}
	else
	{
		UE_LOG(LogWeaponComponent, Error, TEXT("Equip anim notify is forgotten to set"));  // не установлен notify в анимации смены оружия
		checkNoEntry();
	}

	for (auto OneWeaponData : WeaponData)
	{
		// шаблонная функция которая ищет notify 
		auto ReloadFinishedNotify = AnimUtils::FindNotifyByClass<USTUReloadFinishedAnimNotify>(OneWeaponData.ReloadAnimMontage);
		// если ничего не нашли переходим к следующему элементу
		if (!ReloadFinishedNotify)
		{
			UE_LOG(LogWeaponComponent, Error, TEXT("Reload anim notify is forgotten to set"));  // не установлен notify в анимации перезарядки оружия
			checkNoEntry();
		}

		// биндим функцию окончания перезарядки на делегат
		ReloadFinishedNotify->OnNotified.AddUObject(this, &USTUWeaponComponent::OnReloadFinished);
	}

}

// callback который биндим на делегат OnNotified, передаем в него Мэш Charactera, чтобы логика на событие Notify срабатывала только у персонажа 
void USTUWeaponComponent::OnEquipFinished(USkeletalMeshComponent* MeshComponent)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character || MeshComponent != Character->GetMesh()) return;

	// после проигрывания амнимации возвращаем флаг в прежнее состояние
	EquipAnimProgress = false;
}

// callback который биндим на делегат OnNotified, передаем в него Мэш Charactera, чтобы логика на событие Notify срабатывала только у персонажа 
void USTUWeaponComponent::OnReloadFinished(USkeletalMeshComponent* MeshComponent)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character || MeshComponent != Character->GetMesh()) return;

	// после проигрывания амнимации возвращаем флаг в прежнее состояние
	ReloadAnimProgress = false;
}


// вернет true когда можно стрелять
bool USTUWeaponComponent::CanFire() const
{
	// если указатель на текущее оружие не нулевой и не проигрывается анимация смены или стрельбы
	return CurrentWeapon && !EquipAnimProgress && !ReloadAnimProgress;

}

// вернет true когда можно менять оружие
bool USTUWeaponComponent::CanEquip() const
{
	return !EquipAnimProgress && !ReloadAnimProgress;
}

// вернет true когда можно перезаряжаться
bool USTUWeaponComponent::CanReload() const
{
	// если указатель на текущее оружие не нулевой и не проигрывается анимация смены или стрельбы или перезарядки и  количество патронов меньше дефолтного и магазинов > 0
	return CurrentWeapon && !EquipAnimProgress && !ReloadAnimProgress && CurrentWeapon->CanReload();
}

// перезарядка по нажатию клавиши
void USTUWeaponComponent::Reload()
{
	ChangeClip();
}

// перезарадка по делегату, callback на делегат OnClipEmpty
void USTUWeaponComponent::OnEmptyClip()
{
	ChangeClip();
}

// вся логика перезарядки находится в этой функции
void USTUWeaponComponent::ChangeClip()
{
	if (!CanReload()) return;

	CurrentWeapon->StopFire();

	// функция перезарядки у базового класса 
	CurrentWeapon->ChangeClip();

	// выставлям флаг на время перезарядки
	ReloadAnimProgress = true;

	// проигрываем анимацию перезарядки
	PlayAnimMontage(CurrentReloadAnimMontage);
}


// возвращает UIData текущего оружия, внутри функции, внутреннее состояние класса не меняет
bool USTUWeaponComponent::GetCurrentWeaponUIData(FWeaponUIData& UIData) const
{
	if (CurrentWeapon)
	{
		UIData = CurrentWeapon->GetUIData();
		return true;
	}
	return false;
}

// возвращает Current AmmoData текущего оружия, внутри функции, внутреннее состояние класса не меняет
bool USTUWeaponComponent::GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const
{
	if (CurrentWeapon)
	{
		AmmoData = CurrentWeapon->GetAmmoData();
		return true;
	}
	return false;
}