// My Shoot Them Up Game , All Rights Reserved
// � STUBaseCharacter.cpp


#include "Player/STUBaseCharacter.h"
#include "Camera/CameraComponent.h"                   // ��������� ������������ ���� ������
#include "GameFramework/SpringArmComponent.h"         // ��������� ��������
#include "Components/STUCharacterMovementComponent.h" // ��������� ��� ��������� STUCharacterMovementComponent
#include "Components/STUHealthActorComponent.h"       // ���������� ��� ��������� ��������
#include "Components/TextRenderComponent.h"           // ����������� ������ �� ������, ��� ��������
#include "Components/STUWeaponComponent.h"            // ��� ����� ������ � �������
#include "Components/CapsuleComponent.h"              // ��� ������ � ��������� �������

#include "GameFramework/Controller.h"                 // ������������ ���� �����������, ��� ������������ ����� Pawna��




DEFINE_LOG_CATEGORY_STATIC(LogBaseCharacter, All, All);

// Sets default values
ASTUBaseCharacter::ASTUBaseCharacter(const FObjectInitializer& ObjInit)
    : Super(ObjInit.SetDefaultSubobjectClass<USTUCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))

	// ������ ��������� MovementComponent �� ���  STUMovementComponent (����� ������ � Mesh � � �������)
	// ASTUBaseCharacter ( const FObjectInitializer& ObjInit) - ����������� � ���������� � ������� ���������� ������ �������������
	// Super ()                                                                                     - ����������� ������������� ������
	// ObjInit                                                                                       - ������ �������������
	// SetDefaultSubobjectClass < ������_�������_�����_���������� > (������_�������_�����_�������)
	// ACharacter::CharacterMovementComponentName                                                    - ��� ������� � ����������� ���������� �������� ������ ( MovementComponent)
	// (const FObjectInitializer& ObjInit) : Super(ObjInit.SetDefaultSubobjectClass<USTUCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
	//
	// Super ������ ����� ������������� ������ ������� ������� � const FObjectInitializer& ObjInit
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");    // �������� ������ ���������, ������� ������ (������ �� ������� ��������� ������)

	// � SpringArmComponent � ������� Camera � ������� SocketOffset ���������� ���������
	// ������ (Transform)
	// ������ ���������� �� ������� ������ 0 - �� �, 100 - �� Y, 80 �� Z
	SpringArmComponent->SocketOffset = FVector(200.0f, 800.0f, 800.0f);   
	SpringArmComponent->SetupAttachment(GetRootComponent());                                   // ���������� � ��������� ����������
	SpringArmComponent->bUsePawnControlRotation = true;                                        // ��������� �������� ������, ����� �������� � BP
                     
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");   // ������� ������
	CameraComponent->SetupAttachment(SpringArmComponent); // ������������ �������� SpringArmComponent

	HealthComponent = CreateDefaultSubobject<USTUHealthActorComponent>("HealthComponent");   // ������� ������ � ���������
	                                                                                         // ������ �� � ���� �� �����������, �� ���������� ����� ������ � �������

	HealthTextComponent = CreateDefaultSubobject<UTextRenderComponent>("HealthTextComponent"); // ������� ������ � ���������, ���������� ��������
	HealthTextComponent->SetupAttachment(GetRootComponent());                                  // ���������� � ��������� ����������
	HealthTextComponent->SetOwnerNoSee(true);                                                  // �� ����������� ������ �������� ��� ���������� ����� �� �� ���������

	WeaponComponent = CreateDefaultSubobject<USTUWeaponComponent>("WeaponComponent");   // ������� ������ � ������� �������� ���� ������ ������
                                                                                 
} 

