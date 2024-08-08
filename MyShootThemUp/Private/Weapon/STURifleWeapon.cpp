// My Shoot Them Up Game , All Rights Reserved
// В STURifleWeapon.cpp


#include "Weapon/STURifleWeapon.h"
#include "Engine/World.h"                        // 
#include "DrawDebugHelpers.h"                    // дли рисования линий (Line Trace)
#include "Weapon/Components/STUWeaponFXComponent.h"
#include "NiagaraSystem.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"


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
	// эффект niagara
	InitMuzzleFX();

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
	// выключаем видимость эффекта niagara
	SetMuzzleFXVisibility(false);

	// UE_LOG(LogBaseWeapon, Warning, TEXT(" StopFire!!! "));

	// остановка таймера
	GetWorldTimerManager().ClearTimer(ShotTimerHandle);
}

// функция содержит всю логику выстрела
void ASTURifleWeapon::MakeShot()
{
	//UE_LOG(LogTemp, Warning, TEXT("Make Shot"));

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

	FVector TraceFXEnd = TraceEnd;

	// если пересечение было, попали в какой либо актор
	if (HitResult.bBlockingHit)
	{
		// точку столкновения записываем в TraceFXEnd 
		TraceFXEnd = HitResult.ImpactPoint;
		
		
		// функция нанесения урона актору
		MakeDamage(HitResult);

		WeaponFXComponent->PlayImpactFX(HitResult);
		// вызываем функцию проигрвания FX, передаем Hit объект (информацию об столкновении)
	}

	// спавн трасера от дула до точки столкновения
	SpawnTraceFX(GetMuzzleWorldLocation(), TraceFXEnd);

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

	DamageActor->TakeDamage(DamageAmount, FDamageEvent(), GetController(), this);

	// DamageAmount          - количество Damage
	// FDamageEvent()        - тип Damage
	// GetPlayerController() - указатель на контроллер который нанес урон
	// this                  - указатель на актор который нанес урон, текущее оружие this
}


// спавнит niagara system
void ASTURifleWeapon::InitMuzzleFX()
{
	// если эффекта нет, спавним его. спавнится 1 раз, затем только меняем видимость
	if (!MuzzleFXComponent)
	{
		MuzzleFXComponent = SpawnMuzzleFX();
	}

	// включаем видимость
	SetMuzzleFXVisibility(true);
}

// устанавливает видимость эффекта
void ASTURifleWeapon::SetMuzzleFXVisibility(bool Visibility)
{
	// проверка что эффект есть
	if (MuzzleFXComponent)
	{
		// приостанавливает анимацию niagara
		MuzzleFXComponent->SetPaused(!Visibility);

		// включить/ выключить видимость эффекта
		MuzzleFXComponent->SetVisibility(Visibility, true);
		// Visibility - булевая, видимость у текущего компонента
		// false      - видимость у наследников
	}
}

// спавн эффекта трассировки
void ASTURifleWeapon::SpawnTraceFX(const FVector& TraceStart, const FVector& TraceEnd)
{
	// спавним эффект в точке дула
	const auto TraceFXComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), TraceFX, TraceStart);
	// GetWorld() - указатель на мир
	// TraceFX    - указатель на UNiagaraSystem
	// TraceStart - координаты спавна в мире

	if (TraceFXComponent)
	{
		// передаем Vector3 в эффект niagara (конечную точку спавна)
		TraceFXComponent->SetNiagaraVariableVec3(TraceTargetName, TraceEnd);
		// TraceTargetName - имя переменной
		// TraceEnd        - значение переменной

		// функция для передачи в niagara различных переменных
		// SetNiagaraVariableActor
		// SetNiagaraVariableBool
		// SetNiagaraVariableFloat
		// SetNiagaraVariableInt
		// SetNiagaraVariablerColor
		// SetNiagaraVariableVec2
		// SetNiagaraVariableVec3

	}

}


// получаем текущий контроллер (для статистики)
AController* ASTURifleWeapon::GetController() const
{
	// получаем Pawn из GetOwner
	const auto Pawn = Cast<APawn>(GetOwner());

	// получаем контроллер из Pawna
	return Pawn ? Pawn->GetController() : nullptr;
}

