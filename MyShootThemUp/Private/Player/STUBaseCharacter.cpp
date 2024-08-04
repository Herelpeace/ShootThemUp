// My Shoot Them Up Game , All Rights Reserved
// В STUBaseCharacter.cpp


#include "Player/STUBaseCharacter.h"
#include "Camera/CameraComponent.h"                   // добавляем заголовочный файл камеры
#include "GameFramework/SpringArmComponent.h"         // компонент вращения
#include "Components/STUCharacterMovementComponent.h" // добавляем наш созданный STUCharacterMovementComponent
#include "Components/STUHealthActorComponent.h"       // подключили наш компонент здоровья
#include "Components/TextRenderComponent.h"           // отоброжение текста на экране, для здоровья
#include "Components/STUWeaponComponent.h"            // наш класс работы с оружием
#include "Components/CapsuleComponent.h"              // для работы с коллизией капсулы

#include "GameFramework/Controller.h"                 // заголовочный файл контроллера, для переключения между Pawnaми




DEFINE_LOG_CATEGORY_STATIC(LogBaseCharacter, All, All);

// Sets default values
ASTUBaseCharacter::ASTUBaseCharacter(const FObjectInitializer& ObjInit)
    : Super(ObjInit.SetDefaultSubobjectClass<USTUCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))

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
	CameraComponent->SetupAttachment(SpringArmComponent); // родительским указыаем SpringArmComponent

	HealthComponent = CreateDefaultSubobject<USTUHealthActorComponent>("HealthComponent");   // создали объект в редакторе
	                                                                                         // объект ни к чему не привязываем, он логический будет висеть в воздухе

	HealthTextComponent = CreateDefaultSubobject<UTextRenderComponent>("HealthTextComponent"); // создаем объект в редакторе, отображает здоровье
	HealthTextComponent->SetupAttachment(GetRootComponent());                                  // закрепляем к корневому компоненту
	HealthTextComponent->SetOwnerNoSee(true);                                                  // не отрисоываем данный компонет над персонажем когда мы им управляем

	WeaponComponent = CreateDefaultSubobject<USTUWeaponComponent>("WeaponComponent");   // создаем раздел в котором выбираем наши классы оружия
                                                                                 
} 

// Called when the game starts or when spawned
void ASTUBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	check(HealthComponent) // проверка что объекты созданы и существуют
	check(HealthTextComponent) // макросы работают только во время отладки, в shipinge они игнорируются
	check(GetCharacterMovement()) // проверка что CharacterMovement не null
	check(WeaponComponent)
	check(GetMesh());

    // т.к сначала вызвается BeginPlay у компонентов, а затем у Character,нам нужно отобразить здоровье заранее до делегата
	OnHealthChanged(HealthComponent->GetHealth(), 0.0f);

	// биндим делегат на функцию
	// т.к делегат используется только в С++ ипользуем AddUObject
	HealthComponent->onDeath.AddUObject(this, &ASTUBaseCharacter::OnDeath);

	// биндим делегат на функцию, функция вызывается когда сработает длегат
	HealthComponent->OnHealthChanged.AddUObject(this, &ASTUBaseCharacter::OnHealthChanged);

	// this                       - указатель на объект Charactera
	// ASTUBaseCharacter::OnDeath - вызываемая функция	

	// подписываемся на делегат и биндим функцию которую будем вызывать при падении с высоты
	LandedDelegate.AddDynamic(this, &ASTUBaseCharacter::OnGroundLanded);

}


// выводим значение здоровья на экран в виде цифр
void ASTUBaseCharacter::OnHealthChanged(float Health, float HealthDelta)
{
	HealthTextComponent->SetText(FText::FromString(FString::Printf(TEXT(" %.0f"), Health))); // выводим значение здоровья на экран в виде цифр
}



// Called every frame
void ASTUBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const auto Health = HealthComponent->GetHealth();                      // создали переменную с авто типом данных, в которую получаем текущее значение здоровья
	//HealthTextComponent->SetText(FText::FromString(FString::Printf(TEXT(" %.0f"), Health)));           // выводим значение здоровья на экран в виде цифр
}


