
// CSGDemoView.h : interface of the CCSGDemoView class
//

#pragma once


class CCSGDemoView : public CView
{
protected: // create from serialization only
	CCSGDemoView();
	DECLARE_DYNCREATE(CCSGDemoView)

// Attributes
public:
	CCSGDemoDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

	BOOL SetWindowPixelFormat(HDC hDC);
	BOOL CreateViewGLContext(HDC hDC);
// Implementation
public:
	virtual ~CCSGDemoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	int m_GLPixelIndex ;
	HGLRC m_hGLContext;
// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
};

#ifndef _DEBUG  // debug version in CSGDemoView.cpp
inline CCSGDemoDoc* CCSGDemoView::GetDocument() const
   { return reinterpret_cast<CCSGDemoDoc*>(m_pDocument); }
#endif

