
// ImagePro20210797View.cpp: CImagePro20210797View 클래스의 구현

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ImagePro20210797.h"
#endif

#include "ImagePro20210797Doc.h"
#include "ImagePro20210797View.h"

#include "CAngleInDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CImagePro20210797View

IMPLEMENT_DYNCREATE(CImagePro20210797View, CScrollView)

BEGIN_MESSAGE_MAP(CImagePro20210797View, CScrollView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
	ON_COMMAND(ID_PIXEL_ADD, &CImagePro20210797View::OnPixelAdd)
	ON_COMMAND(ID_PIXEL_MUL, &CImagePro20210797View::OnPixelMul)
	ON_COMMAND(ID_PIXEL_SUB, &CImagePro20210797View::OnPixelSub)
	ON_COMMAND(ID_PIXEL_DIV, &CImagePro20210797View::OnPixelDiv)
	ON_COMMAND(ID_PIXEL_HISTO_EQ, &CImagePro20210797View::OnPixelHistoEq)
	ON_COMMAND(ID_PIXEL_CONTRAST_STRETCH, &CImagePro20210797View::OnPixelContrastStretch)
	ON_COMMAND(ID_PIXEL_BINARIZATION, &CImagePro20210797View::OnPixelBinarization)
	ON_COMMAND(ID_PIXEL_TWO_IMAGE_ADD, &CImagePro20210797View::OnPixelTwoImageAdd)
	ON_COMMAND(ID_PIXEL_TWO_IMAGE_SUB, &CImagePro20210797View::OnPixelTwoImageSub)
	ON_COMMAND(ID_REGION_MEANING, &CImagePro20210797View::OnRegionMeaning)
	ON_COMMAND(ID_REGION_SHARPENING, &CImagePro20210797View::OnRegionSharpening)
	ON_COMMAND(ID_RESION_EMBOSSING, &CImagePro20210797View::OnResionEmbossing)
	ON_COMMAND(ID_REGION_PREWITT, &CImagePro20210797View::OnRegionPrewitt)
	ON_COMMAND(ID_RESION_ROBERTS, &CImagePro20210797View::OnResionRoberts)
	ON_COMMAND(ID_RESION_SOBEL, &CImagePro20210797View::OnResionSobel)
	ON_COMMAND(ID_RESION_AVERAGE_FILTERING, &CImagePro20210797View::OnResionAverageFiltering)
	ON_COMMAND(ID_RESION_MEDIAN_FILTERING, &CImagePro20210797View::OnResionMedianFiltering)
	ON_COMMAND(ID_MOPOLOGY_COLOR_TO_GRAY, &CImagePro20210797View::OnMopologyColorToGray)
	ON_COMMAND(ID_MOPOLOGY_BINARIZATION, &CImagePro20210797View::OnMopologyBinarization)
	ON_COMMAND(ID_MOPOLOGY_EROSION, &CImagePro20210797View::OnMopologyErosion)
	ON_COMMAND(ID_MOPOLOGY_DIALATION, &CImagePro20210797View::OnMopologyDialation)
	ON_COMMAND(ID_MOPOLOGY_OPENING, &CImagePro20210797View::OnMopologyOpening)
	ON_COMMAND(ID_MOPOLOGY_CLOSING, &CImagePro20210797View::OnMopologyClosing)
	ON_COMMAND(ID_GEOMETRY_ZOOMIN_PIXEL_COPY, &CImagePro20210797View::OnGeometryZoominPixelCopy)
	ON_COMMAND(ID_GEOMETRY_ZOOMIN_BILINEAR_INTERPOLATION, &CImagePro20210797View::OnGeometryZoominBilinearInterpolation)
	ON_COMMAND(ID_GEOMETRY_ZOOMOUT_SUBSAMPLING, &CImagePro20210797View::OnGeometryZoomoutSubsampling)
	ON_COMMAND(ID_GEOMETRY_ZOOMOUT_MEAN_SUB, &CImagePro20210797View::OnGeometryZoomoutMeanSub)
	ON_COMMAND(ID_GEOMETRY_ZOOMOUT_AVG, &CImagePro20210797View::OnGeometryZoomoutAvg)
	ON_COMMAND(ID_GEOMETRY_ROTATION, &CImagePro20210797View::OnGeometryRotation)
	ON_COMMAND(ID_GEOMETRY_MIRROR, &CImagePro20210797View::OnGeometryMirror)
	ON_COMMAND(ID_GEOMETRY_FLIP, &CImagePro20210797View::OnGeometryFlip)
	ON_COMMAND(ID_GEOMETRY_WARPING, &CImagePro20210797View::OnGeometryWarping)
	ON_COMMAND(ID_GEOMERTY_MORPHING, &CImagePro20210797View::OnGeometryMorphingWithLoad)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_AVI_VIEW, &CImagePro20210797View::OnAviView)
END_MESSAGE_MAP()

// CImagePro20210797View 생성/소멸

CImagePro20210797View::CImagePro20210797View() noexcept
{
	bAviMode = false;

}

CImagePro20210797View::~CImagePro20210797View()
{

}

BOOL CImagePro20210797View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CScrollView::PreCreateWindow(cs);
}

// CImagePro20210797View 그리기

void CImagePro20210797View::OnDraw(CDC* pDC)
{
	CImagePro20210797Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if (bAviMode)
	{
		LoadAviFile(pDC);
		bAviMode = false;
		return;
	}

	int x, y;

	if (pDoc->InputImage != NULL)
	{
		if (pDoc->Depth == 1)
		{
			for (y = 0; y < pDoc->lmageHeight; y++)
				for (x = 0; x < pDoc->lmageWidth; x++)
					pDC->SetPixel(x, y, RGB(pDoc->InputImage[y][x], pDoc->InputImage[y][x], pDoc->InputImage[y][x]));
		}
		else
		{
			for (y = 0; y < pDoc->lmageHeight; y++)
				for (x = 0; x < pDoc->lmageWidth; x++)
					pDC->SetPixel(x, y, RGB(pDoc->InputImage[y][3 * x + 0], pDoc->InputImage[y][3 * x + 1], pDoc->InputImage[y][3 * x + 2]));
		}
	}

	if (pDoc->ResultImage != NULL)
	{
		if (pDoc->Depth == 1)
		{
			for (y = 0; y < pDoc->lmageHeight; y++)
				for (x = 0; x < pDoc->lmageWidth; x++)
					pDC->SetPixel(x + pDoc->lmageWidth + 20, y, RGB(pDoc->ResultImage[y][x], pDoc->ResultImage[y][x], pDoc->ResultImage[y][x]));
		}
		else
		{
			for (y = 0; y < pDoc->lmageHeight; y++)
				for (x = 0; x < pDoc->lmageWidth; x++)
					pDC->SetPixel(x + pDoc->lmageWidth + 20, y, RGB(pDoc->ResultImage[y][3 * x + 0], pDoc->ResultImage[y][3 * x + 1], pDoc->ResultImage[y][3 * x + 2]));
		}
	}

	if (pDoc->InputImage2 != NULL)
	{
		if (pDoc->Depth == 1)
		{
			for (y = 0; y < pDoc->lmageHeight; y++)
				for (x = 0; x < pDoc->lmageWidth; x++)
					pDC->SetPixel(x + (pDoc->lmageWidth + 20) * 2, y, RGB(pDoc->InputImage2[y][x], pDoc->InputImage2[y][x], pDoc->InputImage2[y][x]));
		}
		else
		{
			for (y = 0; y < pDoc->lmageHeight; y++)
				for (x = 0; x < pDoc->lmageWidth; x++)
					pDC->SetPixel(x + (pDoc->lmageWidth + 20) * 2, y, RGB(pDoc->InputImage2[y][3 * x + 0], pDoc->InputImage2[y][3 * x + 1], pDoc->InputImage2[y][3 * x + 2]));
		}
	}

	if (pDoc->gResultImage != NULL)		// 기하학적 처리
	{
		if (pDoc->Depth == 1)
		{
			for (y = 0; y < pDoc->glmageHeight; y++)
				for (x = 0; x < pDoc->glmageWidth; x++)
					pDC->SetPixel(x, y + pDoc->lmageHeight + 20, RGB(pDoc->gResultImage[y][x], pDoc->gResultImage[y][x], pDoc->gResultImage[y][x]));
		}
		else
		{
			for (y = 0; y < pDoc->glmageHeight; y++)
				for (x = 0; x < pDoc->glmageWidth; x++)
					pDC->SetPixel(x, y + pDoc->lmageHeight + 20, RGB(pDoc->gResultImage[y][3 * x + 0], pDoc->gResultImage[y][3 * x + 1], pDoc->gResultImage[y][3 * x + 2]));
		}
	}
}

void CImagePro20210797View::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: 이 뷰의 전체 크기를 계산합니다.
	sizeTotal.cx = 2048;
	sizeTotal.cy = 2048;
	SetScrollSizes(MM_TEXT, sizeTotal);
}


// CImagePro20210797View 인쇄

BOOL CImagePro20210797View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CImagePro20210797View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CImagePro20210797View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

// CImagePro20210797View 진단

#ifdef _DEBUG
void CImagePro20210797View::AssertValid() const
{
	CScrollView::AssertValid();
}

void CImagePro20210797View::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CImagePro20210797Doc* CImagePro20210797View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImagePro20210797Doc)));
	return (CImagePro20210797Doc*)m_pDocument;
}
#endif //_DEBUG

// CImagePro20210797View 메시지 처리기

