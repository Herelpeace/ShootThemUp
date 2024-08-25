// My Shoot Them Up Game , All Rights Reserved
// В STUPlayerCharacter.cpp


#include "Player/STUPlayerCharacter.h"
#include "Camera/CameraComponent.h"                   // добавляем заголовочный файл камеры
#include "Components/InputComponent.h"                
#include "GameFramework/SpringArmComponent.h"         // компонент вращения
#include "Components/STUWeaponComponent.h"            // наш класс работы с оружием
#include "Components/SphereComponent.h"               // компонент сферы
#include "Components/CapsuleComponent.h"              // компонент капсулы

// Sets default values
ASTUPlayerCharacter::ASTUPlayerCharacter (const FObjectInitializer& ObjInit): Super(ObjInit)

	// Меняем дефолтный MovementComponent на наш  STUMovementComponent (можно менять у Mesh и у Капсулы)
	// ASTUBaseCharacter ( const FObjectInitializer& ObjInit) - конструктор с параметром в котором передается объект инициализации
	// Super ()                                                                                     - конструктор родительского класса
	// ObjInit                                                                                       - объект инициализации
	// SetDefaultSubobjectClass < объект_который_будет_установлен > (объект_который_будет_заменен)
	// ACharacter::CharacterMovementComponentName                                                    - имя объекта в статической переменной базового класса ( MovementComponent)
	// (const FObjectInitializer& ObjInit) : Super(ObjInit.SetDefaultSubobjectClass<USTUCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
	//
	// Super вернет новый установленный объект который попадет в const FObjectInitializer& ObjInit
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");    // вращение вокруг персонажа, создаем объект (штатив на котором находится камера)

	// у SpringArmComponent в разделе Camera в разделе SocketOffset содержится положение
	// камеры (Transform)
	// данной настройкой мы смещаем камеру 0 - по Х, 100 - по Y, 80 по Z
	SpringArmComponent->SocketOffset = FVector(200.0f, 800.0f, 800.0f);
	SpringArmComponent->SetupAttachment(GetRootComponent());                                   // закрепляем к корневому компоненту
	SpringArmComponent->bUsePawnControlRotation = true;                                        // разрешает вращение мышкой, можно изменить в BP


	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");   // создаем камеру
	CameraComponent->SetupAttachment(SpringArmComponent);                            // родительским указыаем SpringArmComponent

	CameraCollisionComponent = CreateDefaultSubobject<USphereComponent>("CameraCollisionComponent");	// создаем SphereComponent
	CameraCollisionComponent->SetupAttachment(CameraComponent);                                         // присоединяем к компоненту камеры 
	CameraCollisionComponent->SetSphereRadius(10.0f);                                                   // устанавливаем радиус сферы
	CameraCollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);       // реакция коллизии на все каналы (Overlap - при пересечении с другой коллизией)

}

void ASTUPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(CameraCollisionComponent);

	CameraCollisionComponent->OnComponentBeginOverlap.AddDynamic(this,&ASTUPlayerCharacter::OnCameraCollisionBeginOverlap);
	CameraCollisionComponent->OnComponentEndOverlap.AddDynamic(this, &ASTUPlayerCharacter::OnCameraCollisionEndOverlap);


}


// Called to bind functionality to input
void ASTUPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASTUPlayerCharacter::MoveForward);  // бинд клавиши движение вперед/назад
	PlayerInputComponent->BindAxis("MoveRight", this, &ASTUPlayerCharacter::MoveRight);      // бинд клавиши движение вплево/вправо

	PlayerInputComponent->BindAxis("LookUp", this, &ASTUPlayerCharacter::AddControllerPitchInput); // бинд мышки вверх/вниз
	PlayerInputComponent->BindAxis("TurnAround", this, &ASTUPlayerCharacter::AddControllerYawInput); // бинд мышки вокруг персонажа

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASTUPlayerCharacter::Jump);           // прыжок
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ASTUPlayerCharacter::OnStartRunning);  // зажали shift
	PlayerInputComponent->BindAction("Run", IE_Released, this, &ASTUPlayerCharacter::OnStopRunning);  // отпустили shift

	// Jump       - название биндинга
	// IE_Pressed - состояние контрола, когда будет вызван CallBack
	// this       - объект к которому применяем
	// &ASTUBaseCharacter::Jump - функция которая будет вызвана при нажатии клавиши (уже реализована в классе Pawn)

	PlayerInputComponent->BindAction("Fire", IE_Pressed, WeaponComponent, &USTUWeaponComponent::StartFire); // бинд функций стрельбы мышкой
	PlayerInputComponent->BindAction("Fire", IE_Released, WeaponComponent, &USTUWeaponComponent::StopFire);
	PlayerInputComponent->BindAction("NextWeapon", IE_Released, WeaponComponent, &USTUWeaponComponent::NextWeapon); // смена оружия
	PlayerInputComponent->BindAction("Reload", IE_Pressed, WeaponComponent, &USTUWeaponComponent::Reload); // перезарядка
}


