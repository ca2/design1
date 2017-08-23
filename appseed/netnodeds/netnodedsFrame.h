#pragma once

class CLASS_DECL_CA2_DEVEDGE netnodedsFrame : public SimpleFrameWindow
{
	
public:
	netnodedsFrame(::ca::application * papp);

   void _001InstallMessageHandling(igui::win::message::sender * pinterface);

   DECL_GEN_SIGNAL(_001OnClose)
// Attributes
public:
   //BaseMenuMessageHandler        m_menuhook;
   
   int                        m_iAnimateStep;
   ImageList *                m_pimagelist;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(screencaptureFrame)
	public:
	virtual BOOL PreCreateWindow(::user::create_struct& cs);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, CAFX_CMDHANDLERINFO* pHandlerInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	void ShowControlBars(bool bShow);

	bool IsFullScreen();
	void ToggleFullScreen();
	virtual void WfiOnFullScreen(bool bFullScreen);
	virtual ~netnodedsFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


	int OnCreate(LPCREATESTRUCT lpCreateStruct);
	void OnViewFullScreen();
	void OnUpdateViewFullScreen(CCmdUI* pCmdUI);
	void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);
	void OnMove(int x, int y);
	void OnClose();
	void OnSysCommand(UINT nID, LPARAM lParam);
	void OnTimer(UINT nIDEvent);
   void OnShowWindow(BOOL bShow, UINT nStatus) ;
	void OnNcPaint();
	void OnTogglecustomframe();
	void OnUpdateTogglecustomframe(CCmdUI* pCmdUI);
	void OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu);
	void OnInitMenu(CMenu* pMenu);
	void OnActivate(UINT nState, base_wnd* pWndOther, BOOL bMinimized);
	BOOL OnCopyData(base_wnd * pwnd, COPYDATASTRUCT* pcds);
	DECLARE_MESSAGE_MAP()
};