// Called when the game starts or when spawned
void ASTUBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	check(HealthComponent) // �������� ��� ������� ������� � ����������
	check(HealthTextComponent) // ������� �������� ������ �� ����� �������, � shipinge ��� ������������
	check(GetCharacterMovement()) // �������� ��� CharacterMovement �� null
	check(WeaponComponent)
	check(GetMesh());

    // �.� ������� ��������� BeginPlay � �����������, � ����� � Character,��� ����� ���������� �������� ������� �� ��������
	OnHealthChanged(HealthComponent->GetHealth(), 0.0f);

	// ������ ������� �� �������
	// �.� ������� ������������ ������ � �++ ��������� AddUObject
	HealthComponent->onDeath.AddUObject(this, &ASTUBaseCharacter::OnDeath);

	// ������ ������� �� �������, ������� ���������� ����� ��������� ������
	HealthComponent->OnHealthChanged.AddUObject(this, &ASTUBaseCharacter::OnHealthChanged);

	// this                       - ��������� �� ������ Charactera
	// ASTUBaseCharacter::OnDeath - ���������� �������	

	// ������������� �� ������� � ������ ������� ������� ����� �������� ��� ������� � ������
	LandedDelegate.AddDynamic(this, &ASTUBaseCharacter::OnGroundLanded);

}


// ������� �������� �������� �� ����� � ���� ����
void ASTUBaseCharacter::OnHealthChanged(float Health, float HealthDelta)
{
	HealthTextComponent->SetText(FText::FromString(FString::Printf(TEXT(" %.0f"), Health))); // ������� �������� �������� �� ����� � ���� ����
}



// Called every frame
void ASTUBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const auto Health = HealthComponent->GetHealth();                      // ������� ���������� � ���� ����� ������, � ������� �������� ������� �������� ��������
	//HealthTextComponent->SetText(FText::FromString(FString::Printf(TEXT(" %.0f"), Health)));           // ������� �������� �������� �� ����� � ���� ����
}


// Called to bind functionality to input
void ASTUBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASTUBaseCharacter::MoveForward);  // ���� ������� �������� ������/�����
	PlayerInputComponent->BindAxis("MoveRight", this, &ASTUBaseCharacter::MoveRight);      // ���� ������� �������� ������/������

	PlayerInputComponent->BindAxis("LookUp", this, &ASTUBaseCharacter::AddControllerPitchInput); // ���� ����� �����/����
	PlayerInputComponent->BindAxis("TurnAround", this, &ASTUBaseCharacter::AddControllerYawInput); // ���� ����� ������ ���������

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASTUBaseCharacter::Jump);           // ������
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ASTUBaseCharacter::OnStartRunning);  // ������ shift
	PlayerInputComponent->BindAction("Run", IE_Released, this, &ASTUBaseCharacter::OnStopRunning);  // ��������� shift

	// Jump       - �������� ��������
	// IE_Pressed - ��������� ��������, ����� ����� ������ CallBack
	// this       - ������ � �������� ���������
	// &ASTUBaseCharacter::Jump - ������� ������� ����� ������� ��� ������� ������� (��� ����������� � ������ Pawn)

	PlayerInputComponent->BindAction("Fire",IE_Pressed,WeaponComponent, &USTUWeaponComponent::StartFire); // ���� ������� �������� ������
	PlayerInputComponent->BindAction("Fire",IE_Released,WeaponComponent, &USTUWeaponComponent::StopFire);
	PlayerInputComponent->BindAction("NextWeapon", IE_Released, WeaponComponent, &USTUWeaponComponent::NextWeapon); // ����� ������
	PlayerInputComponent->BindAction("Reload",IE_Pressed,WeaponComponent, &USTUWeaponComponent::Reload); // �����������
}


// MoveForward(float Amount) �������� ������/�����
void ASTUBaseCharacter::MoveForward(float Amount) 
{
	if (Amount == 0.0f) return;
	IsMovingForward = Amount > 0.0f; // ���� >0 ������ ������ ������� �������� ������
	AddMovementInput(GetActorForwardVector(), Amount);

	// GetActorForwardVector() - ������, ����������� � ������� ��������
	// Amount                  - �������� ��������. ����������� �� ������
}
// MoveForward(float Amount) 

