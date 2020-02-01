
// MailslotSrvView.cpp: CMailslotSrvView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MailslotSrv.h"
#endif

#include "MailslotSrvDoc.h"
#include "MailslotSrvView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMailslotSrvView

IMPLEMENT_DYNCREATE(CMailslotSrvView, CView)

BEGIN_MESSAGE_MAP(CMailslotSrvView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(IDM_MAILSLOT_RECV, &CMailslotSrvView::OnMailslotRecv)
END_MESSAGE_MAP()

// CMailslotSrvView 构造/析构

CMailslotSrvView::CMailslotSrvView() noexcept
{
	// TODO: 在此处添加构造代码

}

CMailslotSrvView::~CMailslotSrvView()
{
}

BOOL CMailslotSrvView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMailslotSrvView 绘图

void CMailslotSrvView::OnDraw(CDC* /*pDC*/)
{
	CMailslotSrvDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CMailslotSrvView 打印

BOOL CMailslotSrvView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMailslotSrvView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMailslotSrvView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CMailslotSrvView 诊断

#ifdef _DEBUG
void CMailslotSrvView::AssertValid() const
{
	CView::AssertValid();
}

void CMailslotSrvView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMailslotSrvDoc* CMailslotSrvView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMailslotSrvDoc)));
	return (CMailslotSrvDoc*)m_pDocument;
}
#endif //_DEBUG


// CMailslotSrvView 消息处理程序


void CMailslotSrvView::OnMailslotRecv()
{
	HANDLE hMailslot;
	//创建油槽
	
	LPCTSTR lpszSlotName = _TEXT("\\\\.\\mailslot\\MyMailslot");
	hMailslot = CreateMailslot(lpszSlotName, 0, MAILSLOT_WAIT_FOREVER, NULL);

	if (INVALID_HANDLE_VALUE == hMailslot) {
		MessageBox(L"创建油槽失败");
			return;
	}

	TCHAR buf[100] = { 0 };
	DWORD  dwRead;

	//从油槽读取数据
	if (!ReadFile(hMailslot, buf, 100, &dwRead, NULL)) {
		MessageBox(L"读取数据失败");
		CloseHandle(hMailslot);
		return;
	}
	MessageBox(buf);
	CloseHandle(hMailslot);

}
