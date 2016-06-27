
// CSGDemoView.cpp : implementation of the CCSGDemoView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "CSGDemo.h"
#endif

#include "CSGDemoDoc.h"
#include "CSGDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCSGDemoView

IMPLEMENT_DYNCREATE(CCSGDemoView, CView)

BEGIN_MESSAGE_MAP(CCSGDemoView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CCSGDemoView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_PAINT()
END_MESSAGE_MAP()

// CCSGDemoView construction/destruction

CCSGDemoView::CCSGDemoView()
{
	// TODO: add construction code here
	this->m_GLPixelIndex = 0;
	this->m_hGLContext =NULL;
}

CCSGDemoView::~CCSGDemoView()
{
}

BOOL CCSGDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.style |= (WS_CLIPCHILDREN | WS_CLIPSIBLINGS);
	return CView::PreCreateWindow(cs);
}

// CCSGDemoView drawing

void CCSGDemoView::OnDraw(CDC* /*pDC*/)
{
	CCSGDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CCSGDemoView printing


void CCSGDemoView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CCSGDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CCSGDemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CCSGDemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CCSGDemoView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CCSGDemoView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CCSGDemoView diagnostics

#ifdef _DEBUG
void CCSGDemoView::AssertValid() const
{
	CView::AssertValid();
}

void CCSGDemoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCSGDemoDoc* CCSGDemoView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCSGDemoDoc)));
	return (CCSGDemoDoc*)m_pDocument;
}
#endif //_DEBUG

BOOL CCSGDemoView::SetWindowPixelFormat(HDC hDC)
{
	//定义窗口的像素格式 
	PIXELFORMATDESCRIPTOR pixelDesc=
	{
		sizeof(PIXELFORMATDESCRIPTOR),1,
		PFD_DRAW_TO_WINDOW|PFD_SUPPORT_OPENGL|
		PFD_DOUBLEBUFFER|PFD_SUPPORT_GDI,
		PFD_TYPE_RGBA,24,0,0,0,0,0,0,0,0,0,0,0,0,0,32,0,0,
		PFD_MAIN_PLANE,0,0,0,0
	};
	this->m_GLPixelIndex = ChoosePixelFormat(hDC,&pixelDesc);
	if(this->m_GLPixelIndex == 0)
	{
		this->m_GLPixelIndex = 1;
		if(DescribePixelFormat(hDC,this->m_GLPixelIndex,sizeof(PIXELFORMATDESCRIPTOR),&pixelDesc)==0)
		{
			return FALSE;
		}
	}
	if(SetPixelFormat(hDC,this->m_GLPixelIndex,&pixelDesc)==FALSE)
	{
		return FALSE;
	}
	return TRUE;
}

BOOL CCSGDemoView::CreateViewGLContext(HDC hDC)
{
	this->m_hGLContext =wglCreateContext(hDC);
	if(this->m_hGLContext==NULL)
	{
		//创建失败 
		return FALSE;
	}
	if(wglMakeCurrent(hDC,this->m_hGLContext)==FALSE)
	{
		//选为当前RC失败 
		return FALSE;
	}
	return TRUE;


} 


// CCSGDemoView message handlers


int CCSGDemoView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	HWND hWnd = this->GetSafeHwnd();
	HDC hDC =::GetDC(hWnd);
	if(this->SetWindowPixelFormat(hDC)==FALSE)
	{
		return 0;
	}
	if(this->CreateViewGLContext(hDC)==FALSE)
	{
		return 0;
	}
	return 0;
}

void CCSGDemoView::OnDestroy()
{
	CView::OnDestroy();

	// TODO: Add your message handler code here
	if(wglGetCurrentContext()!=NULL)
	{
		wglMakeCurrent(NULL,NULL);
	}
	if(this->m_hGLContext!=NULL)
	{
		wglDeleteContext(this->m_hGLContext);
		this->m_hGLContext =NULL;
	}
}


void CCSGDemoView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	CView::OnSize(nType, cx, cy);
	GLsizei width,height;
	GLdouble aspect;
	width =cx;
	height =cy;if(cy==0)
	{
		aspect =(GLdouble)width;
	}else
	{
		aspect = (GLdouble)width/(GLdouble)height;
	}
	glViewport(0,0,width,height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,500.0*aspect,0.0,500.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}


void CCSGDemoView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CView::OnPaint() for painting messages

	glLoadIdentity();
	glClearColor(1,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POLYGON);
	glColor4f(1.0f,0.0f,0.0f,1.0f);
	glVertex2f(100.0f,50.0f);
	glColor4f(0.0f,1.0f,0.0f,1.0f);
	glVertex2f(450.0f,400.0f);
	glColor4f(0.0f,0.0f,1.0f,1.0f);
	glVertex2f(450.0f,50.0f);
	glEnd();
	glFlush();
	//glutSwapBuffers();
}
