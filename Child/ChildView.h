
// ChildView.h: CChildView 类的接口
//

#pragma once


class CChildView : public CView
{
protected: // 仅从序列化创建
	CChildView() noexcept;
	DECLARE_DYNCREATE(CChildView)

// 特性
public:
	CChildDoc* GetDocument() const;

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
	virtual ~CChildView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPipeRead();
	afx_msg void OnPipeWrite();
private:
	HANDLE hWrite;
	HANDLE hRead;

public:
	virtual void OnInitialUpdate();
};

#ifndef _DEBUG  // ChildView.cpp 中的调试版本
inline CChildDoc* CChildView::GetDocument() const
   { return reinterpret_cast<CChildDoc*>(m_pDocument); }
#endif