void CImagePro20210797View::OnPixelAdd() // 덧셈 연산
{
	CImagePro20210797Doc* pDoc = GetDocument();

	int x, y;
	int value;
	for (y = 0; y < pDoc->lmageHeight; y++)
		for (x = 0; x < pDoc->lmageWidth; x++)
		{
			if (pDoc->Depth == 1)
			{
			value = pDoc->InputImage[y][x] + 40;
			if (value > 255)	value = 255;
			else if (value < 0)	value = 0;

			pDoc->ResultImage[y][x] = value;
			}
			else
			{
				value = pDoc->InputImage[y][3 * x + 0] + 40;
				if (value > 255)	value = 255;
				else if (value < 0)	value = 0;

				pDoc->ResultImage[y][3 * x + 0] = value;

				value = pDoc->InputImage[y][3 * x + 1] + 40;
				if (value > 255)	value = 255;
				else if (value < 0)	value = 0;

				pDoc->ResultImage[y][3 * x + 1] = value;

				value = pDoc->InputImage[y][3 * x + 2] + 40;
				if (value > 255)	value = 255;
				else if (value < 0)	value = 0;

				pDoc->ResultImage[y][3 * x + 2] = value;
			}
		}
	Invalidate();
}

void CImagePro20210797View::OnPixelMul() // 곱셈 연산
{
	CImagePro20210797Doc* pDoc = GetDocument();

	int x, y;
	int value;
	for (y = 0; y < pDoc->lmageHeight; y++)
		for (x = 0; x < pDoc->lmageWidth; x++)
		{
			if (pDoc->Depth == 1)
			{
				value = pDoc->InputImage[y][x] * 1.2;
				if (value > 255)	value = 255;
				else if (value < 0)	value = 0;

				pDoc->ResultImage[y][x] = value;
			}
			else
			{
				value = pDoc->InputImage[y][3 * x + 0] * 1.2;
				if (value > 255)	value = 255;
				else if (value < 0)	value = 0;

				pDoc->ResultImage[y][3 * x + 0] = value;

				value = pDoc->InputImage[y][3 * x + 1] * 1.2;
				if (value > 255)	value = 255;
				else if (value < 0)	value = 0;

				pDoc->ResultImage[y][3 * x + 1] = value;

				value = pDoc->InputImage[y][3 * x + 2] * 1.2;
				if (value > 255)	value = 255;
				else if (value < 0)	value = 0;

				pDoc->ResultImage[y][3 * x + 2] = value;
			}
		}
	Invalidate();
}

void CImagePro20210797View::OnPixelSub() // 뺄셈 연산
{
	CImagePro20210797Doc* pDoc = GetDocument();

	int x, y;
	int value;
	for (y = 0; y < pDoc->lmageHeight; y++)
		for (x = 0; x < pDoc->lmageWidth; x++)
		{
			if (pDoc->Depth == 1)
			{
				value = pDoc->InputImage[y][x] - 50;
				if (value > 255)	value = 255;
				else if (value < 0)	value = 0;

				pDoc->ResultImage[y][x] = value;
			}
			else
			{
				value = pDoc->InputImage[y][3 * x + 0] - 50;
				if (value > 255)	value = 255;
				else if (value < 0)	value = 0;

				pDoc->ResultImage[y][3 * x + 0] = value;

				value = pDoc->InputImage[y][3 * x + 1] - 50;
				if (value > 255)	value = 255;
				else if (value < 0)	value = 0;

				pDoc->ResultImage[y][3 * x + 1] = value;

				value = pDoc->InputImage[y][3 * x + 2] - 50;
				if (value > 255)	value = 255;
				else if (value < 0)	value = 0;

				pDoc->ResultImage[y][3 * x + 2] = value;
			}
		}
	Invalidate();
}

void CImagePro20210797View::OnPixelDiv() // 나눗셈 연산
{
	CImagePro20210797Doc* pDoc = GetDocument();

	int x, y;
	int value;
	for (y = 0; y < pDoc->lmageHeight; y++)
		for (x = 0; x < pDoc->lmageWidth; x++)
		{
			if (pDoc->Depth == 1)
			{
				value = pDoc->InputImage[y][x] / 1.2;
				if (value > 255)	value = 255;
				else if (value < 0)	value = 0;

				pDoc->ResultImage[y][x] = value;
			}
			else
			{
				value = pDoc->InputImage[y][3 * x + 0] / 1.2;
				if (value > 255)	value = 255;
				else if (value < 0)	value = 0;

				pDoc->ResultImage[y][3 * x + 0] = value;

				value = pDoc->InputImage[y][3 * x + 1] / 1.2;
				if (value > 255)	value = 255;
				else if (value < 0)	value = 0;

				pDoc->ResultImage[y][3 * x + 1] = value;

				value = pDoc->InputImage[y][3 * x + 2] / 1.2;
				if (value > 255)	value = 255;
				else if (value < 0)	value = 0;

				pDoc->ResultImage[y][3 * x + 2] = value;
			}
		}
	Invalidate();
}

void CImagePro20210797View::OnPixelHistoEq() // 히스토그램 평활화
{
	CImagePro20210797Doc* pDoc = GetDocument();
	
	int x, y, i, k, r, g, b;
	int hist[256] = { 0 };

	int sum[256] = { 0 };

	int acc_hist = 0;

	int N = pDoc->lmageHeight * pDoc->lmageWidth;

	//초기화
	if (pDoc->Depth == 1)
	{
		for (k = 0; k < 256; k++)	hist[k] = 0;
	}
	else
	{
		AfxMessageBox("히스토그램 평활화는 흑백만 가능합니다");
		return;
	}

	//명암의 빈도수 조사
	for (y = 0; y < pDoc->lmageHeight; y++)
		for (x = 0; x < pDoc->lmageWidth; x++)
		{
			if (pDoc->Depth == 1)
			{
				k = pDoc->InputImage[y][x];
				hist[k]++;
			}
			else
			{
				AfxMessageBox("히스토그램 평활화는 흑백만 가능합니다");
				return;
			}
		}

	//누적분포 계산
	acc_hist = 0;
	for (k = 0; k < 256; k++)
	{
		if (pDoc->Depth == 1)
		{
			acc_hist += hist[k];
			sum[k] = acc_hist;
		}
		else
		{
			AfxMessageBox("히스토그램 평활화는 흑백만 가능합니다");
			return;
		}
	}

	//변환값 계산
	{
		for (y = 0; y < pDoc->lmageHeight; y++)
			for (x = 0; x < pDoc->lmageWidth; x++)
			{
				if (pDoc->Depth == 1)
				{
					k = pDoc->InputImage[y][x];
					pDoc->ResultImage[y][x] = (float)sum[k] / N * 255;		//K → value
				}
				else
				{
					AfxMessageBox("히스토그램 평활화는 흑백만 가능합니다");
					return;
				}
			}
		Invalidate();
	}
}

void CImagePro20210797View::OnPixelContrastStretch() // 명암대비 스트레칭
{
	CImagePro20210797Doc* pDoc = GetDocument();

	int x, y, r, g, b;
	int minVal = 255, maxVal = 0;

	for (y = 0; y < pDoc->lmageHeight; y++) {
		for (x = 0; x < pDoc->lmageWidth; x++) {
			if (pDoc->Depth == 1)
			{
				int pixel = pDoc->InputImage[y][x];
				if (pixel < minVal) minVal = pixel;
				if (pixel > maxVal) maxVal = pixel;
			}
			else
			{
				AfxMessageBox("명암 대비 스트레칭은 흑백만 가능합니다");
				return;
			}
		}
	}

	// 명암 대비 스트레칭
	for (y = 0; y < pDoc->lmageHeight; y++) {
		for (x = 0; x < pDoc->lmageWidth; x++) {
			if (pDoc->Depth == 1)
			{
				int pixel = pDoc->InputImage[y][x];
				pDoc->ResultImage[y][x] = (pixel - minVal) * 255 / (maxVal - minVal);
			}
			else
			{
				AfxMessageBox("명암 대비 스트레칭은 흑백만 가능합니다");
				return;
			}
		}
	}

	Invalidate();
}

void CImagePro20210797View::OnPixelBinarization() // 이진화
{
    CImagePro20210797Doc* pDoc = GetDocument();

    int threshold = 140;
    int x, y;

    if (pDoc->Depth == 1)  
    {
        for (y = 0; y < pDoc->lmageHeight; y++)
            for (x = 0; x < pDoc->lmageWidth; x++)
            {
                if (pDoc->InputImage[y][x] > threshold)
                    pDoc->ResultImage[y][x] = 255;
                else
                    pDoc->ResultImage[y][x] = 0;
            }
    }

    else if (pDoc->Depth == 3)  
    {
        for (y = 0; y < pDoc->lmageHeight; y++)
            for (x = 0; x < pDoc->lmageWidth; x++)
            {
                // RGB 값을 평균 내어 그레이스케일 변환 후 이진화
                int gray = (pDoc->InputImage[y][x * 3] + 
                            pDoc->InputImage[y][x * 3 + 1] + 
                            pDoc->InputImage[y][x * 3 + 2]) / 3;
                
                int binarizedValue = (gray > threshold) ? 255 : 0;
                
                // 모든 채널에 같은 값을 적용 (흑백 처리)
                pDoc->ResultImage[y][x * 3] = binarizedValue;
                pDoc->ResultImage[y][x * 3 + 1] = binarizedValue;
                pDoc->ResultImage[y][x * 3 + 2] = binarizedValue;
            }
    }

    Invalidate();
}