// Called to bind functionality to input
void ASTUBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASTUBaseCharacter::MoveForward);  // бинд клавиши движение вперед/назад
	PlayerInputComponent->BindAxis("MoveRight", this, &ASTUBaseCharacter::MoveRight);      // бинд клавиши движение вплево/вправо

	PlayerInputComponent->BindAxis("LookUp", this, &ASTUBaseCharacter::AddControllerPitchInput); // бинд мышки вверх/вниз
	PlayerInputComponent->BindAxis("TurnAround", this, &ASTUBaseCharacter::AddControllerYawInput); // бинд мышки вокруг персонажа

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASTUBaseCharacter::Jump);           // прыжок
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ASTUBaseCharacter::OnStartRunning);  // зажали shift
	PlayerInputComponent->BindAction("Run", IE_Released, this, &ASTUBaseCharacter::OnStopRunning);  // отпустили shift

	// Jump       - название биндинга
	// IE_Pressed - состояние контрола, когда будет вызван CallBack
	// this       - объект к которому применяем
	// &ASTUBaseCharacter::Jump - функция которая будет вызвана при нажатии клавиши (уже реализована в классе Pawn)

	PlayerInputComponent->BindAction("Fire",IE_Pressed,WeaponComponent, &USTUWeaponComponent::StartFire); // бинд функций стрельбы мышкой
	PlayerInputComponent->BindAction("Fire",IE_Released,WeaponComponent, &USTUWeaponComponent::StopFire);
	PlayerInputComponent->BindAction("NextWeapon", IE_Released, WeaponComponent, &USTUWeaponComponent::NextWeapon); // смена оружия
	PlayerInputComponent->BindAction("Reload",IE_Pressed,WeaponComponent, &USTUWeaponComponent::Reload); // перезарядка
}


// MoveForward(float Amount) движение вперед/назад
void ASTUBaseCharacter::MoveForward(float Amount) 
{
	if (Amount == 0.0f) return;
	IsMovingForward = Amount > 0.0f; // если >0 значит нажата клавиша движения вперед
	AddMovementInput(GetActorForwardVector(), Amount);

	// GetActorForwardVector() - вектор, направление в котором движимся
	// Amount                  - скорость движения. домножается на вектор
}
// MoveForward(float Amount) 

// MoveRight(float Amount)  движение влево/вправо
void ASTUBaseCharacter::MoveRight(float Amount) 
{
	if (Amount == 0.0f)   return;
	AddMovementInput(GetActorRightVector(), Amount);
}
// MoveRight(float Amount) 

// вызывается при нажатии Left Shift
void ASTUBaseCharacter::OnStartRunning() 
{
	WantsToRun = true;
}
//OnStartRunning() 

// когда отпустли Left Shift
void ASTUBaseCharacter::OnStopRunning() 
{
	WantsToRun = false;
}
// OnStopRunning() 

// возвращает true когда персонаж использует ускоренный бег
bool ASTUBaseCharacter::IsRunning() const
{
	return WantsToRun&& IsMovingForward && !GetVelocity().IsZero();

	//WantsToRun             - нажат shift
	//IsMovingForward        - нажата клавиша вперед
	//GetVelocity().IsZero() - вектор скорости персонажа не равен 0, он действительно двигается
}
// IsRunning()

// поворот персонажа в градусах
float ASTUBaseCharacter::GetMovementDirection() const
{
	// получаем косинус угла между векторами направления и скорости
	// при помощи ArcCos переводим угол в градусы, угол не будет иметь знака, а так же когда скорость =0, угол будет равен 90
	// CrossProduct - векторное произведение двух векторов, будет давать нам 3 вектор со знаком, этот вектор нужно сделать единичным (чтобы давал 1, 0,-1)
	 if (GetVelocity().IsZero()) return 0.0f;                                                               // если объект не двигается, выходим не считаем вектора
	                                                                                                        // анимация назад воспроизводится не будет так как вектора Forward и Velocity
	                                                                                                        // будут противоположны друг другу

	const auto VelocityNormal = GetVelocity().GetSafeNormal();                                              // получаем нормализованный вектор скорости
	const auto AngleBetween   = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityNormal));  // получаем угол в градусах между векторами направления и скорости
	const auto CrossProduct   = FVector::CrossProduct(GetActorForwardVector(),VelocityNormal);              // (векторное произведение) получаем третий вектор который будет определять знак угла
	const auto Degrees        = FMath::RadiansToDegrees(AngleBetween);        // записываем полученное значение градусов


	// auto            - автоматическое вычисление типа
	// GetVelocity()   - получить вектор скорости
	// GetSafeNormal() - получить нормированный вектор (нормаль)

	// DotProduct ()   - косинус угла между векторами ( вектор направления и вектор скорости)
	// Acos()          - ArcCos, преобразует косинус в радианы (в градусы нужно переводить)
	// CrossProduct    - векторное произведение двух векторов, будет давать нам 3 вектор со знаком,в зависимости от направления 2-x векторов
	//                   когда бежим вправо то Cross Product.Z направлен вверх и имеет положительное значение
	//                   в обратную сторону - отрицвтельное

	//return FMath::RadiansToDegrees(AngleBetween) *FMath::Sign(CrossProduct.Z); // угол умножаем на знак и получаем угол со знаком
	return CrossProduct.IsZero()? Degrees: Degrees * FMath::Sign(CrossProduct.Z); // угол умножаем на знак и получаем угол со знаком
	                                                                              
	// если CrossProduct.IsZero() = 0, значит мы бежим назад, просто возвращаем градуы, в простивном случа возращаем градусы со знаком
	// FMath::Sign(CrossProduct.Z)            - возвращает знак числа (положительное:1, отрицательное:-1, ноль:0)
	// FMath::RadiansToDegrees(AngleBetween)  - первод угла из радианов в градусы
}
// GetMovementDirection() const

