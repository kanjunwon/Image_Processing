
// ImagePro20210797View.h: CImagePro20210797View 클래스의 인터페이스
//

#pragma once


class CImagePro20210797View : public CScrollView
{
protected: // serialization에서만 만들어집니다.
	CImagePro20210797View() noexcept;
	DECLARE_DYNCREATE(CImagePro20210797View)

// 특성입니다.
public:
	CImagePro20210797Doc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 생성 후 처음 호출되었습니다.
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CImagePro20210797View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPixelAdd();
	afx_msg void OnPixelMul();
	afx_msg void OnPixelSub();
	afx_msg void OnPixelDiv();
	afx_msg void OnPixelHistoEq();
	afx_msg void OnPixelContrastStretch();
	afx_msg void OnPixelBinarization();
	afx_msg void OnPixelTwoImageAdd();
	afx_msg void OnPixelTwoImageSub();
	afx_msg void OnRegionMeaning();
	void Convolve(unsigned char** inImage, unsigned char** outImage, int cols, int rows, float mask[][3], int bias, int Depth);
	afx_msg void OnRegionSharpening();
	afx_msg void OnResionEmbossing();
	afx_msg void OnRegionPrewitt();
	afx_msg void OnResionRoberts();
	afx_msg void OnResionSobel();
	afx_msg void OnResionAverageFiltering();
	afx_msg void OnResionMedianFiltering();
	afx_msg void OnMopologyColorToGray();
	afx_msg void OnMopologyBinarization();
	afx_msg void OnMopologyErosion();
	afx_msg void OnMopologyDialation();
	void CopyResultToInput();
	afx_msg void OnMopologyOpening();
	afx_msg void OnMopologyClosing();
	afx_msg void OnGeometryZoominPixelCopy();
	afx_msg void OnGeometryZoominBilinearInterpolation();
	afx_msg void OnGeometryZoomoutSubsampling();
	afx_msg void OnGeometryZoomoutMeanSub();
	afx_msg void OnGeometryZoomoutAvg();
	afx_msg void OnGeometryRotation();
	afx_msg void OnGeometryMirror();
	afx_msg void OnGeometryFlip();
	afx_msg void OnGeometryWarping();
	afx_msg void OnGeometryMorphing();
	afx_msg void OnGeometryMorphingWithLoad();
	void MorphImages(double alpha);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnAviView();
	CString AVIFileName;
	bool bAviMode;
	void LoadAviFile(CDC* pDC);
};

#ifndef _DEBUG  // ImagePro20210797View.cpp의 디버그 버전
inline CImagePro20210797Doc* CImagePro20210797View::GetDocument() const
   { return reinterpret_cast<CImagePro20210797Doc*>(m_pDocument); }
#endif

