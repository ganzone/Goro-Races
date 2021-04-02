#pragma once

#include "Resource.h"
#include "grCar.h"

class CCarDialog : public CFormView
{
	DECLARE_DYNCREATE(CCarDialog)
// Attributes
private:
	// Current selected car
	grCar *SelectedCar;

	// Temporary handlers to editable windows
	CComboBox *RoadWnd;
	CEdit *AngleWnd;
	CEdit *LoSpeedWnd;
	CEdit *HiSpeedWnd;
	CEdit *TrajChgWnd;
	CEdit *ColorRWnd;
	CEdit *ColorGWnd;
	CEdit *ColorBWnd;
	CButton *ColorChooseWnd;
	CSpinButtonCtrl *AngleSpin;
	CSpinButtonCtrl *LoSpeedSpin;
	CSpinButtonCtrl *HiSpeedSpin;
	CSpinButtonCtrl *TrajChgSpin;
	CSpinButtonCtrl *ColorRSpin;
	CSpinButtonCtrl *ColorGSpin;
	CSpinButtonCtrl *ColorBSpin;

// Functions
public:
	// Update dialog with given car data
	void Select(grCar *Car);
	// Unselect selected car
	void UnSelect();
	// Re-Initialize temporary handlers to editable windows
	void InitWinH();
	void UpdateDialogData();

	DECLARE_MESSAGE_MAP()
	afx_msg void OnChangedRoad();
	afx_msg void OnChangedAngle();
	afx_msg void OnChangedLoSpeed();
	afx_msg void OnChangedHiSpeed();
	afx_msg void OnChangedTrajChgSpeed();
	afx_msg void OnChangedColorRed();
	afx_msg void OnChangedColorGreen();
	afx_msg void OnChangedColorBlue();
	afx_msg void OnColorChoose();

//Overrides
	afx_msg void OnEnable(BOOL bEnable);
	void OnInitialUpdate();

// Constructors and destructors
public:
	CCarDialog() : CFormView(IDD_CAR_DIALOG) { };
	~CCarDialog(void) { }
};