void CImagePro20210797View::OnPixelTwoImageAdd() // 두 영상의 덧셈
{
	CImagePro20210797Doc* pDoc = GetDocument();

	CFile file;
	CFileDialog dlg(TRUE);

	int x, y, c;
	int value;

	if (dlg.DoModal() == IDOK)
	{
		file.Open(dlg.GetPathName(), CFile::modeRead);
		CArchive ar(&file, CArchive::load);
		pDoc->LoadSecondImageFile(ar);
		file.Close();

		if (pDoc->Depth == 1)
		{
			for (y = 0; y < pDoc->lmageHeight; y++)
				for (x = 0; x < pDoc->lmageWidth; x++)
				{
					value = 0.5 * pDoc->InputImage[y][x] + 0.5 * pDoc->InputImage2[y][x];

					if (value > 255) value = 255;
					else if (value < 0) value = 0;

					pDoc->ResultImage[y][x] = value;
				}
		}

		else if (pDoc->Depth == 3)
		{
			for (y = 0; y < pDoc->lmageHeight; y++)
				for (x = 0; x < pDoc->lmageWidth; x++)
				{
					for (int c = 0; c < 3; c++)	// RGB 각 채널별 연산
					{
						value = 0.5 * pDoc->InputImage[y][x * 3 + c] + 0.5 * pDoc->InputImage2[y][x * 3 + c];

						if (value > 255) value = 255;
						else if (value < 0) value = 0;

						pDoc->ResultImage[y][x * 3 + c] = value;
					}
				}
		}
	}

	Invalidate();
}

void CImagePro20210797View::OnPixelTwoImageSub() // 두 영상의 뺄셈
{
	CImagePro20210797Doc* pDoc = GetDocument();

	CFile file;
	CFileDialog dlg(TRUE);

	int x, y, c;
	int value;

	if (dlg.DoModal() == IDOK)
	{
		file.Open(dlg.GetPathName(), CFile::modeRead);
		CArchive ar(&file, CArchive::load);
		pDoc->LoadSecondImageFile(ar);
		file.Close();

		if (pDoc->Depth == 1)
		{
			for (y = 0; y < pDoc->lmageHeight; y++)
				for (x = 0; x < pDoc->lmageWidth; x++)
				{
					value = abs(pDoc->InputImage[y][x] - pDoc->InputImage2[y][x]);

					if (value > 40) value = 255;
					else value = 0;

					pDoc->ResultImage[y][x] = value;
				}
		}

		else if (pDoc->Depth == 3)
		{
			for (y = 0; y < pDoc->lmageHeight; y++)
				for (x = 0; x < pDoc->lmageWidth; x++)
				{
					for (int c = 0; c < 3; c++)	// RGB 각 채널별 연산
					{
						value = abs(pDoc->InputImage[y][x * 3 + c] - pDoc->InputImage2[y][x * 3 + c]);

						if (value > 40) value = 255;
						else value = 0;

						pDoc->ResultImage[y][x * 3 + c] = value;
					}
				}
		}
	}

	Invalidate();
}

void CImagePro20210797View::OnRegionMeaning()	// 흐림화
{
	CImagePro20210797Doc* pDoc = GetDocument();

	float kernel[3][3] = {	// 가로 3, 세로 3
							{1 / 9.0, 1 / 9.0, 1 / 9.0} ,
							{1 / 9.0, 1 / 9.0, 1 / 9.0},
							{1 / 9.0, 1 / 9.0, 1 / 9.0}
						};

	Convolve(pDoc->InputImage, pDoc->ResultImage, pDoc->lmageWidth, pDoc->lmageHeight, kernel, 0, pDoc->Depth);

	Invalidate();
}

void CImagePro20210797View::OnRegionSharpening()	// 선명화
{
	CImagePro20210797Doc* pDoc = GetDocument();

	float kernel[3][3] = {
							{0, -1,  0} ,
							{-1, 5, -1},
							{0, -1,  0}
	};

	Convolve(pDoc->InputImage, pDoc->ResultImage, pDoc->lmageWidth, pDoc->lmageHeight, kernel, 0, pDoc->Depth);

	Invalidate();
}

void CImagePro20210797View::OnResionEmbossing()	// 엠보싱
{
	CImagePro20210797Doc* pDoc = GetDocument();

	float kernel[3][3] = {
							{-1, 0, 0} ,
							{0,  0, 0},
							{0,  0, 1}
	};

	Convolve(pDoc->InputImage, pDoc->ResultImage, pDoc->lmageWidth, pDoc->lmageHeight, kernel, 128, pDoc->Depth);

	Invalidate();
}

void CImagePro20210797View::Convolve(unsigned char** inImage, unsigned char** outImage, int cols, int rows, float mask[][3], int bias, int Depth)
{
	int x, y, i, j;
	int sum, rsum, gsum, bsum;

	for (y = 1; y < rows - 1; y++)	// 3*3이기 때문에 y = 1, 5*5는 y = 3
		for (x = 1; x < cols - 1; x++)
		{
			if(Depth == 1)
			{
				sum = 0;
				for (j = 0; j < 3; j++)
					for (i = 0; i < 3; i++)
						sum += (inImage[y + j - 1][x + i - 1] * mask[j][i]);	// i는 x 위치에 대응, j는 y 위치에 대응

				sum = sum + bias;

				if (sum > 255)		sum = 255;	// 양수일 경우
				else if (sum < 0)	sum = 0;	// 음수일 경우
					
				outImage[y][x] = sum;
			}
			else
			{
				rsum = 0; gsum = 0; bsum = 0;
				for (j = 0; j < 3; j++)
					for (i = 0; i < 3; i++)
					{
						rsum += (inImage[y + j - 1][3 * (x + i - 1) + 0] * mask[j][i]);
						gsum += (inImage[y + j - 1][3 * (x + i - 1) + 1] * mask[j][i]);
						bsum += (inImage[y + j - 1][3 * (x + i - 1) + 2] * mask[j][i]);
					}

				rsum += bias;
				gsum += bias;
				bsum += bias;

				if (rsum > 255)		rsum = 255;	// r
				else if (rsum < 0)	rsum = 0;

				if (gsum > 255)		gsum = 255;	// g
				else if (gsum < 0)	gsum = 0;

				if (bsum > 255)		bsum = 255;	// b
				else if (bsum < 0)	bsum = 0;

				outImage[y][3 * x + 0] = rsum;
				outImage[y][3 * x + 1] = gsum;
				outImage[y][3 * x + 2] = bsum;
			}
		}
}
void CImagePro20210797View::OnRegionPrewitt()	// 경계성 검출 (Prewitt)
{
	CImagePro20210797Doc* pDoc = GetDocument();

	float maskH[3][3] = {
		{-1, -1, -1},
		{0,   0,  0},
		{1,   1,  1}
	};

	float maskV[3][3] = {
	{1, 0, -1},
	{1, 0, -1},
	{1, 0, -1}
	};

	unsigned char** Er, ** Ec;
	int x, y, i;
	int value;
	int rvalue, gvalue, bvalue;

	// 메모리생성
	// 기억장소 할당
	
	Er = (unsigned char**)malloc(pDoc->lmageHeight * sizeof(unsigned char*));
	Ec = (unsigned char**)malloc(pDoc->lmageHeight * sizeof(unsigned char*));
	for (int i = 0; i < pDoc->lmageHeight; i++)
	{
		Er[i] = (unsigned char*)malloc(pDoc->lmageWidth * pDoc->Depth);
		Ec[i] = (unsigned char*)malloc(pDoc->lmageWidth * pDoc->Depth);
	}

	Convolve(pDoc->InputImage, Er, pDoc->lmageWidth, pDoc->lmageHeight, maskH, 128, pDoc->Depth);
	Convolve(pDoc->InputImage, Ec, pDoc->lmageWidth, pDoc->lmageHeight, maskV, 128, pDoc->Depth);

	for (y = 0; y < pDoc->lmageHeight; y++)
		for (x = 0; x < pDoc->lmageWidth; x++)
		{
			if (pDoc->Depth == 1)
			{
				value = sqrt((Er[y][x] - 128) * (Er[y][x] - 128) + (Ec[y][x] - 128) * (Ec[y][x] - 128));
				if (value > 255)		  value = 255;
				else if (value < 0)	      value = 0;
				pDoc->ResultImage[y][x] = value;
			}
			else
			{
				rvalue = sqrt((Er[y][3 * x + 0] - 128) * (Er[y][3 * x + 0] - 128) + (Ec[y][3 * x + 0] - 128) * (Ec[y][3 * x + 0] - 128));
				if (rvalue > 255)		  rvalue = 255;
				else if (rvalue < 0)	      rvalue = 0;
				// pDoc->ResultImage[y][3 * x + 0] = value;

				gvalue = sqrt((Er[y][3 * x + 1] - 128) * (Er[y][3 * x + 1] - 128) + (Ec[y][3 * x + 1] - 128) * (Ec[y][3 * x + 1] - 128));
				if (gvalue > 255)		  gvalue = 255;
				else if (gvalue < 0)	      gvalue = 0;
				// pDoc->ResultImage[y][3 * x + 1] = value;

				bvalue = sqrt((Er[y][3 * x + 2] - 128) * (Er[y][3 * x + 2] - 128) + (Ec[y][3 * x + 2] - 128) * (Ec[y][3 * x + 2] - 128));
				if (bvalue > 255)		  bvalue = 255;
				else if (bvalue < 0)	      bvalue = 0;
				// pDoc->ResultImage[y][3 * x + 2] = value;

				value = sqrt(rvalue * rvalue + gvalue * gvalue + bvalue * bvalue);
				if (value > 255)	value = 255;
				else if (value < 0)	value = 0;

				pDoc->ResultImage[y][3 * x + 0] = value;
				pDoc->ResultImage[y][3 * x + 1] = value;
				pDoc->ResultImage[y][3 * x + 2] = value;
			}
		}

	for (i = 0; i < pDoc->lmageHeight; i++)
	{
		free(Er[i]);
		free(Ec[i]);
	}
	free(Er);
	free(Ec);

	Invalidate();
}

