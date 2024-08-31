// My Shoot Them Up Game , All Rights Reserved
// � STUPauseWidget.cpp


#include "UI/STUPauseWidget.h"
#include "GameFramework/GameModeBase.h"
#include "Components/Button.h"


// BeginPlay ��� ��������
bool USTUPauseWidget::Initialize()
{
	// ��������� �������� ������� ���������� ������������ ������� 
	const auto InitStatus = Super::Initialize();

	if (ClearPauseButton)
	{
		// ������ ������ �� ������� ����� �� ������, �������� ������� OnClearPause()
		ClearPauseButton->OnClicked.AddDynamic(this, &USTUPauseWidget::OnClearPause);

		// ��������� ��������
		// ClearPauseButton->OnClicked  - ��� ����� �� ������
		// ClearPauseButton->OnHovered  - ��� ����������
		// ClearPauseButton->OnPressed  - ��� �������
		// ClearPauseButton->OnReleased - ��� �������
	}

	// ���������� �������� ������������ ������� 
	return InitStatus;
}


// ������� ��� ������� �� ������������ �������, ��� ����� �� ������ CONTINUE
void USTUPauseWidget::OnClearPause()
{
	// �������� �� ��� � �� GameMode
	if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

	// ���������� ���� ���� �������, ������� �����
	GetWorld()->GetAuthGameMode()->ClearPause();
}
