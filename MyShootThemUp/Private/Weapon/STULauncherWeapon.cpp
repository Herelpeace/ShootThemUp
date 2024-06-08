// My Shoot Them Up Game , All Rights Reserved
// В STULauncherWeapon.cpp


#include "Weapon/STULauncherWeapon.h"
#include "Weapon/STUProjectile.h"

void ASTULauncherWeapon::StartFire()
{
	// функция с логикой стрельбы
	MakeShot(); 

}

void ASTULauncherWeapon::MakeShot()
{
	// проверка мира на null, аммуниция пуста IsAmmoEmpty() = true
	if (!GetWorld()||IsAmmoEmpty()) return;

	FVector TraceStart, TraceEnd;
	// начальная и конечная точки выстрела

	if (!GetTraceData(TraceStart, TraceEnd)) return;

	FHitResult HitResult;
	// структура в которую сохраняем информацию о пересечении LineTrace с объектами
	// структура FHitResult содержит поля: время пересечения, точка пересечения, нормаль, указатель на актор с которым
	// пересеклись и т.д. так же FHitResult содержит информацию было пересечение или нет, переменная bBlockingHit

	// заполняем структуру HitResult
	MakeHit(HitResult, TraceStart, TraceEnd);

	// определяем координаты конечной точки в которой должна оказаться ракетв
	const FVector EndPoint = HitResult.bBlockingHit ? HitResult.ImpactPoint : TraceEnd;
	// если пересечение было то EndPoint = координаты точки пересечения, иначе координаты TraceEnd
	// bBlockingHit - поле структуры HitResult, принимает true если было пересечение вектора с каким либо объектом
	// ImpactPoint  - поле структуры HitResult, возвращает координаты точки пересечения объектов

	// определяем вектор напрвления, для этого из конечной точки вычитаем начальную
	const FVector Direction = (EndPoint - GetMuzzleWorldLocation()).GetSafeNormal();
    // нам нужно только нарправление, поэтому сделаем вектор единичным при помощи функции GetSafeNormal()


	// задаем первоначальный трансформ ракеты, в переменную SpawnTransform 
	const FTransform SpawnTransform(FRotator::ZeroRotator, GetMuzzleWorldLocation());
	// FRotator::ZeroRotator    - вращение, нулевое
	// GetMuzzleWorldLocation() - функция в базовом классе,возвращает FVector координаты положения MuzzleSocket
	//                            т.е. координаты спавна ракеты совпадают с координами MuzzleSocket

	// спавн ракеты через GetWorld, вернет указатель на класс соспавненного объекта
	ASTUProjectile* Projectile = GetWorld()->SpawnActorDeferred<ASTUProjectile>(ProjectileClass, SpawnTransform);
	// TSubclassOf<ASTUProjectile> ProjectileClass - класс ракеты который будем спавнить при выстреле Launchera
	if (Projectile)
	{
		// передаем вектор направления (Direction), соспавненному актору ракеты
		Projectile->SetShootDirection(Direction);
		// по сути мы создали объект класса ASTUProjectile и записали его в переменную
		// далее через эту переменную обращаемся к методам класса в поле public, передаем туда данные
		// таким же способом мы можем передавать параметры Damage или любые другие в класс Projectile
		// создаем переменную класса и через неё обращаемся к public методам класса

		Projectile->SetOwner(GetOwner());
		// присваиваем владельца Projectilу текущего Charactera т.к. оружие будет уустановлено у Charactera


		// заершаем спавн
		Projectile->FinishSpawning(SpawnTransform);
	}

	// уменьшаем количество патронов
	DecreaseAmmo();


}