void CImagePro20210797View::OnResionRoberts()	// 경계성 검출 (Roberts)
{
	CImagePro20210797Doc* pDoc = GetDocument();

	float maskH[3][3] = {
	{-1, 0, 0},
	{0,  1, 0},
	{0,  0, 0}
	};

	float maskV[3][3] = {
	{0, 0, -1},
	{0, 1,  0},
	{0, 0,  0}
	};

	unsigned char** Er, ** Ec;
	int x, y, i;
	int value;
	int rvalue, gvalue, bvalue;

	// 메모리생성
	// 기억장소 할당

	Er = (unsigned char**)malloc(pDoc->lmageHeight * sizeof(unsigned char*));
	Ec = (unsigned char**)malloc(pDoc->lmageHeight * sizeof(unsigned char*));
	for (int i = 0; i < pDoc->lmageHeight; i++)
	{
		Er[i] = (unsigned char*)malloc(pDoc->lmageWidth * pDoc->Depth);
		Ec[i] = (unsigned char*)malloc(pDoc->lmageWidth * pDoc->Depth);
	}

	Convolve(pDoc->InputImage, Er, pDoc->lmageWidth, pDoc->lmageHeight, maskH, 128, pDoc->Depth);
	Convolve(pDoc->InputImage, Ec, pDoc->lmageWidth, pDoc->lmageHeight, maskV, 128, pDoc->Depth);

	for (y = 0; y < pDoc->lmageHeight; y++)
		for (x = 0; x < pDoc->lmageWidth; x++)
		{
			if (pDoc->Depth == 1)
			{
				value = sqrt((Er[y][x] - 128) * (Er[y][x] - 128) + (Ec[y][x] - 128) * (Ec[y][x] - 128));
				if (value > 255)		  value = 255;
				else if (value < 0)	      value = 0;
				pDoc->ResultImage[y][x] = value;
			}
			else
			{
				rvalue = sqrt((Er[y][3 * x + 0] - 128) * (Er[y][3 * x + 0] - 128) + (Ec[y][3 * x + 0] - 128) * (Ec[y][3 * x + 0] - 128));
				if (rvalue > 255)		  rvalue = 255;
				else if (rvalue < 0)	      rvalue = 0;
				// pDoc->ResultImage[y][3 * x + 0] = value;

				gvalue = sqrt((Er[y][3 * x + 1] - 128) * (Er[y][3 * x + 1] - 128) + (Ec[y][3 * x + 1] - 128) * (Ec[y][3 * x + 1] - 128));
				if (gvalue > 255)		  gvalue = 255;
				else if (gvalue < 0)	      gvalue = 0;
				// pDoc->ResultImage[y][3 * x + 1] = value;

				bvalue = sqrt((Er[y][3 * x + 2] - 128) * (Er[y][3 * x + 2] - 128) + (Ec[y][3 * x + 2] - 128) * (Ec[y][3 * x + 2] - 128));
				if (bvalue > 255)		  bvalue = 255;
				else if (bvalue < 0)	      bvalue = 0;
				// pDoc->ResultImage[y][3 * x + 2] = value;

				value = sqrt(rvalue * rvalue + gvalue * gvalue + bvalue * bvalue);
				if (value > 255)	value = 255;
				else if (value < 0)	value = 0;

				pDoc->ResultImage[y][3 * x + 0] = value;
				pDoc->ResultImage[y][3 * x + 1] = value;
				pDoc->ResultImage[y][3 * x + 2] = value;
			}
		}

	for (i = 0; i < pDoc->lmageHeight; i++)
	{
		free(Er[i]);
		free(Ec[i]);
	}
	free(Er);
	free(Ec);

	Invalidate();
}
void CImagePro20210797View::OnResionSobel()	// 경계선 검출 (Sobel)
{
	CImagePro20210797Doc* pDoc = GetDocument();

	float maskH[3][3] = {
		{-1, -2, -1},
		{0,   0,  0},
		{1,   2,  1}
	};

	float maskV[3][3] = {
	{1, 0, -1},
	{2, 0, -2},
	{1, 0, -1}
	};

	unsigned char** Er, ** Ec;
	int x, y, i;
	int value;
	int rvalue, gvalue, bvalue;

	// 메모리생성
	// 기억장소 할당

	Er = (unsigned char**)malloc(pDoc->lmageHeight * sizeof(unsigned char*));
	Ec = (unsigned char**)malloc(pDoc->lmageHeight * sizeof(unsigned char*));
	for (int i = 0; i < pDoc->lmageHeight; i++)
	{
		Er[i] = (unsigned char*)malloc(pDoc->lmageWidth * pDoc->Depth);
		Ec[i] = (unsigned char*)malloc(pDoc->lmageWidth * pDoc->Depth);
	}

	Convolve(pDoc->InputImage, Er, pDoc->lmageWidth, pDoc->lmageHeight, maskH, 128, pDoc->Depth);
	Convolve(pDoc->InputImage, Ec, pDoc->lmageWidth, pDoc->lmageHeight, maskV, 128, pDoc->Depth);

	for (y = 0; y < pDoc->lmageHeight; y++)
		for (x = 0; x < pDoc->lmageWidth; x++)
		{
			if (pDoc->Depth == 1)
			{
				value = sqrt((Er[y][x] - 128) * (Er[y][x] - 128) + (Ec[y][x] - 128) * (Ec[y][x] - 128));
				if (value > 255)		  value = 255;
				else if (value < 0)	      value = 0;
				pDoc->ResultImage[y][x] = value;
			}
			else
			{
				rvalue = sqrt((Er[y][3 * x + 0] - 128) * (Er[y][3 * x + 0] - 128) + (Ec[y][3 * x + 0] - 128) * (Ec[y][3 * x + 0] - 128));
				if (rvalue > 255)		  rvalue = 255;
				else if (rvalue < 0)	  rvalue = 0;
				// pDoc->ResultImage[y][3 * x + 0] = value;

				gvalue = sqrt((Er[y][3 * x + 1] - 128) * (Er[y][3 * x + 1] - 128) + (Ec[y][3 * x + 1] - 128) * (Ec[y][3 * x + 1] - 128));
				if (gvalue > 255)		  gvalue = 255;
				else if (gvalue < 0)	  gvalue = 0;
				// pDoc->ResultImage[y][3 * x + 1] = value;

				bvalue = sqrt((Er[y][3 * x + 2] - 128) * (Er[y][3 * x + 2] - 128) + (Ec[y][3 * x + 2] - 128) * (Ec[y][3 * x + 2] - 128));
				if (bvalue > 255)		  bvalue = 255;
				else if (bvalue < 0)	  bvalue = 0;
				// pDoc->ResultImage[y][3 * x + 2] = value;

				value = sqrt(rvalue * rvalue + gvalue * gvalue + bvalue * bvalue);
				if (value > 255)	value = 255;
				else if (value < 0)	value = 0;

				pDoc->ResultImage[y][3 * x + 0] = value;
				pDoc->ResultImage[y][3 * x + 1] = value;
				pDoc->ResultImage[y][3 * x + 2] = value;
			}
		}

	for (i = 0; i < pDoc->lmageHeight; i++)
	{
		free(Er[i]);
		free(Ec[i]);
	}
	free(Er);
	free(Ec);

	Invalidate();
}

void CImagePro20210797View::OnResionAverageFiltering()	// 평균값 필터링
{
	CImagePro20210797Doc* pDoc = GetDocument();

	float kernel[3][3] = {
	{1 / 9.0, 1 / 9.0, 1 / 9.0},
	{1 / 9.0, 1 / 9.0, 1 / 9.0},
	{1 / 9.0, 1 / 9.0, 1 / 9.0}
	};
	Convolve(pDoc->InputImage, pDoc->ResultImage, pDoc->lmageWidth, pDoc->lmageHeight, kernel, 0, pDoc->Depth);

	Invalidate();
}

