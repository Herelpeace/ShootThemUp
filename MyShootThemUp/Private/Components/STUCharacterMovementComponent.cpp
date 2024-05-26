// My Shoot Them Up Game , All Rights Reserved
// STUCharacterMovementComponent.cpp


#include "Components/STUCharacterMovementComponent.h"
#include "Player/STUBaseCharacter.h"

float USTUCharacterMovementComponent::GetMaxSpeed() const
{
    const float MaxSpeed = Super::GetMaxSpeed();

    const ASTUBaseCharacter* Player = Cast<ASTUBaseCharacter>(GetPawnOwner());   // создаем указатель, так как указатель хранит только указатель на класс Pawna
                                                                                 // нам нужно сделать Cast до нашего конкретного Charactera
    // GetPawnOwner() - возвращает указатель на владельца данного компонента
    // т.е у ASTUBaseCharacter вызываем GetPawnOwner() и она возвращает указатель на ASTUBaseCharacter

    return Player && Player->IsRunning()? MaxSpeed*RunModifier:MaxSpeed;

    // Player                                      - указатель, если он не существует то будет null
    // Player->IsRunning()                         - функция внутри Charactera которую мы создали, true - если применен ускоренный бег
    // IsRunning()? MaxSpeed*RunModifier:MaxSpeed  - если ускоренный бег то MaxSpeed*RunModifier, в противном случае просто MaxSpeed
    // RunModifier                                 - домножаем обычный бег на это число
}
