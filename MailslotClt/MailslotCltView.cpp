
// MailslotCltView.cpp: CMailslotCltView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MailslotClt.h"
#endif

#include "MailslotCltDoc.h"
#include "MailslotCltView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMailslotCltView

IMPLEMENT_DYNCREATE(CMailslotCltView, CView)

BEGIN_MESSAGE_MAP(CMailslotCltView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(IDM_MAILSLOT_SEND, &CMailslotCltView::OnMailslotSend)
END_MESSAGE_MAP()

// CMailslotCltView 构造/析构

CMailslotCltView::CMailslotCltView() noexcept
{
	// TODO: 在此处添加构造代码

}

CMailslotCltView::~CMailslotCltView()
{
}

BOOL CMailslotCltView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMailslotCltView 绘图

void CMailslotCltView::OnDraw(CDC* /*pDC*/)
{
	CMailslotCltDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CMailslotCltView 打印

BOOL CMailslotCltView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMailslotCltView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMailslotCltView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CMailslotCltView 诊断

#ifdef _DEBUG
void CMailslotCltView::AssertValid() const
{
	CView::AssertValid();
}

void CMailslotCltView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMailslotCltDoc* CMailslotCltView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMailslotCltDoc)));
	return (CMailslotCltDoc*)m_pDocument;
}
#endif //_DEBUG


// CMailslotCltView 消息处理程序


void CMailslotCltView::OnMailslotSend()
{
	HANDLE hMailslot;
	//打开油槽
	LPCTSTR lpszSlotName = _TEXT("\\\\.\\mailslot\\MyMailslot");
	hMailslot = CreateFile(lpszSlotName, GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,NULL);
	if (INVALID_HANDLE_VALUE == hMailslot) {
		MessageBox(L"打开油槽失败！");
		return;
	}
	TCHAR buf[] = L"www.baidu.com";
	DWORD dwWrite;
	//向油槽写入数据
	if (!WriteFile(hMailslot, buf, _tcslen(buf) * sizeof(TCHAR), &dwWrite, NULL)) {
		MessageBox(L"写入数据失败！");
		CloseHandle(hMailslot);
		return;
	}
	CloseHandle(hMailslot);

}
