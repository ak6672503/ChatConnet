
// NamedPipeCltView.h: CNamedPipeCltView 类的接口
//

#pragma once


class CNamedPipeCltView : public CView
{
protected: // 仅从序列化创建
	CNamedPipeCltView() noexcept;
	DECLARE_DYNCREATE(CNamedPipeCltView)

// 特性
public:
	CNamedPipeCltDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CNamedPipeCltView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPipeWrite();
	afx_msg void OnPipeRead();
	afx_msg void OnPipeConnect();
private:
	HANDLE hPipe;
};

#ifndef _DEBUG  // NamedPipeCltView.cpp 中的调试版本
inline CNamedPipeCltDoc* CNamedPipeCltView::GetDocument() const
   { return reinterpret_cast<CNamedPipeCltDoc*>(m_pDocument); }
#endif

