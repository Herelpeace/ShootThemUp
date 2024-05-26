// My Shoot Them Up Game , All Rights Reserved
// STUDevDamageActor.cpp

#include "Dev/STUDevDamageActor.h"
#include "DrawDebugHelpers.h"            // подключаем графические примитивы
#include "Kismet/GameplayStatics.h"      // для нанесения урона (для получения доступа к актору)

// Sets default values
ASTUDevDamageActor::ASTUDevDamageActor()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    // создаем SceneComponent в редакторе
    SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
    SetRootComponent(SceneComponent); // устанавливаем его главным, в него будем вкладывать остальные классы
}

// Called when the game starts or when spawned
void ASTUDevDamageActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASTUDevDamageActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    
    DrawDebugSphere(GetWorld(), GetActorLocation(),Radius, 24,SphereColor );
    
    // GetWorld()         - указатель на мир
    // GetActorLocation() - координаты центра сферы, будем рисовать там где расположен Actor
    // Radius             - радиус сферы 
    // 24                 - количество сегментов сферы
    // SphereColor        - цвет сферы

   // UGameplayStatics::ApplyDamage();         нужно получить доступ к указателю на актор через коллизии
   // UGameplayStatics::ApplyPointDamage();    нужно получить доступ к указателю на актор через коллизии

    UGameplayStatics::ApplyRadialDamage(GetWorld(), Damage, GetActorLocation(), Radius, DamageType, {}, this, nullptr,DoFullDamage); // урон будет наносится всем акторам которые находятся в модельной сфере

    // функция ApplyRadialDamage пробегает по всем переданным в неё акторам и вызывает для них внутри себя функцию TakeDamage(), наносит урон величиной Damage
    // GetWorld()         - указатель на мир
    // Damage             - количество наносимого урона
    // GetActorLocation() - центр сферы урона
    // Radius             - радиус сферы
    // DamageType         - тип Damage, передаем nullptr - без типа
    // {}                 - массив акторов которым не будет наноситься урон, {} - пустой массив, урон наносится всем акторам
    // this               - актор который наносит урон
    // nullptr            - Controller, в данном случае у нас просто MeshComponent, не Pawn и не Character, у него нет контроллера управления
    // DoFullDamage       - true - макcимальный урон на любом удалении от центра, false - чем ближе к центру тем урон больше


}

