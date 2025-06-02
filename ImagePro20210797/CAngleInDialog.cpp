// CAngleInDialog.cpp: 구현 파일
//

#include "pch.h"
#include "ImagePro20210797.h"
#include "afxdialogex.h"
#include "CAngleInDialog.h"


// CAngleInDialog 대화 상자

IMPLEMENT_DYNAMIC(CAngleInDialog, CDialogEx)

CAngleInDialog::CAngleInDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_ANGLE_IN, pParent)
	, m_iAngle(0)
{

}

CAngleInDialog::~CAngleInDialog()
{
}

void CAngleInDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ANGLE, m_iAngle);
}


BEGIN_MESSAGE_MAP(CAngleInDialog, CDialogEx)
END_MESSAGE_MAP()


// CAngleInDialog 메시지 처리기
