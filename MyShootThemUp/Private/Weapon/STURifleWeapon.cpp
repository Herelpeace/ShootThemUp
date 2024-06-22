// My Shoot Them Up Game , All Rights Reserved
// В STURifleWeapon.cpp


#include "Weapon/STURifleWeapon.h"
#include "Engine/World.h"                        // 
#include "DrawDebugHelpers.h"                    // дли рисования линий (Line Trace)
#include "Weapon/Components/STUWeaponFXComponent.h"


ASTURifleWeapon::ASTURifleWeapon()  // конструктор класса ASTURifleWeapon, нужен для создания компонета STUWeaponFXComponent
{
	// в переменную FX компонета записываем компонент USTUWeaponFXComponent
	WeaponFXComponent = CreateDefaultSubobject<USTUWeaponFXComponent>("WeaponFXComponent");
}

void ASTURifleWeapon::BeginPlay()
{
	Super::BeginPlay();

	check(WeaponFXComponent);   // drbug проверка компонента на null
}

// функция бинда кнопки мышки, вызывается из Charactera до тех пор пока кнопка мышки не отпущена
// начало стрельбы
void ASTURifleWeapon::StartFire()
{
	// UE_LOG(LogBaseWeapon, Warning, TEXT(" StartFire!!! "));

	// запуск таймера
	GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &ASTURifleWeapon::MakeShot, TimeBetweenShots, true);

	// ShotTimerHandle           - имя создаваемого таймера
	// this                      - указатель на объект
	// &ASTUBaseWeapon::MakeShot - функция которая будет вызываться
	// TimeBetweenShots          - время между вызовами функции ( float переменная,скорость стрельбы)
	// true                      - цикличная работа таймера ( false - единорозовый вызов )

	// функция производит выстрел
	MakeShot();
}


// функция бинда кнопки мышки, вызывается из Charactera, вызывается после того как отпустили кнопку мышки
// конец стрельбы
void ASTURifleWeapon::StopFire()
{
	// UE_LOG(LogBaseWeapon, Warning, TEXT(" StopFire!!! "));

	// остановка таймера
	GetWorldTimerManager().ClearTimer(ShotTimerHandle);
}

// функция содержит всю логику выстрела
void ASTURifleWeapon::MakeShot()
{
	UE_LOG(LogTemp, Warning, TEXT("Make Shot"));

	// проверка мира на null, аммуниция пуста IsAmmoEmpty() = true
	if (!GetWorld() || IsAmmoEmpty())
	{
		StopFire();
		return;
	}

	FVector TraceStart, TraceEnd;
	// начальная и конечная точки выстрела

	if (!GetTraceData(TraceStart, TraceEnd))
	{
		StopFire();
		return;
	}

	FHitResult HitResult;
	// структура в которую сохраняем информацию о пересечении LineTrace с объектами
	// структура FHitResult содержит поля: время пересечения, точка пересечения, нормаль, указатель на актор с которым
	// пересеклись и т.д. так же FHitResult содержит информацию было пересечение или нет, переменная bBlockingHit

	// заполняем структуру HitResult
	MakeHit(HitResult, TraceStart, TraceEnd);


	// если пересечение было, попали в какой либо актор
	if (HitResult.bBlockingHit)
	{
		// функция нанесения урона актору
		MakeDamage(HitResult);


		// функция отрисовки линии,пердаем коодинаты в виде переменных (без нашей функции, рефакторинга)
		//DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Green, false, 3.0f, 0, 3.0f);

		//DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), HitResult.ImpactPoint, FColor::Green, false, 3.0f, 0, 3.0f);

		// GetWorld()    - указатель на мир
		// TraceStart    - координаты откуда начинается линия
		// TraceEnd      - конечная точка
		// FColor::Green - цвет линии
		// false         - линия не остается навсегда, исчезает через какое то время
		// 3.0f          - время отображения линии до исчезновения
		// 0             - порядок отрисовки глубины
		// 3.0f          - толщина линии

		// SocketTransform.GetLocation() - координаты откуда начинается линия
		// HitResult.ImpactPoint         - конечная точка


		// рисуем сферу в месте пересечения
		//DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.0f, 24.0f, FColor::Green, false, 5.0f);

		// GetWorld()            - указатель на мир
		// HitResult.ImpactPoint - центр сферы, координаты в которых рисуем сферу, берем координаты точки пересечения
		// 10.0f                 - радиус сферы
		// 24.0f                 - количество сегментов
		// FColor::Green         - цвет сферы
		// false                 - ?
		// 5.0f                  - время отображения сферы секунд

		// UE_LOG(LogBaseWeapon, Warning, TEXT(" Bone: %s "), *HitResult.BoneName.ToString());

		WeaponFXComponent->PlayImpactFX(HitResult);
		// вызываем функцию проигрвания FX, передаем Hit объект (информацию об столкновении)

	}
	else
	{
		DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), TraceEnd, FColor::Green, false, 3.0f, 0, 3.0f);
		// если никуда не попали то конечную точку рисуем в TraceEnd
	}

	// уменьшаем количество патронов
	DecreaseAmmo();
}
// MakeShot() 

// заполняем начальные и конечные координаты для рисуемой линии
bool ASTURifleWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
	FVector  ViewLocation;  // для сохранения координат
	FRotator ViewRotation;  // для сохранения вращения

	if (!GetPlayerViewPoint(ViewLocation, ViewRotation)) return false;


	// получем трансфорамцию сокета
	// const FTransform SocketTransform = WeaponMesh->GetSocketTransform(MuzzleSocketName);

	// GetSocketTransform - получает Transform сокета, принимает 2 параметра
	// MuzzleSocketName   - имя сокета
	// TypeCoordinate     - тип координат в которой хотим получить сокет. Параметр
	// не указан значит получаем координаты в мировой системе координат

	// точка начала выстрела, записываем в нее положение сокета
	// точка начала выстрела, записываем в нее положение камеры
	TraceStart = ViewLocation; // SocketTransform.GetLocation();

	// переводим угол разброса в радианы
	const auto HalfRad = FMath::DegreesToRadians(BulletSpread);

	// вектор направления выстрела (единичный)
	const FVector ShootDirection = FMath::VRandCone(ViewRotation.Vector(), HalfRad); //	SocketTransform.GetRotation().GetForwardVector();

	// SocketTransform.GetRotation() - получаем кватернион наших векторов
	// GetForwardVector()            - возвращает Forward вектор кватерниона (вектор поворота по оси Х)
	// ViewRotation.Vector()         - возвращает Forward вектор
	// FMath::VRandCone()            - получаем случайный вектор в коническом пространстве
	// ViewRotation.Vector()         - направление в котором получаем разброс
	// HalfRad                       - половина угла расхождения конуса ( в радианах)

	// конечная точка выстрела
	TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;

	// к точке старта прибавляем единичный вектор направления умноженный на какое то число, которое задаст длинну
	// вектора

	return true;

}


// Через HitResult выходим на актора и вызвываем у него TakeDamage
void  ASTURifleWeapon::MakeDamage(FHitResult& HitResult)
{
	// получаем указатель на актора в которого попал LineTrace
	const auto DamageActor = HitResult.GetActor();

	if (!DamageActor) return;

	DamageActor->TakeDamage(DamageAmount, FDamageEvent(), GetPlayerController(), this);

	// DamageAmount          - количество Damage
	// FDamageEvent()        - тип Damage
	// GetPlayerController() - указатель на контроллер который нанес урон
	// this                  - указатель на актор который нанес урон, текущее оружие this
}