// MoveRight(float Amount)  �������� �����/������
void ASTUBaseCharacter::MoveRight(float Amount) 
{
	if (Amount == 0.0f)   return;
	AddMovementInput(GetActorRightVector(), Amount);
}
// MoveRight(float Amount) 

// ���������� ��� ������� Left Shift
void ASTUBaseCharacter::OnStartRunning() 
{
	WantsToRun = true;
}
//OnStartRunning() 

// ����� �������� Left Shift
void ASTUBaseCharacter::OnStopRunning() 
{
	WantsToRun = false;
}
// OnStopRunning() 

// ���������� true ����� �������� ���������� ���������� ���
bool ASTUBaseCharacter::IsRunning() const
{
	return WantsToRun&& IsMovingForward && !GetVelocity().IsZero();

	//WantsToRun             - ����� shift
	//IsMovingForward        - ������ ������� ������
	//GetVelocity().IsZero() - ������ �������� ��������� �� ����� 0, �� ������������� ���������
}
// IsRunning()

// ������� ��������� � ��������
float ASTUBaseCharacter::GetMovementDirection() const
{
	// �������� ������� ���� ����� ��������� ����������� � ��������
	// ��� ������ ArcCos ��������� ���� � �������, ���� �� ����� ����� �����, � ��� �� ����� �������� =0, ���� ����� ����� 90
	// CrossProduct - ��������� ������������ ���� ��������, ����� ������ ��� 3 ������ �� ������, ���� ������ ����� ������� ��������� (����� ����� 1, 0,-1)
	 if (GetVelocity().IsZero()) return 0.0f;                                                               // ���� ������ �� ���������, ������� �� ������� �������
	                                                                                                        // �������� ����� ��������������� �� ����� ��� ��� ������� Forward � Velocity
	                                                                                                        // ����� �������������� ���� �����

	const auto VelocityNormal = GetVelocity().GetSafeNormal();                                              // �������� ��������������� ������ ��������
	const auto AngleBetween   = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityNormal));  // �������� ���� � �������� ����� ��������� ����������� � ��������
	const auto CrossProduct   = FVector::CrossProduct(GetActorForwardVector(),VelocityNormal);              // (��������� ������������) �������� ������ ������ ������� ����� ���������� ���� ����
	const auto Degrees        = FMath::RadiansToDegrees(AngleBetween);        // ���������� ���������� �������� ��������


	// auto            - �������������� ���������� ����
	// GetVelocity()   - �������� ������ ��������
	// GetSafeNormal() - �������� ������������� ������ (�������)

	// DotProduct ()   - ������� ���� ����� ��������� ( ������ ����������� � ������ ��������)
	// Acos()          - ArcCos, ����������� ������� � ������� (� ������� ����� ����������)
	// CrossProduct    - ��������� ������������ ���� ��������, ����� ������ ��� 3 ������ �� ������,� ����������� �� ����������� 2-x ��������
	//                   ����� ����� ������ �� Cross Product.Z ��������� ����� � ����� ������������� ��������
	//                   � �������� ������� - �������������

	//return FMath::RadiansToDegrees(AngleBetween) *FMath::Sign(CrossProduct.Z); // ���� �������� �� ���� � �������� ���� �� ������
	return CrossProduct.IsZero()? Degrees: Degrees * FMath::Sign(CrossProduct.Z); // ���� �������� �� ���� � �������� ���� �� ������
	                                                                              
	// ���� CrossProduct.IsZero() = 0, ������ �� ����� �����, ������ ���������� ������, � ���������� ����� ��������� ������� �� ������
	// FMath::Sign(CrossProduct.Z)            - ���������� ���� ����� (�������������:1, �������������:-1, ����:0)
	// FMath::RadiansToDegrees(AngleBetween)  - ������ ���� �� �������� � �������
}
// GetMovementDirection() const

