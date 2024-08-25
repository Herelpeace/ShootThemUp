// My Shoot Them Up Game , All Rights Reserved
// � STUPlayerCharacter.cpp


#include "Player/STUPlayerCharacter.h"
#include "Camera/CameraComponent.h"                   // ��������� ������������ ���� ������
#include "Components/InputComponent.h"                
#include "GameFramework/SpringArmComponent.h"         // ��������� ��������
#include "Components/STUWeaponComponent.h"            // ��� ����� ������ � �������
#include "Components/SphereComponent.h"               // ��������� �����
#include "Components/CapsuleComponent.h"              // ��������� �������

// Sets default values
ASTUPlayerCharacter::ASTUPlayerCharacter (const FObjectInitializer& ObjInit): Super(ObjInit)

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
	CameraComponent->SetupAttachment(SpringArmComponent);                            // ������������ �������� SpringArmComponent

	CameraCollisionComponent = CreateDefaultSubobject<USphereComponent>("CameraCollisionComponent");	// ������� SphereComponent
	CameraCollisionComponent->SetupAttachment(CameraComponent);                                         // ������������ � ���������� ������ 
	CameraCollisionComponent->SetSphereRadius(10.0f);                                                   // ������������� ������ �����
	CameraCollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);       // ������� �������� �� ��� ������ (Overlap - ��� ����������� � ������ ���������)

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

	PlayerInputComponent->BindAxis("MoveForward", this, &ASTUPlayerCharacter::MoveForward);  // ���� ������� �������� ������/�����
	PlayerInputComponent->BindAxis("MoveRight", this, &ASTUPlayerCharacter::MoveRight);      // ���� ������� �������� ������/������

	PlayerInputComponent->BindAxis("LookUp", this, &ASTUPlayerCharacter::AddControllerPitchInput); // ���� ����� �����/����
	PlayerInputComponent->BindAxis("TurnAround", this, &ASTUPlayerCharacter::AddControllerYawInput); // ���� ����� ������ ���������

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASTUPlayerCharacter::Jump);           // ������
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ASTUPlayerCharacter::OnStartRunning);  // ������ shift
	PlayerInputComponent->BindAction("Run", IE_Released, this, &ASTUPlayerCharacter::OnStopRunning);  // ��������� shift

	// Jump       - �������� ��������
	// IE_Pressed - ��������� ��������, ����� ����� ������ CallBack
	// this       - ������ � �������� ���������
	// &ASTUBaseCharacter::Jump - ������� ������� ����� ������� ��� ������� ������� (��� ����������� � ������ Pawn)

	PlayerInputComponent->BindAction("Fire", IE_Pressed, WeaponComponent, &USTUWeaponComponent::StartFire); // ���� ������� �������� ������
	PlayerInputComponent->BindAction("Fire", IE_Released, WeaponComponent, &USTUWeaponComponent::StopFire);
	PlayerInputComponent->BindAction("NextWeapon", IE_Released, WeaponComponent, &USTUWeaponComponent::NextWeapon); // ����� ������
	PlayerInputComponent->BindAction("Reload", IE_Pressed, WeaponComponent, &USTUWeaponComponent::Reload); // �����������
}


// MoveForward(float Amount) �������� ������/�����
void ASTUPlayerCharacter::MoveForward(float Amount)
{
	if (Amount == 0.0f) return;
	IsMovingForward = Amount > 0.0f; // ���� >0 ������ ������ ������� �������� ������
	AddMovementInput(GetActorForwardVector(), Amount);

	// GetActorForwardVector() - ������, ����������� � ������� ��������
	// Amount                  - �������� ��������. ����������� �� ������
}
// MoveForward(float Amount) 

// MoveRight(float Amount)  �������� �����/������
void ASTUPlayerCharacter::MoveRight(float Amount)
{
	if (Amount == 0.0f)   return;
	AddMovementInput(GetActorRightVector(), Amount);
}
// MoveRight(float Amount) 

// ���������� ��� ������� Left Shift
void ASTUPlayerCharacter::OnStartRunning()
{
	WantsToRun = true;
}
//OnStartRunning() 

// ����� �������� Left Shift
void ASTUPlayerCharacter::OnStopRunning()
{
	WantsToRun = false;
}
// OnStopRunning() 

// ���������� true ����� �������� ���������� ���������� ���
bool ASTUPlayerCharacter::IsRunning() const
{
	return WantsToRun && IsMovingForward && !GetVelocity().IsZero();

	//WantsToRun             - ����� shift
	//IsMovingForward        - ������ ������� ������
	//GetVelocity().IsZero() - ������ �������� ��������� �� ����� 0, �� ������������� ���������
}
// IsRunning()

// ������� ���������� ���������, ����� �������� ����� 0
void ASTUPlayerCharacter::OnDeath()
{
	Super::OnDeath();

	if (Controller)  // �������� �� null
	{
		// ������� ��� ����� Pawna
		Controller->ChangeState(NAME_Spectating);
	}
}
// OnDeath()

	// ������� ��� ����� �� ������� BeginOverlap
void ASTUPlayerCharacter::OnCameraCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// ��������� ������������ �� �������� ����� � �������
	CheckCameraOverlap();
}

// ������� ��� ����� �� ������� EndOverlap
void ASTUPlayerCharacter::OnCameraCollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// ��������� ������������ �� �������� ����� � �������
	CheckCameraOverlap();
}


// ��������� ������������ �� �������� ����� � �������
void ASTUPlayerCharacter::CheckCameraOverlap()
{
	// ��������� ���� �� ����������� � ����������� �������, ������� IsOverlappingComponent(name_Component)
	const auto HideMesh = CameraCollisionComponent->IsOverlappingComponent(GetCapsuleComponent());

	// ������ ��� ��������� ���������
	GetMesh()->SetOwnerNoSee(HideMesh);

	// ��������� ������ ���������� �� ���������� �����, � ������ ������ ��� ����� ���
	TArray<USceneComponent*> MeshChildren;

	// �������� ��� �������� ���������� ���� (��� ������ � �.�.)
	GetMesh()->GetChildrenComponents(true, MeshChildren);
	// true         - ������ �������� �� ���� �������, false - ������ ������� ������ 
	// MeshChildren - ������ �� ������, � ���� ����������� ��������� �� ��� �������� ���������� 

	for (auto MeshChild : MeshChildren)
	{
		// MeshChildren - ��� USceneComponent � ���� ������ ��������� ���������
		// ������� ������ ��� �� UPrimitiveComponent, � �������� ��� ����� ��������� ���������  
		// ������� �� ������� SetOwnerNoSee ������ ��� ��� ���������� � UPrimitiveComponent, 
		// � ������� �� UPrimitiveComponent ������ ��� �� ����������� �� USceneComponent

		const auto MeshChildGeometry = Cast<UPrimitiveComponent>(MeshChild);
		if (MeshChildGeometry)
		{
			MeshChildGeometry->SetOwnerNoSee(HideMesh);
		}
	}
}
