// MoveForward(float Amount) движение вперед/назад
void ASTUPlayerCharacter::MoveForward(float Amount)
{
	if (Amount == 0.0f) return;
	IsMovingForward = Amount > 0.0f; // если >0 значит нажата клавиша движения вперед
	AddMovementInput(GetActorForwardVector(), Amount);

	// GetActorForwardVector() - вектор, направление в котором движимся
	// Amount                  - скорость движения. домножается на вектор
}
// MoveForward(float Amount) 

// MoveRight(float Amount)  движение влево/вправо
void ASTUPlayerCharacter::MoveRight(float Amount)
{
	if (Amount == 0.0f)   return;
	AddMovementInput(GetActorRightVector(), Amount);
}
// MoveRight(float Amount) 

// вызывается при нажатии Left Shift
void ASTUPlayerCharacter::OnStartRunning()
{
	WantsToRun = true;
}
//OnStartRunning() 

// когда отпустли Left Shift
void ASTUPlayerCharacter::OnStopRunning()
{
	WantsToRun = false;
}
// OnStopRunning() 

// возвращает true когда персонаж использует ускоренный бег
bool ASTUPlayerCharacter::IsRunning() const
{
	return WantsToRun && IsMovingForward && !GetVelocity().IsZero();

	//WantsToRun             - нажат shift
	//IsMovingForward        - нажата клавиша вперед
	//GetVelocity().IsZero() - вектор скорости персонажа не равен 0, он действительно двигается
}
// IsRunning()

// функция вызываемая делегатом, когда здоровье равно 0
void ASTUPlayerCharacter::OnDeath()
{
	Super::OnDeath();

	if (Controller)  // проверка на null
	{
		// фцнкция для смены Pawna
		Controller->ChangeState(NAME_Spectating);
	}
}
// OnDeath()

	// функция для бинда на делегат BeginOverlap
void ASTUPlayerCharacter::OnCameraCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Проверяем пересекаются ли коллизии сферы и капсулы
	CheckCameraOverlap();
}

// функция для бинда на делегат EndOverlap
void ASTUPlayerCharacter::OnCameraCollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// Проверяем пересекаются ли коллизии сферы и капсулы
	CheckCameraOverlap();
}


// Проверяем пересекаются ли коллизии сферы и капсулы
void ASTUPlayerCharacter::CheckCameraOverlap()
{
	// проверяем есть ли пересечение с компонентом капсулы, функция IsOverlappingComponent(name_Component)
	const auto HideMesh = CameraCollisionComponent->IsOverlappingComponent(GetCapsuleComponent());

	// делаем меш пероснажа невидимым
	GetMesh()->SetOwnerNoSee(HideMesh);

	// объявляем массив указателей на компоненты сцены, в данном случае нам нужен меш
	TArray<USceneComponent*> MeshChildren;

	// получаем все дочерние компоненты мэша (мэш оружия и т.д.)
	GetMesh()->GetChildrenComponents(true, MeshChildren);
	// true         - вернет потомков со всех уровней, false - только первого уровня 
	// MeshChildren - массив по ссылке, в него передадутся указатели на все дочерние компоненты 

	for (auto MeshChild : MeshChildren)
	{
		// MeshChildren - это USceneComponent у него нельзя отключить видимость
		// поэтому кастим его до UPrimitiveComponent, у которого уже можно отключать видимость  
		// перейдя по функции SetOwnerNoSee увидим что она вызывается у UPrimitiveComponent, 
		// а перейдя по UPrimitiveComponent увидим что он наследуются от USceneComponent

		const auto MeshChildGeometry = Cast<UPrimitiveComponent>(MeshChild);
		if (MeshChildGeometry)
		{
			MeshChildGeometry->SetOwnerNoSee(HideMesh);
		}
	}
}
