// ������� ���������� ���������, ����� �������� ����� 0
void ASTUBaseCharacter::OnDeath() 
{
	UE_LOG(LogBaseCharacter, Display, TEXT(" Player %s is dead!!!"), *GetName());

	//PlayAnimMontage(DeathAnimMontage);   // ������ ��� ������������ AnimMontage
	// DeathAnimMontage - ��������� �� �������� ������� ����� ���������. ����� �� ��������� �� null, �������� ���� ������ Unreal

	// ���������� �������� ���������
	GetCharacterMovement()->DisableMovement();

	// GetCharacterMovement() - ��������� �� CharacterMovement
	// DisableMovement()      - ���������� �������� 

	// ����������� ��������� ����� 5 ������
	SetLifeSpan(LifeSpanDeth);  

	if (Controller)  // �������� �� null
	{
		// ������� ��� ����� Pawna
	    Controller->ChangeState(NAME_Spectating);
	}

	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	// GetCapsuleComponent()            - �������� ��������� �� CapsuleComponent
	// SetCollisionResponseToAllChannels - ������������� ��������� �������� ��������� ��� ���� �������
	// ECollisionResponse                - enum ���������� �������� ��������� �������� ECR_Ignore, ECR_Overlap, ECR_Block

	WeaponComponent->StopFire();

	// �������� ��������� �� ���, �������� ��������
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	// �������� ���������� ��������� ����
	GetMesh()->SetSimulatePhysics(true);
}
// OnDeath()

// ������� ��������� ��������� ��� ������� � ������
void ASTUBaseCharacter::OnGroundLanded(const FHitResult& Hit) 
{
	// ������� �������� charactera �� ���������� Z (������� � ������, �������� �������������������� ������)
	// ����� �������� ����� "-" ����� ������������� �������� ��������� � �������������

	const auto FallVelocityZ = -GetVelocity().Z;

	UE_LOG(LogBaseCharacter, Warning, TEXT("Velocity Z On Landed: %f "), FallVelocityZ);

	// ���� �������� ������ ��������� � ��������� LandedDamageVelocity �� ������ �� ������
	if (FallVelocityZ < LandedDamageVelocity.X) return;

	// ��������� Damage � ����������� �� �������� ��������
	const auto FinalDamage = FMath::GetMappedRangeValueClamped(LandedDamageVelocity, LandedDamage, FallVelocityZ);
	
	// LandedDamageVelocity - ������� ��������
	// LandedDamage         - �������� ��������
	// FallVelocityZ        - �������� �� �������� ����� ������������� �������� ��������
	// ������� �������� �� �������� ��������� ����� �������������� ����� �� �������� �� ��������� ���������
	// ������� �������� ��� �������, ������� ������ ��� �� ������� ��������� � ������ ����� �� ��������� ���������

	UE_LOG(LogBaseCharacter, Warning, TEXT(" FinalDamage: %f "), FinalDamage);

    // ������� ����
	TakeDamage(FinalDamage, FDamageEvent(), nullptr, nullptr);

	// FinalDamage    - �������� Damage
	// FDamageEvent() - ��� �����, �������� ������ ���
	// nullptr        - ���������� 
	// nullptr        - ��������� �� �Actor
	// ��������� 2 ��������� nullptr ������ ��� ���� ��������� � ����� ���������� �����,� �� Actora 

}
// OnGroundLanded(const FHitResult& Hit) 


// ������������� ����, ����� ������� �� Charactera 
void ASTUBaseCharacter::SetPlayerColor(const FLinearColor& Color)
{
	// ������ �������� �� ���� ������������ 
	const auto MaterialInst = GetMesh()->CreateAndSetMaterialInstanceDynamic(0);

	if (!MaterialInst) return;

	// �������� ��� ��������� � ��� ��������� ��������, ��� ��������� � �������� ����� �������� 
	MaterialInst->SetVectorParameterValue(MaterialColorName, Color);




}