void CImagePro20210797View::OnResionMedianFiltering()	// 중간값 필터링
{
	CImagePro20210797Doc* pDoc = GetDocument();

	int n[9];
	int x, y, i, j;
	int temp;

	for (y = 1; y < pDoc->lmageHeight - 1; y++)
		for (x = 1; x < pDoc->lmageWidth - 1; x++)
		{
			if (pDoc->Depth == 1)
			{
				n[0] = pDoc->InputImage[y - 1][x - 1];
				n[1] = pDoc->InputImage[y - 1][x - 0];
				n[2] = pDoc->InputImage[y - 1][x + 1];
				n[3] = pDoc->InputImage[y - 0][x - 1];
				n[4] = pDoc->InputImage[y - 0][x - 0];
				n[5] = pDoc->InputImage[y - 0][x + 1];
				n[6] = pDoc->InputImage[y + 1][x - 1];
				n[7] = pDoc->InputImage[y + 1][x - 0];
				n[8] = pDoc->InputImage[y + 1][x + 1];

				// Sorting 선택정렬, 오름차순
				for (i = 8; i > 0; i--)
					for (j = 0; j < i; j++)
					{
						if (n[j] > n[j + 1])
						{
							temp = n[j + 1];
							n[j + 1] = n[j];
							n[j] = temp;
						}
					}

				pDoc->ResultImage[y][x] = n[4];
			}
			else
			{
				n[0] = pDoc->InputImage[y - 1][3 * (x - 1) + 0];
				n[1] = pDoc->InputImage[y - 1][3 * (x - 0) + 0];
				n[2] = pDoc->InputImage[y - 1][3 * (x + 1) + 0];
				n[3] = pDoc->InputImage[y - 0][3 * (x - 1) + 0];
				n[4] = pDoc->InputImage[y - 0][3 * (x - 0) + 0];
				n[5] = pDoc->InputImage[y - 0][3 * (x + 1) + 0];
				n[6] = pDoc->InputImage[y + 1][3 * (x - 1) + 0];
				n[7] = pDoc->InputImage[y + 1][3 * (x - 0) + 0];
				n[8] = pDoc->InputImage[y + 1][3 * (x + 1) + 0];

				// Sorting 선택정렬, 오름차순
				for (i = 8; i > 0; i--)
					for (j = 0; j < i; j++)
					{
						if (n[j] > n[j + 1])
						{
							temp = n[j + 1];
							n[j + 1] = n[j];
							n[j] = temp;
						}
					}

				pDoc->ResultImage[y][3 * x + 0] = n[4];

				n[0] = pDoc->InputImage[y - 1][3 * (x - 1) + 1];
				n[1] = pDoc->InputImage[y - 1][3 * (x - 0) + 1];
				n[2] = pDoc->InputImage[y - 1][3 * (x + 1) + 1];
				n[3] = pDoc->InputImage[y - 0][3 * (x - 1) + 1];
				n[4] = pDoc->InputImage[y - 0][3 * (x - 0) + 1];
				n[5] = pDoc->InputImage[y - 0][3 * (x + 1) + 1];
				n[6] = pDoc->InputImage[y + 1][3 * (x - 1) + 1];
				n[7] = pDoc->InputImage[y + 1][3 * (x - 0) + 1];
				n[8] = pDoc->InputImage[y + 1][3 * (x + 1) + 1];

				// Sorting 선택정렬, 오름차순
				for (i = 8; i > 0; i--)
					for (j = 0; j < i; j++)
					{
						if (n[j] > n[j + 1])
						{
							temp = n[j + 1];
							n[j + 1] = n[j];
							n[j] = temp;
						}
					}

				pDoc->ResultImage[y][3 * x + 1] = n[4];

				n[0] = pDoc->InputImage[y - 1][3 * (x - 1) + 2];
				n[1] = pDoc->InputImage[y - 1][3 * (x - 0) + 2];
				n[2] = pDoc->InputImage[y - 1][3 * (x + 1) + 2];
				n[3] = pDoc->InputImage[y - 0][3 * (x - 1) + 2];
				n[4] = pDoc->InputImage[y - 0][3 * (x - 0) + 2];
				n[5] = pDoc->InputImage[y - 0][3 * (x + 1) + 2];
				n[6] = pDoc->InputImage[y + 1][3 * (x - 1) + 2];
				n[7] = pDoc->InputImage[y + 1][3 * (x - 0) + 2];
				n[8] = pDoc->InputImage[y + 1][3 * (x + 1) + 2];

				// Sorting 선택정렬, 오름차순
				for (i = 8; i > 0; i--)
					for (j = 0; j < i; j++)
					{
						if (n[j] > n[j + 1])
						{
							temp = n[j + 1];
							n[j + 1] = n[j];
							n[j] = temp;
						}
					}

				pDoc->ResultImage[y][3 * x + 2] = n[4];
			}

		}
	Invalidate();
}

void CImagePro20210797View::OnMopologyColorToGray()
{
	CImagePro20210797Doc* pDoc = GetDocument();

	int x, y, gray;
	
	if (pDoc->Depth == 1)	// 흑백일 시 동작 X
		return;

		for (y = 0; y < pDoc->lmageHeight; y++)
			for (x = 0; x < pDoc->lmageWidth; x++)
			{
				gray = (pDoc->InputImage[y][3 * x + 0] + pDoc->InputImage[y][3 * x + 1] + pDoc->InputImage[y][3 * x + 2]) / 3;

				pDoc->InputImage[y][3 * x + 0] = gray;
				pDoc->InputImage[y][3 * x + 1] = gray;
				pDoc->InputImage[y][3 * x + 2] = gray;
			}
	Invalidate();
}

void CImagePro20210797View::OnMopologyBinarization()
{
	CImagePro20210797Doc* pDoc = GetDocument();

	int threshold = 70;
	int x, y;

	for (y = 0; y < pDoc->lmageHeight; y++)
		for (x = 0; x < pDoc->lmageWidth; x++)
		{
			if (pDoc->Depth == 1)
			{

				if (pDoc->InputImage[y][x] >= threshold)
					pDoc->InputImage[y][x] = 255;

				else
					pDoc->InputImage[y][x] = 0;
			}
			else
			{
				if (pDoc->InputImage[y][3 * x + 0] >= threshold)
				{
					pDoc->InputImage[y][3 * x + 0] = 255;
					pDoc->InputImage[y][3 * x + 1] = 255;
					pDoc->InputImage[y][3 * x + 2] = 255;
				}
				else
				{
					pDoc->InputImage[y][3 * x + 0] = 0;
					pDoc->InputImage[y][3 * x + 1] = 0;
					pDoc->InputImage[y][3 * x + 2] = 0;
				}
			}
		}
	Invalidate();
}

void CImagePro20210797View::OnMopologyErosion()	// 최솟값 필터
{
	CImagePro20210797Doc* pDoc = GetDocument();

	int x, y;
	int min, rmin, gmin, bmin;

	for (y = 1; y < pDoc->lmageHeight - 1; y++)
		for (x = 1; x < pDoc->lmageWidth - 1; x++)	// 1로 해야지 주변 9개를 가져올 수 있음
		{
			if (pDoc->Depth == 1)
			{
				min = 255;
				for (int j = -1; j <= 1; j++)
					for (int i = -1; i <= 1; i++)
					{
						if (pDoc->InputImage[y + j][x + i] < min)
							min = pDoc->InputImage[y + j][x + i];
					}
				pDoc->ResultImage[y][x] = min;
			}
			else
			{
				rmin = 255;
				gmin = 255;
				bmin = 255;

				for (int j = -1; j <= 1; j++)
					for (int i = -1; i <= 1; i++)
					{
						if (pDoc->InputImage[y + j][3 * (x + i) + 0] < rmin)
							rmin = pDoc->InputImage[y + j][3 * (x + i) + 0];

						if (pDoc->InputImage[y + j][3 * (x + i) + 1] < gmin)
							gmin = pDoc->InputImage[y + j][3 * (x + i) + 1];

						if (pDoc->InputImage[y + j][3 * (x + i) + 2] < bmin)
							bmin = pDoc->InputImage[y + j][3 * (x + i) + 2];
					}
				pDoc->ResultImage[y][3 * x + 0] = rmin;
				pDoc->ResultImage[y][3 * x + 1] = gmin;
				pDoc->ResultImage[y][3 * x + 2] = bmin;
			}
			Invalidate();
		}
}
void CImagePro20210797View::OnMopologyDialation()
{
	CImagePro20210797Doc* pDoc = GetDocument();

	int x, y;
	int max, rmax, gmax, bmax;

	for (y = 1; y < pDoc->lmageHeight - 1; y++)
		for (x = 1; x < pDoc->lmageWidth - 1; x++)	// 1로 해야지 주변 9개를 가져올 수 있음
		{
			if (pDoc->Depth == 1)
			{
				max = 0;
				for (int j = -1; j <= 1; j++)
					for (int i = -1; i <= 1; i++)
					{
						if (pDoc->InputImage[y + j][x + i] > max)
							max = pDoc->InputImage[y + j][x + i];
					}
				pDoc->ResultImage[y][x] = max;
			}
			else
			{
				rmax = 0;
				gmax = 0;
				bmax = 0;

				for (int j = -1; j <= 1; j++)
					for (int i = -1; i <= 1; i++)
					{
						if (pDoc->InputImage[y + j][3 * (x + i) + 0] > rmax)
							rmax = pDoc->InputImage[y + j][3 * (x + i) + 0];

						if (pDoc->InputImage[y + j][3 * (x + i) + 1] > gmax)
							gmax = pDoc->InputImage[y + j][3 * (x + i) + 1];

						if (pDoc->InputImage[y + j][3 * (x + i) + 2] > bmax)
							bmax = pDoc->InputImage[y + j][3 * (x + i) + 2];
					}
				pDoc->ResultImage[y][3 * x + 0] = rmax;
				pDoc->ResultImage[y][3 * x + 1] = gmax;
				pDoc->ResultImage[y][3 * x + 2] = bmax;
			}
			Invalidate();
		}
}

void CImagePro20210797View::CopyResultToInput()
{
	CImagePro20210797Doc* pDoc = GetDocument();

	int x, y;

	for (y = 0; y < pDoc->lmageHeight; y++)
		for (x = 0; x < pDoc->lmageWidth * pDoc->Depth; x++)
		{
			pDoc->InputImage[y][x] = pDoc->ResultImage[y][x];
		}
}

void CImagePro20210797View::OnMopologyOpening()
{
	OnMopologyErosion();
	CopyResultToInput();
	OnMopologyErosion();
	CopyResultToInput();
	OnMopologyErosion();
	
	CopyResultToInput();	// resultImg
	OnMopologyDialation();
	CopyResultToInput();
	OnMopologyDialation();
	CopyResultToInput();
	OnMopologyDialation();	// resultImg
}