// функция вызываемая делегатом, когда здоровье равно 0
void ASTUBaseCharacter::OnDeath() 
{
	UE_LOG(LogBaseCharacter, Display, TEXT(" Player %s is dead!!!"), *GetName());

	//PlayAnimMontage(DeathAnimMontage);   // фунция для проигрывания AnimMontage
	// DeathAnimMontage - указатель на анимацию которую нужно проиграть. Можно не проверять на null, проверка есть внутри Unreal

	// остановить движение персонажа
	GetCharacterMovement()->DisableMovement();

	// GetCharacterMovement() - указатель на CharacterMovement
	// DisableMovement()      - остановить движение 

	// уничтожение персонажа через 5 секунд
	SetLifeSpan(LifeSpanDeth);  

	if (Controller)  // проверка на null
	{
		// фцнкция для смены Pawna
	    Controller->ChangeState(NAME_Spectating);
	}

	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	// GetCapsuleComponent()            - получаем указатель на CapsuleComponent
	// SetCollisionResponseToAllChannels - устанавливает параметры коллизии одинаково для всех каналов
	// ECollisionResponse                - enum содержащий основные параметры коллизий ECR_Ignore, ECR_Overlap, ECR_Block

	WeaponComponent->StopFire();

	// получаем указатель на мэш, включаем коллизию
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	// включить физическую симуляцию тела
	GetMesh()->SetSimulatePhysics(true);
}
// OnDeath()

// функция вызваемая делегатом при падении с высоты
void ASTUBaseCharacter::OnGroundLanded(const FHitResult& Hit) 
{
	// получем скорость charactera по координате Z (падение с высоты, скорость прямопропорциональна высоте)
	// перед функцией стоит "-" чтобы отрицательное значение перевести в положительное

	const auto FallVelocityZ = -GetVelocity().Z;

	UE_LOG(LogBaseCharacter, Warning, TEXT("Velocity Z On Landed: %f "), FallVelocityZ);

	// если скорость меньше указаного в диапазоне LandedDamageVelocity то ничего не делаем
	if (FallVelocityZ < LandedDamageVelocity.X) return;

	// вычисляем Damage в зависимости от значения скорости
	const auto FinalDamage = FMath::GetMappedRangeValueClamped(LandedDamageVelocity, LandedDamage, FallVelocityZ);
	
	// LandedDamageVelocity - входной диапазон
	// LandedDamage         - выходной диапазон
	// FallVelocityZ        - значение по которому будет высчитываться выходной диапазон
	// каждому значению из входного диапазона будет соотвествовать какое то значение из выходного диапазона
	// передав значение для расчета, функция найдет его во входном диапазоне и выдаст число из выходного диапазона

	UE_LOG(LogBaseCharacter, Warning, TEXT(" FinalDamage: %f "), FinalDamage);

    // наносим урон
	TakeDamage(FinalDamage, FDamageEvent(), nullptr, nullptr);

	// FinalDamage    - значение Damage
	// FDamageEvent() - тип урона, передаем пустой тип
	// nullptr        - контроллер 
	// nullptr        - указатель на оActor
	// последние 2 параметра nullptr потому что урон относится к урону окружающей среды,а не Actora 

}
// OnGroundLanded(const FHitResult& Hit) 


// устанавливаем цвет, новая функция из Charactera 
void ASTUBaseCharacter::SetPlayerColor(const FLinearColor& Color)
{
	// делаем материал на мэше динамическим 
	const auto MaterialInst = GetMesh()->CreateAndSetMaterialInstanceDynamic(0);

	if (!MaterialInst) return;

	// передаем имя параметра и его векторное значение, для установки в качестве новых значений 
	MaterialInst->SetVectorParameterValue(MaterialColorName, Color);




}











