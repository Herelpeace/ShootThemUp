// My Shoot Them Up Game , All Rights Reserved
// В STUBaseWeapon.cpp


#include "Weapon/STUBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"    // для добавления Mesh
#include "Engine/World.h"                        // 
#include "DrawDebugHelpers.h"                    // дли рисования линий (Line Trace)
#include "GameFramework/Character.h"             // класс Charactera
#include "GameFramework/Controller.h"            // класс Controllera чтобы через него получить доступ к камере


DEFINE_LOG_CATEGORY_STATIC(LogBaseWeapon, All, All);


ASTUBaseWeapon::ASTUBaseWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	SetRootComponent(WeaponMesh);    // делаем компонет корневым
}


void ASTUBaseWeapon::BeginPlay()
{
	Super::BeginPlay();	

	check(WeaponMesh);  // проверяем Mash оружия, если его нет, то ничего не отрисовываем

	// текущее количиство аммуниции равно дефолтноиу количеству
	CurrentAmmo = DefaultAmmo;
}

// функция бинда кнопки мышки, вызывается из Charactera до тех пор пока кнопка мышки не отпущена
// начало стрельбы
void ASTUBaseWeapon::StartFire() 
{

}


// функция бинда кнопки мышки, вызывается из Charactera, вызывается после того как отпустили кнопку мышки
// конец стрельбы
void ASTUBaseWeapon::StopFire()
{

}



// функция содержит всю логику выстрела
void ASTUBaseWeapon::MakeShot() 
{

}
// MakeShot() 


// функця возвращает указатель на контроллер текущего актора
APlayerController* ASTUBaseWeapon::GetPlayerController() const
{
	const auto Player = Cast<ACharacter>(GetOwner());
	// получаем указатель на владельца компонента STUBaseWeapon, приводим его к типу ACharacter, записываем в
	// переменную

	if (!Player) return nullptr;

	return Player->GetController<APlayerController>();
	// из указателя на владельца получаем указатель на Controller
}

// получаем Координаты и вращение камеры
bool ASTUBaseWeapon::GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const
{
	const auto Controller = GetPlayerController();

	if (!Controller)  return false;

	//FVector ViewLocation;  // для сохранения координат
	//FRotator ViewRotation; // для сохранения вращения

	Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);
	// заполняем переменные ViewLocation, ViewRotation данными
	// из указателя на Controller получаем позицию камеры
	// указатель на камеру Charactera ViewLocation - коорддинаты камеры, ViewRotation- вращение камеры
	return true;
}


// функция возвращает положение сокета
FVector ASTUBaseWeapon::GetMuzzleWorldLocation() const
{
	return WeaponMesh->GetSocketLocation(MuzzleSocketName);
}

// заполняем начальные и конечные координаты для рисуемой линии
bool ASTUBaseWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
	FVector ViewLocation;  // для сохранения координат
	FRotator ViewRotation; // для сохранения вращения

	if(!GetPlayerViewPoint(ViewLocation, ViewRotation)) return false;


	// получем трансфорамцию сокета
	// const FTransform SocketTransform = WeaponMesh->GetSocketTransform(MuzzleSocketName);

	// GetSocketTransform - получает Transform сокета, принимает 2 параметра
	// MuzzleSocketName   - имя сокета
	// TypeCoordinate     - тип координат в которой хотим получить сокет. Параметр
	// не указан значит получаем координаты в мировой системе координат

	// точка начала выстрела, записываем в нее положение сокета
	// точка начала выстрела, записываем в нее положение камеры
	TraceStart = ViewLocation; // SocketTransform.GetLocation();


	// вектор направления выстрела (единичный)
	const FVector ShootDirection = ViewRotation.Vector();  //FMath::VRandCone( ViewRotation.Vector(), HalfRad);

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


// получаем данные о пересечении (столкновении)
void ASTUBaseWeapon::MakeHit( FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd) 
{
	if (!GetWorld()) return;

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetOwner()); // заполняем поле AddIgnoredActor()

	// FCollisionQueryParams - структура в которой можно указать игнорируемые компоненты или акторы
	// AddIgnoredActor()     - актор которого нужно игнорировать, нужно чтобы игрок не попадал сам в себя при стрельбе


	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, CollisionParams);

	// LineTraceSingleByChannel()		 - вернет информацию о пересечении с
	// первым объектом
	// HitResult
	// - структура которая содержит информацию о пересечении TraceStart
	// - координаты начала линии TraceEnd
	// - координаты конца линии ECollisionChannel::ECC_Visibility - отфильтровывает объекты на сцене, работает только
	// с объектами которые блокируют данный канал
	//                                     остальные объекты будут игнорироваться
	// функция так же возвращает true если пересечение было или false если небыло
	// CollisionParams                   - игнорируемые акторы. (передаем текущий актор, не будем попадать сами в
	// себя)
}

// уменьшает количество патронов, вызывается после каждого выстрела
void ASTUBaseWeapon::DecreaseAmmo()
{
	CurrentAmmo.Bullets--;
	
	LogAmmo();

	// меняем магазин если количество патронов в магазине равно 0 и количество патронов в арсенале не равно 0
	if (IsClipEmpty() && !IsAmmoEmpty())
	{
		// меняем магазин
		ChangeClip();
	}

}

// true когда арсенал не бесконечный, полностью пустой, количество магазинов и патронов = 0
bool ASTUBaseWeapon::IsAmmoEmpty() const
{
	return !CurrentAmmo.Infinite && CurrentAmmo.Clips == 0 && IsClipEmpty();

}

// true когда текущий магазин пустой
bool ASTUBaseWeapon::IsClipEmpty() const
{
	return CurrentAmmo.Bullets == 0;

}

// меняет магазин на новый
void ASTUBaseWeapon::ChangeClip()
{
	CurrentAmmo.Bullets = DefaultAmmo.Bullets;

	// если количество магазинов не бесконечное
	if (!CurrentAmmo.Infinite)
	{
		CurrentAmmo.Clips--;
	}

	UE_LOG(LogBaseWeapon, Warning, TEXT("------Change Clip ------"));

}

// выводит состояние аммуниции в консоль
void ASTUBaseWeapon::LogAmmo()
{
	FString AmmoInfo = "Ammo: " + FString::FromInt(CurrentAmmo.Bullets) + " / ";
	AmmoInfo += " Magazine: ";
	AmmoInfo += CurrentAmmo.Infinite ? "Infinite" : FString::FromInt(CurrentAmmo.Clips);

	UE_LOG(LogBaseWeapon, Warning, TEXT("%s"),*AmmoInfo);

}

