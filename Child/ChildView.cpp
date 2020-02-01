
// ChildView.cpp: CChildView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Child.h"
#endif

#include "ChildDoc.h"
#include "ChildView.h"
#include"resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

IMPLEMENT_DYNCREATE(CChildView, CView)

BEGIN_MESSAGE_MAP(CChildView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(IDM_PIPE_READ, &CChildView::OnPipeRead)
	ON_COMMAND(IDM_PIPE_WRITE, &CChildView::OnPipeWrite)
END_MESSAGE_MAP()

// CChildView 构造/析构

CChildView::CChildView() noexcept
{
	hRead = NULL;
	hWrite = NULL;
}

CChildView::~CChildView()
{
	if (hRead)
		CloseHandle(hRead);
	if (hWrite)
		CloseHandle(hWrite);
}

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CChildView 绘图

void CChildView::OnDraw(CDC* /*pDC*/)
{
	CChildDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CChildView 打印

BOOL CChildView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CChildView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CChildView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CChildView 诊断

#ifdef _DEBUG
void CChildView::AssertValid() const
{
	CView::AssertValid();
}

void CChildView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CChildDoc* CChildView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CChildDoc)));
	return (CChildDoc*)m_pDocument;
}
#endif //_DEBUG


// CChildView 消息处理程序


void CChildView::OnPipeRead()
{
	char buf[100];
	DWORD dwRead;
	if (!ReadFile(hRead, buf, 100, &dwRead, NULL)) {
		MessageBox(L"读取数据失败！");
		return;
	}
	USES_CONVERSION;
	MessageBox(A2T(buf));

}


void CChildView::OnPipeWrite()
{
	char buf[] = "匿名管道测试程序";
	DWORD dwWrite;
	if (!WriteFile(hWrite, buf, strlen(buf) + 1, &dwWrite, NULL)) {
		MessageBox(L"写入数据失败!");
		return;
	}
}

//窗口创建成功后第一个调用的函数，所以要干嘛就可以先在这里做
void CChildView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	hRead = GetStdHandle(STD_INPUT_HANDLE);
	hWrite = GetStdHandle(STD_OUTPUT_HANDLE);


}
