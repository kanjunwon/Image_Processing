
// ImagePro20210797Doc.cpp: CImagePro20210797Doc 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ImagePro20210797.h"
#endif

#include "ImagePro20210797Doc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CImagePro20210797Doc

IMPLEMENT_DYNCREATE(CImagePro20210797Doc, CDocument)

BEGIN_MESSAGE_MAP(CImagePro20210797Doc, CDocument)
END_MESSAGE_MAP()


// CImagePro20210797Doc 생성/소멸

CImagePro20210797Doc::CImagePro20210797Doc() noexcept
{
	InputImage = NULL;
	InputImage2 = NULL;
	ResultImage = NULL;

	gResultImage = NULL;	// 기하학적 처리
}

CImagePro20210797Doc::~CImagePro20210797Doc()
{
	int i;

	if (InputImage != NULL)
	{
		for (i = 0; i < lmageHeight; i++)
			free(InputImage[i]);
		free(InputImage);
	}

	if (InputImage2 != NULL)
	{
		for (i = 0; i < lmageHeight; i++)
			free(InputImage2[i]);
		free(InputImage2);
	}

	if (ResultImage != NULL)
	{
		for (i = 0; i < lmageHeight; i++)
			free(ResultImage[i]);
		free(ResultImage);
	}

	if (gResultImage != NULL)
	{
		for (i = 0; i < glmageHeight; i++)
			free(gResultImage[i]);
		free(gResultImage);
	}
}

BOOL CImagePro20210797Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CImagePro20210797Doc serialization

