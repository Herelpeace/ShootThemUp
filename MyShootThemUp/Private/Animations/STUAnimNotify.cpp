// My Shoot Them Up Game , All Rights Reserved
// � STUAnimNotify.cpp


#include "Animations/STUAnimNotify.h"

void USTUAnimNotify ::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	// �������� ��� �������, �������� ��� ������� � ������� �������� �������
	OnNotified.Broadcast(MeshComp);

	Super::Notify(MeshComp, Animation);

}