#pragma once

class CMainDlg;

// Implements cropping functionality. Binds to main dialog.
class CCropCtl {
public:
	enum Handle {
		HH_None,
		HH_Border,
		HH_TopLeft,
		HH_TopRight,
		HH_BottomLeft,
		HH_BottomRight,
		HH_Left,
		HH_Right,
		HH_Top,
		HH_Bottom
	};

	enum CropMode {
		CM_Free,
		CM_FixedSize,
		CM_FixedAspectRatio,
		CM_FixedAspectRatioImage
	};
public:
	CCropCtl(CMainDlg* pMainDlg);

	bool IsCropping() { return m_bCropping; } // during cropping
	bool IsDoCropping() { return m_bDoCropping; } // during cropping and cropping rectangle visible
	
	// Set aspect ratio of cropping rectangle, 0 is invalid.  Only used when CM_FixedAspectRatio bits are on, both Fixed and Image
	void SetCropRectAR(CSize sizeAR);
	
	// set the image size for CropCtl to calculate the ImageAR option
	void SetImageSize(CSize sizeImage);

	// Cropping rectangle in image coordinates (in original size image)
	CRect GetImageCropRect(bool losslessCrop);

	void SetCropMode(CropMode eMode) { m_eCropMode = eMode; }
	//CropMode GetCropMode() { return m_eCropMode; }

	void OnPaint(CPaintDC& dc); // paints cropping rectangle when in cropping
	bool OnTimer(int nTimerId);

	// nX, nY is the current mouse coordinate
	void StartCropping(int nX, int nY);
	bool DoCropping(int nX, int nY);
	void EndCropping(bool bShowMenu);
	void AbortCropping();

	// Snaps a pending (not actively dragged) selection to a 1:1 square around its center.
	// Returns false if there is no such selection.
	bool SnapSelectionToSquare();

	void CancelCropping() { m_bCropping = false; m_bDoCropping = false; }
	void ResetStartCropOnNextClick() { m_bDontStartCropOnNextClick = false; }

	// perform lossless cropping, using the current cropping rectangle
	void CropLossless();

	// Gets the handle hit at the given mouse position
	Handle HitHandle(int nX, int nY);

	// Shows the crop context menu and executes the chosen menu command (if a menu item was chosen)
	// Returns the executed menu command ID, zero if none
	int ShowCropContextMenu();

private:
	CMainDlg* m_pMainDlg;
	CPoint m_cropStart;
	CPoint m_cropEnd;
	CPoint m_cropMouse;
	CPoint m_startTrackMousePos;

	// for tracking
	double m_dLastZoom;

	double GetCropRectAR(void);

	CSize m_sizeCropRectAspectRatio;
	CSize m_sizeImageAspectRatio;
	bool m_bCropRectAspectRatioReversed; // track when an aspect ratio got inverted due to pulling bottom-right

	CropMode m_eCropMode;
	CropMode m_ePrevCropMode; // Store previous crop mode when temporarily using 1:1 aspect ratio with Shift key
	bool m_bTempSquareMode; // true while Shift temporarily forces a 1:1 crop (so a deliberately chosen 1:1 mode is not reset)
	int m_nHandleSize;
	Handle m_eHitHandle;

	bool m_bCropping;
	bool m_bDoCropping;
	bool m_bDoTracking;
	bool m_bTrackingMode;
	bool m_bDontStartCropOnNextClick;

	void TrackCroppingRect(int nX, int nY, Handle eHandle);
	void UpdateCroppingRect(int nX, int nY, HDC hPaintDC, bool bShow);
	CRect GetScreenCropRect();
	void PaintCropRect(HDC hPaintDC);
	void InvalidateSceenCropRect();
	CPoint ScreenToImage(int nX, int nY);
	CPoint PreserveAspectRatio(CPoint cropStart, CPoint cropEnd, bool adjustWidth, bool bCalculateEnd);
	void NormalizeCroppingRect();
	void SetMouseCursor(int nX, int nY);
};