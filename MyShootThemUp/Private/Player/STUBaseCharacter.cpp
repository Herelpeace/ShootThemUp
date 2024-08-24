// My Shoot Them Up Game , All Rights Reserved
// � STUBaseCharacter.cpp


#include "Player/STUBaseCharacter.h"

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

	HealthComponent = CreateDefaultSubobject<USTUHealthActorComponent>("HealthComponent");   // ������� ������ � ���������
	                                                                                         // ������ �� � ���� �� �����������, �� ���������� ����� ������ � �������
	WeaponComponent = CreateDefaultSubobject<USTUWeaponComponent>("WeaponComponent");   // ������� ������ � ������� �������� ���� ������ ������
                                                                                 
} 

// Called when the game starts or when spawned
void ASTUBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	check(HealthComponent) // �������� ��� ������� ������� � ����������
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
	
}



// Called every frame
void ASTUBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const auto Health = HealthComponent->GetHealth();                      // ������� ���������� � ���� ����� ������, � ������� �������� ������� �������� ��������
	//HealthTextComponent->SetText(FText::FromString(FString::Printf(TEXT(" %.0f"), Health)));           // ������� �������� �������� �� ����� � ���� ����
}


// ���������� true ����� �������� ���������� ���������� ���
bool ASTUBaseCharacter::IsRunning() const
{
	return false;

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











