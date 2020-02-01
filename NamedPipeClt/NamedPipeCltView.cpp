
// NamedPipeCltView.cpp: CNamedPipeCltView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "NamedPipeClt.h"
#endif

#include "NamedPipeCltDoc.h"
#include "NamedPipeCltView.h"
#include"Resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CNamedPipeCltView

IMPLEMENT_DYNCREATE(CNamedPipeCltView, CView)

BEGIN_MESSAGE_MAP(CNamedPipeCltView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(IDM_PIPE_WRITE, &CNamedPipeCltView::OnPipeWrite)
	ON_COMMAND(IDM_PIPE_READ, &CNamedPipeCltView::OnPipeRead)
	ON_COMMAND(IDM_PIPE_CONNECT, &CNamedPipeCltView::OnPipeConnect)
END_MESSAGE_MAP()

// CNamedPipeCltView 构造/析构

CNamedPipeCltView::CNamedPipeCltView() noexcept
{
	hPipe = NULL;

}

CNamedPipeCltView::~CNamedPipeCltView()
{
	if (hPipe)
		CloseHandle(hPipe);
}

BOOL CNamedPipeCltView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CNamedPipeCltView 绘图

void CNamedPipeCltView::OnDraw(CDC* /*pDC*/)
{
	CNamedPipeCltDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CNamedPipeCltView 打印

BOOL CNamedPipeCltView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CNamedPipeCltView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CNamedPipeCltView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CNamedPipeCltView 诊断

#ifdef _DEBUG
void CNamedPipeCltView::AssertValid() const
{
	CView::AssertValid();
}

void CNamedPipeCltView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CNamedPipeCltDoc* CNamedPipeCltView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CNamedPipeCltDoc)));
	return (CNamedPipeCltDoc*)m_pDocument;
}
#endif //_DEBUG


// CNamedPipeCltView 消息处理程序


void CNamedPipeCltView::OnPipeWrite()
{
	char buf[] = "命名管道测试程序";
	DWORD dwWrite;
	if (!WriteFile(hPipe, buf, strlen(buf) + 1, &dwWrite, NULL) ){
		MessageBox(L"写入数据失败");
			return;
	}
}


void CNamedPipeCltView::OnPipeRead()
{
	char buf[100];
	DWORD dwRead;
	if (!ReadFile(hPipe, buf, 100, &dwRead, NULL)) {
		MessageBox(L"读取数据失败");
		return;
	}
	USES_CONVERSION;
	MessageBox(A2T(buf));
}


void CNamedPipeCltView::OnPipeConnect()
{

	LPCTSTR lpszSlotName = _TEXT("\\\\.\\pipe\\MyPipe");
	//判断是否有可以利用的命名管道
	if (!WaitNamedPipe(lpszSlotName, NMPWAIT_WAIT_FOREVER)) {
		MessageBox(L"当前没有可用的命名管道");
		return;
	}
	//打开可用的命名管道 并与服务端进行通信
	hPipe = CreateFile(lpszSlotName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == hPipe) {
		MessageBox(L"打开管道失败");
		hPipe = NULL;
		return;
	}

}