void CImagePro20210797View::OnMopologyClosing()
{
	OnMopologyDialation();
	CopyResultToInput();
	OnMopologyDialation();
	CopyResultToInput();
	OnMopologyDialation();	// resultImg

	CopyResultToInput();
	OnMopologyErosion();
	CopyResultToInput();
	OnMopologyErosion();
	CopyResultToInput();
	OnMopologyErosion();	// resultImg
}

void CImagePro20210797View::OnGeometryZoominPixelCopy()
{
	CImagePro20210797Doc* pDoc = GetDocument();

	int x, y, i;
	int scale_x = 2;
	int scale_y = 3;

	if (pDoc->gResultImage != NULL)
	{
		for (i = 0; i < pDoc->glmageHeight; i++)
			free(pDoc->gResultImage[i]);
		free(pDoc->gResultImage);
	}

	pDoc->glmageWidth = pDoc->lmageWidth * scale_x;
	pDoc->glmageHeight = pDoc->lmageHeight * scale_y;

	// 기억장소 할당
	pDoc->gResultImage = (unsigned char**)malloc(pDoc->glmageHeight * sizeof(unsigned char*));
	for (int i = 0; i < pDoc->glmageHeight; i++)
	{
		pDoc->gResultImage[i] = (unsigned char*)malloc(pDoc->glmageWidth * pDoc->Depth);
	}
/*
	// 전방향 사상
	for (y = 0; y < pDoc->lmageHeight; y++)
		for (x = 0; x < pDoc->lmageWidth; x++)
		{
			for (int j = 0; j > scale_y; j++)
				for (int i = 0; i < scale_x; i++)
				{
					if (pDoc->Depth == 1)
						pDoc->gResultImage[y * scale_y + j][x * scale_x + i] = pDoc->InputImage[y][x];
					else
					{
						pDoc->gResultImage[y * scale_y + j][3 * (x * scale_x + i) + 0] = pDoc->InputImage[y][3 * x + 0];
						pDoc->gResultImage[y * scale_y + j][3 * (x * scale_x + i) + 1] = pDoc->InputImage[y][3 * x + 1];
						pDoc->gResultImage[y * scale_y + j][3 * (x * scale_x + i) + 2] = pDoc->InputImage[y][3 * x + 2];
					}
				}
*/
	// 역방향 사상
	for (y = 0; y < pDoc->glmageHeight; y++)
		for (x = 0; x < pDoc->glmageWidth; x++)
		{
			if (pDoc->Depth == 1)
				pDoc->gResultImage[y][x] = pDoc->InputImage[y / scale_y][x / scale_x];
			else
			{
				pDoc->gResultImage[y][3 * x + 0] = pDoc->InputImage[y / scale_y][3 * (x / scale_x) + 0];
				pDoc->gResultImage[y][3 * x + 1] = pDoc->InputImage[y / scale_y][3 * (x / scale_x) + 1];
				pDoc->gResultImage[y][3 * x + 2] = pDoc->InputImage[y / scale_y][3 * (x / scale_x) + 2];
			}
		}

	Invalidate();
}

void CImagePro20210797View::OnGeometryZoominBilinearInterpolation()
{
	CImagePro20210797Doc* pDoc = GetDocument();

	int x, y, i;
	float scale_x = 1.5;
	float scale_y = 1.3;
	float src_x, src_y;
	float alpha, beta;
	int Ax, Ay, Bx, By, Cx, Cy, Dx, Dy;
	int E, F;

	if (pDoc->gResultImage != NULL)
	{
		for (i = 0; i < pDoc->glmageHeight; i++)
			free(pDoc->gResultImage[i]);
		free(pDoc->gResultImage);
	}

	pDoc->glmageWidth = pDoc->lmageWidth * scale_x;
	pDoc->glmageHeight = pDoc->lmageHeight * scale_y;

	// 기억장소 할당
	pDoc->gResultImage = (unsigned char**)malloc(pDoc->glmageHeight * sizeof(unsigned char*));
	for (int i = 0; i < pDoc->glmageHeight; i++)
	{
		pDoc->gResultImage[i] = (unsigned char*)malloc(pDoc->glmageWidth * pDoc->Depth);
	}

	// 역방향 사상
	for (y = 0; y < pDoc->glmageHeight; y++)
		for (x = 0; x < pDoc->glmageWidth; x++)
		{
			src_x = x / scale_x;
			src_y = y / scale_y;

			alpha = src_x - (int)src_x;
			beta = src_y - (int)src_y;

			Ax = (int)src_x;
			Ay = (int)src_y;
			Bx = Ax + 1;
			By = Ay;
			Cx = Ax;
			Cy = Ay + 1;
			Dx = Ax + 1;
			Dy = Ay + 1;

			if (Bx > pDoc->lmageWidth - 1)	Bx = pDoc->lmageWidth - 1;
			if (Cy > pDoc->lmageHeight - 1)	Cy = pDoc->lmageHeight - 1;
			if (Dx > pDoc->lmageWidth - 1)	Dx = pDoc->lmageWidth - 1;
			if (Dy > pDoc->lmageHeight - 1)	Dy = pDoc->lmageHeight - 1;

			if (pDoc->Depth == 1)
			{
				E = (1 - alpha) * pDoc->InputImage[Ay][Ax] + alpha * pDoc->InputImage[By][Bx];
				F = (1 - alpha) * pDoc->InputImage[Cy][Cx] + alpha * pDoc->InputImage[Dy][Dx];
				pDoc->gResultImage[y][x] = (1 - beta) * E + beta * F;
			}
			else
			{
				E = (1 - alpha) * pDoc->InputImage[Ay][3 * Ax + 0] + alpha * pDoc->InputImage[By][3 * Bx + 0];
				F = (1 - alpha) * pDoc->InputImage[Cy][3 * Cx + 0] + alpha * pDoc->InputImage[Dy][3 * Dx + 0];
				pDoc->gResultImage[y][3 * x + 0] = (1 - beta) * E + beta * F;

				E = (1 - alpha) * pDoc->InputImage[Ay][3 * Ax + 1] + alpha * pDoc->InputImage[By][3 * Bx + 1];
				F = (1 - alpha) * pDoc->InputImage[Cy][3 * Cx + 1] + alpha * pDoc->InputImage[Dy][3 * Dx + 1];
				pDoc->gResultImage[y][3 * x + 1] = (1 - beta) * E + beta * F;

				E = (1 - alpha) * pDoc->InputImage[Ay][3 * Ax + 2] + alpha * pDoc->InputImage[By][3 * Bx + 2];
				F = (1 - alpha) * pDoc->InputImage[Cy][3 * Cx + 2] + alpha * pDoc->InputImage[Dy][3 * Dx + 2];
				pDoc->gResultImage[y][3 * x + 2] = (1 - beta) * E + beta * F;
			}
		}

	Invalidate();
}

void CImagePro20210797View::OnGeometryZoomoutSubsampling()
{
	CImagePro20210797Doc* pDoc = GetDocument();

	int x, y, i;
	int scale_x = 2;
	int scale_y = 3;

	if (pDoc->gResultImage != NULL)
	{
		for (i = 0; i < pDoc->glmageHeight; i++)
			free(pDoc->gResultImage[i]);
		free(pDoc->gResultImage);
	}

	pDoc->glmageWidth = pDoc->lmageWidth / scale_x;
	pDoc->glmageHeight = pDoc->lmageHeight / scale_y;

	// 기억장소 할당
	pDoc->gResultImage = (unsigned char**)malloc(pDoc->glmageHeight * sizeof(unsigned char*));
	for (int i = 0; i < pDoc->glmageHeight; i++)
	{
		pDoc->gResultImage[i] = (unsigned char*)malloc(pDoc->glmageWidth * pDoc->Depth);
	}

	// 역방향 사상
	for (y = 0; y < pDoc->glmageHeight; y++)
		for (x = 0; x < pDoc->glmageWidth; x++)
		{
			if (pDoc->Depth == 1)
				pDoc->gResultImage[y][x] = pDoc->InputImage[y * scale_y][x * scale_x];
			else
			{
				pDoc->gResultImage[y][3 * x + 0] = pDoc->InputImage[y * scale_y][3 * (x * scale_x) + 0];
				pDoc->gResultImage[y][3 * x + 1] = pDoc->InputImage[y * scale_y][3 * (x * scale_x) + 1];
				pDoc->gResultImage[y][3 * x + 2] = pDoc->InputImage[y * scale_y][3 * (x * scale_x) + 2];
			}
		}

	Invalidate();
}

void CImagePro20210797View::OnGeometryZoomoutMeanSub()
{
	OnRegionMeaning();
	CopyResultToInput();
	OnGeometryZoomoutSubsampling();
}

