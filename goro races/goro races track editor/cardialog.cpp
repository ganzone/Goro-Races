#include "stdafx.h"
#include "CarDialog.h"

IMPLEMENT_DYNCREATE(CCarDialog, CFormView)

BEGIN_MESSAGE_MAP(CCarDialog, CFormView)
	ON_CBN_SELCHANGE(IDC_CAR_STARTPOS_ROAD,	CCarDialog::OnChangedRoad)
	ON_EN_CHANGE(IDC_CAR_STARTPOS_ANGLE,	CCarDialog::OnChangedAngle)
	ON_EN_CHANGE(IDC_CAR_SPEED_LOW,			CCarDialog::OnChangedLoSpeed)
	ON_EN_CHANGE(IDC_CAR_SPEED_HIGH,		CCarDialog::OnChangedHiSpeed)
	ON_EN_CHANGE(IDC_CAR_SPEED_TRAJCHG,		CCarDialog::OnChangedTrajChgSpeed)
	ON_EN_CHANGE(IDC_CAR_COLOR_RED,			CCarDialog::OnChangedColorRed)
	ON_EN_CHANGE(IDC_CAR_COLOR_GREEN,		CCarDialog::OnChangedColorGreen)
	ON_EN_CHANGE(IDC_CAR_COLOR_BLUE,		CCarDialog::OnChangedColorBlue)
	ON_BN_CLICKED(IDC_CAR_COLOR_CHOOSE,		CCarDialog::OnColorChoose)
	ON_WM_ENABLE()
END_MESSAGE_MAP()


void CCarDialog::Select(grCar *Car)
{
	ASSERT(Car);

	// Update selected car pointer
	SelectedCar = Car;

	// Enable dialog controls
	EnableWindow(TRUE);
}


void CCarDialog::UnSelect(void)
{
	// Update selected car pointer
	SelectedCar = NULL;

	// Disable dialog controls
	EnableWindow(FALSE);
}


void CCarDialog::OnChangedRoad()
{
	InitWinH();

	switch (RoadWnd->GetCurSel())
	{
	case 0: SelectedCar->StartRoad = TRACK_ROAD1_TRAJECTORY; break;
	case 1: SelectedCar->StartRoad = TRACK_ROAD2_TRAJECTORY; break;
	case 2: SelectedCar->StartRoad = TRACK_ROAD3_TRAJECTORY; break;
	case 3: SelectedCar->StartRoad = TRACK_ROAD4_TRAJECTORY; break;
	}

	SelectedCar->setOnTrackPos(SelectedCar->getOnTrackAngle(), SelectedCar->StartRoad);
	//UpdateDialogData();

	GetDocument()->SetModifiedFlag(TRUE);
}


void CCarDialog::OnChangedAngle()
{
	InitWinH();

	SelectedCar->StartAngle = AngleSpin->GetPos() * M_PI / 180;
	SelectedCar->setOnTrackPos(SelectedCar->StartAngle);
	GetDocument()->SetModifiedFlag(TRUE);
}


void CCarDialog::OnChangedLoSpeed()
{
	InitWinH();

	SelectedCar->LoSpeed = ((float) LoSpeedSpin->GetPos()) / 1000;
	GetDocument()->SetModifiedFlag(TRUE);
}


void CCarDialog::OnChangedHiSpeed()
{
	InitWinH();

	SelectedCar->HiSpeed = ((float) HiSpeedSpin->GetPos()) / 1000;
	GetDocument()->SetModifiedFlag(TRUE);
}


void CCarDialog::OnChangedTrajChgSpeed()
{
	InitWinH();

	SelectedCar->TrajChgSpeed = ((float) TrajChgSpin->GetPos()) / 1000;
	GetDocument()->SetModifiedFlag(TRUE);
}


void CCarDialog::OnChangedColorRed()
{
	InitWinH();
	
	SelectedCar->Color.r = ((float) ColorRSpin->GetPos()) / 255;
	GetDocument()->SetModifiedFlag(TRUE);
}


void CCarDialog::OnChangedColorGreen()
{
	InitWinH();
	
	SelectedCar->Color.g = ((float) ColorGSpin->GetPos()) / 255;
	GetDocument()->SetModifiedFlag(TRUE);
}


void CCarDialog::OnChangedColorBlue()
{
	InitWinH();
	
	SelectedCar->Color.b = ((float) ColorBSpin->GetPos()) / 255;
	GetDocument()->SetModifiedFlag(TRUE);
}


void CCarDialog::OnColorChoose()
{
	CColorDialog ColorDialog;
	ColorDialog.DoModal();
	COLORREF Color = ColorDialog.GetColor();
	
	SelectedCar->Color.r = (float) ((float) (GetRValue(Color)) / 255);
	SelectedCar->Color.g = (float) ((float) (GetGValue(Color)) / 255);
	SelectedCar->Color.b = (float) ((float) (GetBValue(Color)) / 255);

	UpdateDialogData();
}


void CCarDialog::OnEnable(BOOL bEnable)
{
	InitWinH();

	// Set enabled flag
	AngleWnd->EnableWindow(bEnable);
	RoadWnd->EnableWindow(bEnable);
	LoSpeedWnd->EnableWindow(bEnable);
	HiSpeedWnd->EnableWindow(bEnable);
	TrajChgWnd->EnableWindow(bEnable);
	ColorRWnd->EnableWindow(bEnable);
	ColorGWnd->EnableWindow(bEnable);
	ColorBWnd->EnableWindow(bEnable);
	ColorChooseWnd->EnableWindow(bEnable);
	AngleSpin->EnableWindow(bEnable);
	LoSpeedSpin->EnableWindow(bEnable);
	HiSpeedSpin->EnableWindow(bEnable);
	TrajChgSpin->EnableWindow(bEnable);
	ColorRSpin->EnableWindow(bEnable);
	ColorGSpin->EnableWindow(bEnable);
	ColorBSpin->EnableWindow(bEnable);

	if (bEnable)
		UpdateDialogData();
}