void CImagePro20210797Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		
	}
	else
	{
		LoadImageFile(ar);
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CImagePro20210797Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CImagePro20210797Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CImagePro20210797Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CImagePro20210797Doc 진단

#ifdef _DEBUG
void CImagePro20210797Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CImagePro20210797Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CImagePro20210797Doc 명령


void CImagePro20210797Doc::LoadImageFile(CArchive& ar)
{
	int maxValue;
	char type[16], buf[256];
	CFile* fp = ar.GetFile();
	CString fname = fp->GetFilePath();
	bool isbmp = false;

	if (strcmp(strrchr(fname, '.'), ".ppm") == 0 || strcmp(strchr(fname, '.'), ".PPM") == 0 || // ppm 파일
		strcmp(strrchr(fname, '.'), ".pgm") == 0 || strcmp(strchr(fname, '.'), ".PGM") == 0)	//pgm 파일
	{
		ar.ReadString(type, 15); // 아스키 코드

		do {
			ar.ReadString(buf, 255);
		} while (buf[0] == '#');
		sscanf(buf, "%d %d", &lmageWidth, &lmageHeight);

		do {
			ar.ReadString(buf, 255);
		} while (buf[0] == '#');
		sscanf(buf, "%d", &maxValue);

		if (strcmp(type, "P5") == 0)	Depth = 1;
		else							Depth = 3;
	}

	else if (strcmp(strchr(fname, '.'), ".raw") == 0 || strcmp(strchr(fname, '.'), ".RAW") == 0) // raw 파일
	{
		if (fp->GetLength() != 256 * 256)
		{
			AfxMessageBox("256x256 크기의 파일만 사용가능합니다.");
			return;
		}

		lmageWidth = 256;
		lmageHeight = 256;
		Depth = 1;
	}

	else if (strcmp(strrchr(fname, '.'), ".bmp") == 0 || strcmp(strchr(fname, '.'), ".BMP") == 0)	// bmp 파일
	{
		// bmp file Header 읽기
		BITMAPFILEHEADER bmfh;
		ar.Read(&bmfh, sizeof(bmfh)); // 바이너리 코드
		
		//BMP 파일임을 나타내는 "BM" 마커가 있는지 확인
		if (bmfh.bfType != (WORD)(('M' << 8) | 'B'))	return;

		//bmp info Header 읽기
		BITMAPINFOHEADER bih;
		ar.Read(&bih, sizeof(bih)); // 바이너리 코드

		lmageWidth = bih.biWidth;	// 가로
		lmageHeight = bih.biHeight;	// 세로
		Depth = bih.biBitCount / 8;	// 컬러

		int pal_size = bmfh.bfOffBits - sizeof(bmfh) - sizeof(bih);
		if (pal_size != 0)
		{
			// palette 존재
			BYTE palette[256 * 4];
			ar.Read(palette, 256 * 4);
		}
		else
		{
			if (Depth == 1)
			{
				// palette 존재
				BYTE palette[256 * 4];
				ar.Read(palette, 256 * 4);
			}
		}
		isbmp = true;
	}

	// 기억장소 할당
	InputImage = (unsigned char**)malloc(lmageHeight * sizeof(unsigned char*));
	ResultImage = (unsigned char**)malloc(lmageHeight * sizeof(unsigned char*));
	for (int i = 0; i < lmageHeight; i++)
	{
		InputImage[i] = (unsigned char*)malloc(lmageWidth * Depth);
		ResultImage[i] = (unsigned char*)malloc(lmageWidth * Depth);
	}

	if (!isbmp)		//bmp 파일이 아닐 때
	{
		for (int i = 0; i < lmageHeight; i++)
			ar.Read(InputImage[i], lmageWidth * Depth);
	}
	else	// bmp 파일일 때
	{
		BYTE nu[4];
		int widthfile;
		widthfile = (lmageWidth * Depth * 8 + 31) / 32 * 4;

		for (int i = 0; i < lmageHeight; i++)
		{
			if (Depth == 1)
				ar.Read(InputImage[lmageHeight - 1 - i], lmageWidth * Depth);
			else
			{
				for (int j = 0; j < lmageWidth; j++)
				{
					int r, g, b;
					ar.Read(&b, 1);		ar.Read(&g, 1);		ar.Read(&r, 1);

					InputImage[lmageHeight - 1 - i][3 * j + 0] = r;
					InputImage[lmageHeight - 1 - i][3 * j + 1] = g;
					InputImage[lmageHeight - 1 - i][3 * j + 2] = b;
				}
			}
			
			if ((widthfile - lmageWidth) != 0)
			{
				ar.Read(nu, (widthfile - lmageWidth * Depth));
			}
		}
	}
}

void CImagePro20210797Doc::LoadSecondImageFile(CArchive& ar)
{
	int i, maxValue;
	char type[16], buf[256];
	CFile* fp = ar.GetFile();
	CString fname = fp->GetFilePath();
	int W, H, D;
	bool isbmp = false;

	if (strcmp(strrchr(fname, '.'), ".ppm") == 0 || strcmp(strchr(fname, '.'), ".PPM") == 0 ||	// ppm 파일
		strcmp(strrchr(fname, '.'), ".pgm") == 0 || strcmp(strchr(fname, '.'), ".PGM") == 0)	// pgm 파일
	{
		ar.ReadString(type, 15);

		do {
			ar.ReadString(buf, 255);
		} while (buf[0] == '#');
		sscanf(buf, "%d %d", &W, &H);

		do {
			ar.ReadString(buf, 255);
		} while (buf[0] == '#');
		sscanf(buf, "%d", &maxValue);

		if (strcmp(type, "P5") == 0)	D = 1;
		else							D = 3;
	}

	else if (strcmp(strchr(fname, '.'), ".raw") == 0 || strcmp(strchr(fname, '.'), ".RAW") == 0)	// raw 파일
	{
		if (fp->GetLength() != 256 * 256)
		{
			AfxMessageBox("256x256 크기의 파일만 사용가능합니다.");
			return;
		}

		W = 256;
		H = 256;
		D = 1;
	}

	else if (strcmp(strrchr(fname, '.'), ".bmp") == 0 || strcmp(strchr(fname, '.'), ".BMP") == 0)	// bmp 파일
	{
		// bmp file Header 읽기
		BITMAPFILEHEADER bmfh;
		ar.Read(&bmfh, sizeof(bmfh)); // 바이너리 코드

		//BMP 파일임을 나타내는 "BM" 마커가 있는지 확인
		if (bmfh.bfType != (WORD)(('M' << 8) | 'B'))	return;

		//bmp info Header 읽기
		BITMAPINFOHEADER bih;
		ar.Read(&bih, sizeof(bih)); // 바이너리 코드

		W = bih.biWidth;	// 가로
		H = bih.biHeight;	// 세로
		D = bih.biBitCount / 8;	// 컬러

		int pal_size = bmfh.bfOffBits - sizeof(bmfh) - sizeof(bih);
		if (pal_size != 0)
		{
			// palette 존재
			BYTE palette[256 * 4];
			ar.Read(palette, 256 * 4);
		}
		else
		{
			if (Depth == 1)
			{
				// palette 존재
				BYTE palette[256 * 4];
				ar.Read(palette, 256 * 4);
			}
		}
		isbmp = true;
	}

	if (lmageWidth != W || lmageHeight != H || Depth != D)
	{
		AfxMessageBox("이미지의 가로, 세로 색상이 다릅니다.");
		return;
	}

	// 기억장소 할당
	InputImage2 = (unsigned char**)malloc(lmageHeight * sizeof(unsigned char*));
	for (int i = 0; i < lmageHeight; i++)
	{
		InputImage2[i] = (unsigned char*)malloc(lmageWidth * Depth);
	}

	if (!isbmp)		//bmp 파일이 아닐 때
	{
		for (int i = 0; i < lmageHeight; i++)
			ar.Read(InputImage2[i], lmageWidth * Depth);
	}
	else	// bmp 파일일 때
	{
		BYTE nu[4];
		int widthfile;
		widthfile = (lmageWidth * Depth * 8 + 31) / 32 * 4;

		for (int i = 0; i < lmageHeight; i++)
		{
			if (Depth == 1)
				ar.Read(InputImage2[lmageHeight - 1 - i], lmageWidth * Depth);
			else
			{
				for (int j = 0; j < lmageWidth; j++)
				{
					int r, g, b;
					ar.Read(&b, 1);		ar.Read(&g, 1);		ar.Read(&r, 1);

					InputImage2[lmageHeight - 1 - i][3 * j + 0] = r;
					InputImage2[lmageHeight - 1 - i][3 * j + 1] = g;
					InputImage2[lmageHeight - 1 - i][3 * j + 2] = b;
				}
			}

			if ((widthfile - lmageWidth) != 0)
			{
				ar.Read(nu, (widthfile - lmageWidth * Depth));
			}
		}
	}
}