void CImagePro20210797View::OnGeometryZoomoutAvg()
{
	CImagePro20210797Doc* pDoc = GetDocument();

	int x, y, i;
	int scale_x = 2;
	int scale_y = 3;
	int sum, rsum, gsum, bsum;
	int src_x, src_y;

	if (pDoc->gResultImage != NULL)
	{
		for (i = 0; i < pDoc->glmageHeight; i++)
			free(pDoc->gResultImage[i]);
		free(pDoc->gResultImage);
	}

	pDoc->glmageWidth = pDoc->lmageWidth / scale_x + 1;
	pDoc->glmageHeight = pDoc->lmageHeight / scale_y + 1;

	// 기억장소 할당
	pDoc->gResultImage = (unsigned char**)malloc(pDoc->glmageHeight * sizeof(unsigned char*));
	for (int i = 0; i < pDoc->glmageHeight; i++)
	{
		pDoc->gResultImage[i] = (unsigned char*)malloc(pDoc->glmageWidth * pDoc->Depth);
	}

	// 전방향 사상
	for (y = 0; y < pDoc->lmageHeight; y += scale_y)
		for (x = 0; x < pDoc->lmageWidth; x += scale_x)
		{
			if (pDoc->Depth == 1)
			{
				sum = 0;
				for (int j = 0; j < scale_y; j++)
					for (int i = 0; i < scale_x; i++)
					{
						src_x = x + i;
						src_y = y + j;
						if (src_x > pDoc->lmageWidth - 1)	src_x = pDoc->lmageWidth - 1;
						if (src_y > pDoc->lmageHeight - 1)	src_y = pDoc->lmageHeight - 1;

						sum += pDoc->InputImage[src_y][src_x];
					}
				pDoc->gResultImage[y / scale_y][x / scale_x] = sum / (scale_y * scale_x);
			}
			else
			{
				rsum = 0;	gsum = 0; bsum = 0;
				for (int j = 0; j < scale_y; j++)
					for (int i = 0; i < scale_x; i++)
					{
						src_x = x + i;
						src_y = y + j;
						if (src_x > pDoc->lmageWidth - 1)	src_x = pDoc->lmageWidth - 1;
						if (src_y > pDoc->lmageHeight - 1)	src_y = pDoc->lmageHeight - 1;

						rsum += pDoc->InputImage[src_y][3 * src_x + 0];
						gsum += pDoc->InputImage[src_y][3 * src_x + 1];
						bsum += pDoc->InputImage[src_y][3 * src_x + 2];
					}
				pDoc->gResultImage[y / scale_y][3 * (x / scale_x) + 0] = rsum / (scale_y * scale_x);
				pDoc->gResultImage[y / scale_y][3 * (x / scale_x) + 1] = gsum / (scale_y * scale_x);
				pDoc->gResultImage[y / scale_y][3 * (x / scale_x) + 2] = bsum / (scale_y * scale_x);
			}
		}

	Invalidate();
}

#define PI 3.1415926521

void CImagePro20210797View::OnGeometryRotation()
{
	CImagePro20210797Doc* pDoc = GetDocument();

	int angle = 30;	// degree 단위 양수: 반시계 / 음수: 시계

	int x, y, i;
	int Cx, Cy, Hy;
	int x_source, y_source;
	int xdiff, ydiff;

	CAngleInDialog dlg;
	dlg.m_iAngle = angle;
	if (dlg.DoModal() == IDCANCEL)
		return;

	angle = dlg.m_iAngle;
	float radian = PI / 180 * angle;	// PI = 3.1415926521

	if (pDoc->gResultImage != NULL)
	{
		for (int i = 0; i < pDoc->glmageHeight; i++)
			free(pDoc->gResultImage[i]);
		free(pDoc->gResultImage);
	}

	pDoc->glmageWidth = pDoc->lmageHeight * fabs(cos(PI / 2 - radian)) + pDoc->lmageWidth * fabs(cos(radian));
	pDoc->glmageHeight = pDoc->lmageHeight * fabs(cos(radian)) + pDoc->lmageWidth * fabs(cos(PI / 2 - radian));

	// 기억장소 할당
	pDoc->gResultImage = (unsigned char**)malloc(pDoc->glmageHeight * sizeof(unsigned char*));
	for (int i = 0; i < pDoc->glmageHeight; i++)
	{
		pDoc->gResultImage[i] = (unsigned char*)malloc(pDoc->glmageWidth * pDoc->Depth);
	}

	// 중심점
	Cx = pDoc->lmageWidth / 2;
	Cy = pDoc->lmageHeight / 2;

	// y의 마지막 좌표
	Hy = pDoc->lmageHeight - 1;

	xdiff = (pDoc->glmageWidth - pDoc->lmageWidth) / 2;
	ydiff = (pDoc->glmageHeight - pDoc->lmageHeight) / 2;

	for (y = -ydiff; y < pDoc->glmageHeight - ydiff; y++)
		for (x = -xdiff; x < pDoc->glmageWidth - xdiff; x++)
		{
			x_source = ((Hy - y) - Cy) * sin(radian) + (x - Cy) * cos(radian) + Cx;
			y_source = Hy - (((Hy - y) - Cy) * cos(radian) - (x - Cx) * sin(radian) + Cy);

			if (pDoc->Depth == 1)
			{
				if (x_source<0 || x_source>pDoc->lmageWidth - 1 ||	// x_source보다 크면 메모리 에러
					y_source<0 || y_source>pDoc->lmageHeight - 1)	// y_source보다 크면 메모리 에러
					pDoc->gResultImage[y + ydiff][x + xdiff] = 255;

				else
					pDoc->gResultImage[y + ydiff][x + xdiff] = pDoc->InputImage[y_source][x_source];
			}
			else
			{
				if (x_source<0 || x_source>pDoc->lmageWidth - 1 ||	// x_source보다 크면 메모리 에러
					y_source<0 || y_source>pDoc->lmageHeight - 1)	// y_source보다 크면 메모리 에러
				{
					pDoc->gResultImage[y + ydiff][3 * (x + xdiff) + 0] = 255;
					pDoc->gResultImage[y + ydiff][3 * (x + xdiff) + 1] = 255;
					pDoc->gResultImage[y + ydiff][3 * (x + xdiff) + 2] = 255;
				}
				else
				{
					pDoc->gResultImage[y + ydiff][3 * (x + xdiff) + 0] = pDoc->InputImage[y_source][3 * (x_source)+0];
					pDoc->gResultImage[y + ydiff][3 * (x + xdiff) + 1] = pDoc->InputImage[y_source][3 * (x_source)+1];
					pDoc->gResultImage[y + ydiff][3 * (x + xdiff) + 2] = pDoc->InputImage[y_source][3 * (x_source)+2];
				}
			}
		}


	Invalidate();
}

void CImagePro20210797View::OnGeometryMirror()
{
	CImagePro20210797Doc* pDoc = GetDocument();

	int x, y;

	for (y = 0; y < pDoc->lmageHeight; y++)
		for (x = 0; x < pDoc->lmageWidth; x++)
		{
			if (pDoc->Depth == 1)
				pDoc->ResultImage[y][pDoc->lmageWidth - 1 - x] = pDoc->InputImage[y][x];
			else
			{
				pDoc->ResultImage[y][3 * (pDoc->lmageWidth - 1 - x) + 0] = pDoc->InputImage[y][3 * x + 0];
				pDoc->ResultImage[y][3 * (pDoc->lmageWidth - 1 - x) + 1] = pDoc->InputImage[y][3 * x + 1];
				pDoc->ResultImage[y][3 * (pDoc->lmageWidth - 1 - x) + 2] = pDoc->InputImage[y][3 * x + 2];
			}
		}

	Invalidate();
}

void CImagePro20210797View::OnGeometryFlip()
{
	CImagePro20210797Doc* pDoc = GetDocument();

	int x, y;

	for (y = 0; y < pDoc->lmageHeight; y++)
		for (x = 0; x < pDoc->lmageWidth; x++)
		{
			if (pDoc->Depth == 1)
				pDoc->ResultImage[pDoc->lmageHeight - 1 - y][x] = pDoc->InputImage[y][x];
			else
			{
				pDoc->ResultImage[pDoc->lmageHeight - 1 - y][3 * x + 0] = pDoc->InputImage[y][3 * x + 0];
				pDoc->ResultImage[pDoc->lmageHeight - 1 - y][3 * x + 1] = pDoc->InputImage[y][3 * x + 1];
				pDoc->ResultImage[pDoc->lmageHeight - 1 - y][3 * x + 2] = pDoc->InputImage[y][3 * x + 2];
			}
		}

	Invalidate();
}

typedef struct // 4개의 점 생성
{
	int Px;
	int Py;
	int Qx;
	int Qy;
} controll_line;	// 구조체 형식 정의

controll_line mctrl_source = { 100, 100, 150, 150 };
controll_line mctrl_dest = { 100, 100, 200, 200 };