void CCarDialog::OnInitialUpdate(void)
{
	InitWinH();

	// Initialize selected car pointer
	SelectedCar = NULL;

	// Disable dialog
	EnableWindow(FALSE);

	// Set spin controls buddy windows
	AngleSpin->SetBuddy(AngleWnd);
	LoSpeedSpin->SetBuddy(LoSpeedWnd);
	HiSpeedSpin->SetBuddy(HiSpeedWnd);
	TrajChgSpin->SetBuddy(TrajChgWnd);
	ColorRSpin->SetBuddy(ColorRWnd);
	ColorGSpin->SetBuddy(ColorGWnd);
	ColorBSpin->SetBuddy(ColorBWnd);

	// Set spin controls ranges
	AngleSpin->SetRange(0, 359);
	LoSpeedSpin->SetRange(1, 1000);
	HiSpeedSpin->SetRange(1, 1000);
	TrajChgSpin->SetRange(1, 1000);
	ColorRSpin->SetRange(0, 255);
	ColorGSpin->SetRange(0, 255);
	ColorBSpin->SetRange(0, 255);
}


void CCarDialog::UpdateDialogData()
{
	// Check if a car is selected
	if (!SelectedCar)
		return;

	InitWinH();
	
	// Fill dialog with selected car data
		if (SelectedCar->StartRoad == TRACK_ROAD1_TRAJECTORY)
		RoadWnd->SetCurSel(0);
	else
		if (SelectedCar->StartRoad == TRACK_ROAD2_TRAJECTORY)
		RoadWnd->SetCurSel(1);
	else
		if (SelectedCar->StartRoad == TRACK_ROAD3_TRAJECTORY)
		RoadWnd->SetCurSel(2);
	else
		if (SelectedCar->StartRoad == TRACK_ROAD4_TRAJECTORY)
		RoadWnd->SetCurSel(3);

	AngleSpin->SetPos((int) (SelectedCar->StartAngle * 180 / M_PI));
	LoSpeedSpin->SetPos((int) (SelectedCar->LoSpeed * 1000));
	HiSpeedSpin->SetPos((int) (SelectedCar->HiSpeed * 1000));
	TrajChgSpin->SetPos((int) (SelectedCar->TrajChgSpeed * 1000));
	ColorRSpin->SetPos((int) (SelectedCar->Color.r * 255));
	ColorGSpin->SetPos((int) (SelectedCar->Color.g * 255));
	ColorBSpin->SetPos((int) (SelectedCar->Color.b * 255));
}


void CCarDialog::InitWinH()
{
	RoadWnd = (CComboBox *) GetDescendantWindow(IDC_CAR_STARTPOS_ROAD);
	AngleWnd = (CEdit *) GetDescendantWindow(IDC_CAR_STARTPOS_ANGLE);
	LoSpeedWnd = (CEdit *) GetDescendantWindow(IDC_CAR_SPEED_LOW);
	HiSpeedWnd = (CEdit *) GetDescendantWindow(IDC_CAR_SPEED_HIGH);
	TrajChgWnd = (CEdit *) GetDescendantWindow(IDC_CAR_SPEED_TRAJCHG);
	ColorRWnd = (CEdit *) GetDescendantWindow(IDC_CAR_COLOR_RED);
	ColorGWnd = (CEdit *) GetDescendantWindow(IDC_CAR_COLOR_GREEN);
	ColorBWnd = (CEdit *) GetDescendantWindow(IDC_CAR_COLOR_BLUE);
	ColorChooseWnd = (CButton *) GetDescendantWindow(IDC_CAR_COLOR_CHOOSE);
	AngleSpin = (CSpinButtonCtrl *) GetDescendantWindow(IDC_CAR_STARTPOS_ANGLE_SPIN);
	LoSpeedSpin = (CSpinButtonCtrl *) GetDescendantWindow(IDC_CAR_SPEED_LOW_SPIN);
	HiSpeedSpin = (CSpinButtonCtrl *) GetDescendantWindow(IDC_CAR_SPEED_HIGH_SPIN);
	TrajChgSpin = (CSpinButtonCtrl *) GetDescendantWindow(IDC_CAR_SPEED_TRAJCHG_SPIN);
	ColorRSpin = (CSpinButtonCtrl *) GetDescendantWindow(IDC_CAR_COLOR_RED_SPIN);
	ColorGSpin = (CSpinButtonCtrl *) GetDescendantWindow(IDC_CAR_COLOR_GREEN_SPIN);
	ColorBSpin = (CSpinButtonCtrl *) GetDescendantWindow(IDC_CAR_COLOR_BLUE_SPIN);

	ASSERT(RoadWnd);
	ASSERT(AngleWnd);
	ASSERT(LoSpeedWnd);
	ASSERT(HiSpeedWnd);
	ASSERT(TrajChgWnd);
	ASSERT(ColorRWnd);
	ASSERT(ColorGWnd);
	ASSERT(ColorBWnd);
	ASSERT(ColorChooseWnd);
	ASSERT(AngleSpin);
	ASSERT(LoSpeedSpin);
	ASSERT(HiSpeedSpin);
	ASSERT(TrajChgSpin);
	ASSERT(ColorRSpin);
	ASSERT(ColorGSpin);
	ASSERT(ColorBSpin);
}