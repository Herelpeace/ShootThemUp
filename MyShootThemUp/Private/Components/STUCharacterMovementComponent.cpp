// My Shoot Them Up Game , All Rights Reserved
// STUCharacterMovementComponent.cpp


#include "Components/STUCharacterMovementComponent.h"
#include "Player/STUBaseCharacter.h"

float USTUCharacterMovementComponent::GetMaxSpeed() const
{
    const float MaxSpeed = Super::GetMaxSpeed();

    const ASTUBaseCharacter* Player = Cast<ASTUBaseCharacter>(GetPawnOwner());   // ������� ���������, ��� ��� ��������� ������ ������ ��������� �� ����� Pawna
                                                                                 // ��� ����� ������� Cast �� ������ ����������� Charactera
    // GetPawnOwner() - ���������� ��������� �� ��������� ������� ����������
    // �.� � ASTUBaseCharacter �������� GetPawnOwner() � ��� ���������� ��������� �� ASTUBaseCharacter

    return Player && Player->IsRunning()? MaxSpeed*RunModifier:MaxSpeed;

    // Player                                      - ���������, ���� �� �� ���������� �� ����� null
    // Player->IsRunning()                         - ������� ������ Charactera ������� �� �������, true - ���� �������� ���������� ���
    // IsRunning()? MaxSpeed*RunModifier:MaxSpeed  - ���� ���������� ��� �� MaxSpeed*RunModifier, � ��������� ������ ������ MaxSpeed
    // RunModifier                                 - ��������� ������� ��� �� ��� �����
}
