// My Shoot Them Up Game , All Rights Reserved
// STUWeaponComponent.cpp


#include "Components/STUWeaponComponent.h"
#include "Weapon/STUBaseWeapon.h"                     // наш класс оружия
#include "GameFramework/Character.h"                  // для получения мэша к которому приаттачиваем оружие

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

	// спавн оружия при старте игры
	SpawnWeapon();

}

// функция делает спавн оружи и присоединяет его к персонажу
void USTUWeaponComponent::SpawnWeapon()
{
	if (!GetWorld())    return;

	// получаем ссылку на Character к которому приаттачиваем оружие
	ACharacter* Character = Cast<ACharacter>(GetOwner());

	if (!Character)	return;



	CurrentWeapon = GetWorld()->SpawnActor<ASTUBaseWeapon>(WeaponClass);
	// Spawn оружия, после спавна CurrentWeapon перестанет быть нулевым
	// ASTUBaseWeapon - класс оружия
	// WeaponClass    - переменная типа ASTUBaseWeapon
	// Сохраняем указатель на соспавненый объект в переменную Weapon

	if (!CurrentWeapon)   return;


	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	// заполняем структуру типа FAttachmentTransformRules, для передачи в качестве параметра в функцию
	// AttachToComponent()

	CurrentWeapon->AttachToComponent(Character->GetMesh(), AttachmentRules, WeaponAttachPointName);  
	// приаттачиваем оружие к Meshу персонажа через сокет WeaponSoket
	// SnapToTarget - актор наследует трансформацию от компонента к которому его присоединяют
	// false        - параметр bInWeldSimulatedBodies - отвечает за физическую симуляцию когда два тела
	// приаттачены друг к другу
	// WeaponAttachPointName    - тектовая переменная, хранит имя сокета
	// Character->GetMesh()     - указатель на SceletalMesh компонент charactera
	// AttachmentRules          - переменная Attachment rools
	// "WeaponSoket"            - название сокета, опциональный

	// CurrentWeapon->SetOwner(GetOwner());
	CurrentWeapon->SetOwner(Character);
	// Компоненту CurrentWeapon, указываем владельца, чтобы через него получить доступ к камере в отрисовке Line Trace
	// Задать владельца можно двумя способами GetOwner() или через переменную Character ( ACharacter* Character = Cast<ACharacter>(GetOwner());)
}


void USTUWeaponComponent::Fire()
{
	if (!CurrentWeapon) return;

	// из класса STUBaseWeapon.h вызыавем функциб Fire
	CurrentWeapon->Fire();
}
// Fire()