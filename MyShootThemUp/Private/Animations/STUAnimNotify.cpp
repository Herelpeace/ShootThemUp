// My Shoot Them Up Game , All Rights Reserved
// В STUAnimNotify.cpp


#include "Animations/STUAnimNotify.h"

void USTUAnimNotify ::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	// вызываем наш делегат, передаем Мэш скелета в котором вызвался делегат
	OnNotified.Broadcast(MeshComp);

	Super::Notify(MeshComp, Animation);

}