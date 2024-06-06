// My Shoot Them Up Game , All Rights Reserved
// В STUEquipFinishedAnimNotify.cpp


#include "Animations/STUEquipFinishedAnimNotify.h"

void USTUEquipFinishedAnimNotify ::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	// вызываем наш делегат, передаем Мэш скелета в котором вызвался делегат
	OnNotified.Broadcast(MeshComp);


	Super::Notify(MeshComp, Animation);

}