﻿
// ImagePro20210797Doc.h: CImagePro20210797Doc 클래스의 인터페이스
//


#pragma once


class CImagePro20210797Doc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CImagePro20210797Doc() noexcept;
	DECLARE_DYNCREATE(CImagePro20210797Doc)

// 특성입니다.
public:

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CImagePro20210797Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:

	unsigned char** InputImage;
	unsigned char** InputImage2;
	unsigned char** ResultImage;
	
	int lmageWidth;			// 가로 크기
	int lmageHeight;		// 세로 크기
	int Depth;				// 1= 흑백 영상, 3= 컬러 영상
	
	// 기하학적변환을 위한 변수와 메모리
	int glmageWidth;		// 가로 크기
	int glmageHeight;		// 세로 크기
	unsigned char** gResultImage;

	void LoadImageFile(CArchive& ar);
	void LoadSecondImageFile(CArchive& ar);
};