void CImagePro20210797View::OnGeometryWarping()
{
	CImagePro20210797Doc* pDoc = GetDocument();

	controll_line source_lines[5] =	// 점 4개 정의
	{
		{100, 100, 150, 150},
		{0, 0, pDoc->lmageWidth - 1, 0},
		{pDoc->lmageWidth - 1, 0, pDoc->lmageWidth - 1, pDoc->lmageHeight - 1},
		{pDoc->lmageWidth - 1, pDoc->lmageHeight - 1, 0, pDoc->lmageHeight - 1},
		{0, pDoc->lmageHeight - 1, 0, 0}
	};

	controll_line dest_lines[5] =
	{
		{100, 100, 200, 200},
		{0, 0, pDoc->lmageWidth - 1, 0},
		{pDoc->lmageWidth - 1, 0, pDoc->lmageWidth - 1, pDoc->lmageHeight - 1},
		{pDoc->lmageWidth - 1, pDoc->lmageHeight - 1, 0, pDoc->lmageHeight - 1},
		{0, pDoc->lmageHeight - 1, 0, 0}
	};

	source_lines[0] = mctrl_source;
	dest_lines[0] = mctrl_dest;

	int x, y;
	double u;	// 수직 교차점의 위치
	double h;	// 제어선으로부터 픽셀의 수직거리
	double d;	// 제어선과 픽셀사이의 거리
	double tx, ty;	// 결과영상 픽셀과 대응되는 입력영상의 픽셀사이의 변위 합
	double xp, yp;	// 각 제어선에 대해 계산된 입력 양상의 대응되는 픽셀 위치
	double weight;	// 각 제어선의 가중치
	double totalWeight;	// 가중치의 합
	double a = 0.001;
	double b = 2.0;
	double p = 0.75;

	int x1, y1, x2, y2;
	int src_x1, src_y1, src_x2, src_y2;

	double src_line_length, dest_line_length;

	int num_line = 5;	// 제어선의 수
	int line;
	int source_x, source_y;

	for (y = 0; y < pDoc->lmageHeight; y++)
		for (x = 0; x < pDoc->lmageWidth; x++)
		{
			tx = 0.0;
			ty = 0.0;
			totalWeight = 0.0;

			for (line = 0; line < num_line; line++)
			{
				x1 = dest_lines[line].Px;
				y1 = dest_lines[line].Py;
				x2 = dest_lines[line].Qx;
				y2 = dest_lines[line].Qy;

				dest_line_length = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));

				u = (double)((x - x1) * (x2 - x1) + (y - y1) * (y2 - y1)) /
					(double)((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));

				h = ((y - y1) * (x2 - x1) - (x - x1) * (y2 - y1)) / dest_line_length;

				if (u < 0)			d = sqrt((x - x1) * (x - x1) + (y - y1) * (y - y1));
				else if (u > 1)		d = sqrt((x - x2) * (x - x2) + (y - y2) * (y - y2));
				else				d = fabs(h);

				src_x1 = source_lines[line].Px;
				src_y1 = source_lines[line].Py;
				src_x2 = source_lines[line].Qx;
				src_y2 = source_lines[line].Qy;

				src_line_length = sqrt((src_x2 - src_x1) * (src_x2 - src_x1) + (src_y2 - src_y1) * (src_y2 - src_y1));

				xp = src_x1 + u * (src_x2 - src_x1) - (h * (src_y2 - src_y1)) / src_line_length;
				yp = src_y1 + u * (src_y2 - src_y1) + (h * (src_x2 - src_x1)) / src_line_length;

				weight = pow(pow(dest_line_length, p) / (a + d), b);	// 가중치 계산

				tx += (xp - x) * weight;
				ty += (yp - y) * weight;
				totalWeight += weight;
			}

			source_x = x + tx / totalWeight;
			source_y = y + ty / totalWeight;

			if (source_x < 0)	source_x = 0;
			else if (source_x > pDoc->lmageWidth - 1)	source_x = pDoc->lmageWidth - 1;
			if (source_y < 0)	source_y = 0;
			else if (source_y > pDoc->lmageHeight - 1)	source_y = pDoc->lmageHeight - 1;

			if (pDoc->Depth == 1)
			pDoc->ResultImage[y][x] = pDoc->InputImage[source_y][source_x];	// 역방향 사상
			else
			{
				pDoc->ResultImage[y][3 * x + 0] = pDoc->InputImage[source_y][3 * source_x + 0];
				pDoc->ResultImage[y][3 * x + 1] = pDoc->InputImage[source_y][3 * source_x + 1];
				pDoc->ResultImage[y][3 * x + 2] = pDoc->InputImage[source_y][3 * source_x + 2];
			}
		}

	Invalidate();
}

void CImagePro20210797View::OnGeometryMorphingWithLoad()
{
	CImagePro20210797Doc* pDoc = GetDocument();

	CFile file;
	CFileDialog dlg(TRUE);

	if (dlg.DoModal() == IDOK)
	{
		file.Open(dlg.GetPathName(), CFile::modeRead);
		CArchive ar(&file, CArchive::load);
		pDoc->LoadSecondImageFile(ar);
		file.Close();

		// 이미지 크기와 Depth 체크
		if (pDoc->lmageWidth != pDoc->lmageWidth || pDoc->lmageHeight != pDoc->lmageHeight)
		{
			AfxMessageBox(_T("두 이미지 크기가 다릅니다!"));
			return;
		}
		if (pDoc->Depth != pDoc->Depth)
		{
			AfxMessageBox(_T("두 이미지 색상 깊이가 다릅니다!"));
			return;
		}

		// alpha 값 고정 0.5 (필요 시 조절 가능)
		double alpha = 0.5;
		MorphImages(alpha);
	}

	Invalidate();
}

void CImagePro20210797View::MorphImages(double alpha)
{
	CImagePro20210797Doc* pDoc = GetDocument();

	int width = pDoc->lmageWidth;
	int height = pDoc->lmageHeight;
	int depth = pDoc->Depth;

	// 선형 보간으로 모핑 처리 (간단한 모핑 예제)
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (depth == 1)
			{
				int val = (int)((1.0 - alpha) * pDoc->InputImage[y][x] + alpha * pDoc->InputImage2[y][x]);
				if (val > 255) val = 255;
				else if (val < 0) val = 0;
				pDoc->ResultImage[y][x] = (unsigned char)val;
			}
			else if (depth == 3)
			{
				for (int c = 0; c < 3; c++)
				{
					int val = (int)((1.0 - alpha) * pDoc->InputImage[y][x * 3 + c] + alpha * pDoc->InputImage2[y][x * 3 + c]);
					if (val > 255) val = 255;
					else if (val < 0) val = 0;
					pDoc->ResultImage[y][x * 3 + c] = (unsigned char)val;
				}
			}
		}
	}
}


CPoint mpos_start, mpos_end;

void CImagePro20210797View::OnLButtonDown(UINT nFlags, CPoint point)
{
	mpos_start = point;

	CScrollView::OnLButtonDown(nFlags, point);
}

void CImagePro20210797View::OnLButtonUp(UINT nFlags, CPoint point)
{
	mpos_end = point;

	CDC* pDC = GetDC();
	CPen	pen;
	pen.CreatePen(PS_SOLID, 0, RGB(255, 0, 0));

	pDC->SelectObject(&pen);
	pDC->MoveTo(mpos_start);
	pDC->LineTo(mpos_end);

	ReleaseDC(pDC);

	int Ax, Ay, Bx, By;
	Ax = mpos_start.x;
	Ay = mpos_start.y;
	Bx = mpos_end.x;
	By = mpos_end.y;

	// 기준 위치
	if (Ax < Bx)	mctrl_source.Px = Ax - (Bx - Ax) / 2;
	else 			mctrl_source.Px = Ax + (Bx - Ax) / 2;

	if (Ay < By)	mctrl_source.Py = Ay - (By - Ay) / 2;
	else 			mctrl_source.Py = Ay + (By - Ay) / 2;

	mctrl_dest.Px = mctrl_source.Px;
	mctrl_dest.Py = mctrl_source.Py;

	mctrl_source.Qx = mpos_start.x;
	mctrl_source.Qy = mpos_start.y;
	mctrl_dest.Qx = mpos_end.x;
	mctrl_dest.Qy = mpos_end.y;

	CScrollView::OnLButtonUp(nFlags, point);
}

void CImagePro20210797View::OnAviView()
{
	CFileDialog dlg(true, "", "", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "AVI 파일(*.avi)|*.avi|모든 파일(*.*)|*.*|");

	if (dlg.DoModal() == IDOK)
	{
		AVIFileName = dlg.GetPathName();
		bAviMode = true;

		Invalidate();
	}
}

#include "Vfw.h"
void CImagePro20210797View::LoadAviFile(CDC* pDC)
{
	PAVIFILE pavi;
	LPBITMAPINFOHEADER pbmapih;
	PAVISTREAM pstm = NULL;
	PGETFRAME pfrm = NULL;

	AVIFILEINFO fi;
	AVISTREAMINFO si;

	int stm;
	int frame;
	int x, y;

	unsigned char* image;

	AVIFileInit();
	AVIFileOpen(&pavi, AVIFileName, OF_READ || OF_SHARE_DENY_NONE, NULL);
	AVIFileInfo(pavi, &fi, sizeof(AVIFILEINFO));

	for (stm = 0; stm < fi.dwStreams; stm++)
	{
		AVIFileGetStream(pavi, &pstm, 0, stm);
		AVIStreamInfo(pstm, &si, sizeof(si));
		if (si.fccType == streamtypeVIDEO)
		{
			pfrm = AVIStreamGetFrameOpen(pstm, NULL);
			for (frame = 0; frame < fi.dwLength; frame++)
			{
				pbmapih = (LPBITMAPINFOHEADER)AVIStreamGetFrame(pfrm, frame);
				if (!pbmapih)	continue;

				image = (unsigned char*)((LPSTR)pbmapih + (WORD)pbmapih->biSize);

				/*
				for (y = 0; y < fi.dwHeight; y++)
					for (x = 0; x < fi.dwWidth; x++)
					{
						pDC->SetPixel(x, fi.dwHeight - 1 - y,
							RGB(image[(y * fi.dwWidth + x) * 3 + 2],
								image[(y * fi.dwWidth + x) * 3 + 1],
								image[(y * fi.dwWidth + x) * 3 + 0]));
					}
				*/
				pDC->SetStretchBltMode(COLORONCOLOR);
				::SetDIBitsToDevice
				(
					pDC->GetSafeHdc(),
					0, 0, fi.dwWidth, fi.dwHeight,
					0, 0, 0, fi.dwWidth,
					image, (BITMAPINFO*)pbmapih, DIB_RGB_COLORS
				);
				Sleep(30);
			}
		}
	}

	AVIStreamGetFrameClose(pfrm);
	AVIStreamRelease(pstm);
	AVIFileRelease(pavi);
	AVIFileExit();
}
