#include "stdafx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new AURA_NEW
#endif


// IMPLEMENT_DYNCREATE(netnodedsView, base_edit_plain_text_view)

  BEGIN_MESSAGE_MAP(netnodedsView, base_edit_plain_text_view)
	//{{AFX_MSG_MAP(netnodedsView)
/*
   ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_CONTEXTMENU()
	ON_WM_SETCURSOR()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
	// Standard printing commands
   ON_MESSAGE(WM_USER + 177, OnTabClick)
   ON_MESSAGE(WM_APP + 119, OnWavePlayerEvent)
	ON_COMMAND(ID_FILE_PRINT, base_edit_plain_text_view::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, base_edit_plain_text_view::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, base_edit_plain_text_view::OnFilePrintPreview)
   */
END_MESSAGE_MAP()


netnodedsView::netnodedsView(::ca::application * papp)
: base_edit_plain_text_view(papp), Ex1VirtualGuieInterface(papp), BaseVirtualGuie(papp),
Ex1ScrollViewInterface(papp), BaseScrollView(papp), Ex1EditPlainTextInterface(papp)
{
   m_bMultiLine = true;
   connect_update_cmd_ui("edit_undo", &netnodedsView::_001OnUpdateEditUndo);
   connect_command("edit_undo", &netnodedsView::_001OnEditUndo);
   connect_update_cmd_ui("edit_redo", &netnodedsView::_001OnUpdateEditRedo);
   connect_command("edit_redo", &netnodedsView::_001OnEditRedo);


   LOGFONT lf;

   memset(&lf, 0, sizeof(lf));
   lf.lfHeight = 16;
   strcpy(lf.lfFaceName, "Courier New");
   
   m_font.CreateFontIndirect(&lf);

}

netnodedsView::~netnodedsView()
{
}



#ifdef _DEBUG
void netnodedsView::AssertValid() const
{
	base_edit_plain_text_view::AssertValid();
}

void netnodedsView::Dump(CDumpContext& dc) const
{
	base_edit_plain_text_view::Dump(dc);
}
#endif //_DEBUG

BOOL netnodedsView::PreCreateWindow(::user::create_struct& cs)
{
   cs.lpszClass = AfxRegisterWndClass(
		CS_DBLCLKS |
		CS_OWNDC,
		0, 0, 0);
   cs.style &= ~WS_EX_CLIENTEDGE;
   cs.style &= ~WS_BORDER;
	return base_edit_plain_text_view::PreCreateWindow(cs);
}

BOOL netnodedsView::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}

void netnodedsView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
}

void netnodedsView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
}


base_wnd * netnodedsView::_001GetWnd()
{
   return this;
}

void netnodedsView::OnUpdate(BaseView* pSender, LPARAM lHint, base_object* phint) 
{
   if(lHint == 1001)
   {
      _001RedrawWindow();
   }
   else if(lHint == 123)
   {
      SetFile(&GetDocument()->m_file);
      CDC * pdc = _001GetWnd()->GetDC();
      _001OnCalcLayout(pdc);
      _001GetWnd()->ReleaseDC(pdc);

      AfxBeginThread(get_app(), ThreadProcScrollSize, dynamic_cast < Ex1EditPlainTextInterface * > (this));
   }
   else if(lHint == 12345)
   {
      m_editfile.Flush();
   }
   else if(lHint == 1234508)
   {
      CreateLineIndex();
      m_bGetTextNeedUpdate = true;
      RedrawWindow();
      CDC * pdc = _001GetWnd()->GetDC();
      _001OnCalcLayout(pdc);
      _001GetWnd()->ReleaseDC(pdc);

      AfxBeginThread(get_app(), ThreadProcScrollSize, dynamic_cast < Ex1EditPlainTextInterface * > (this));

   }
   /*xxx if(phint != NULL)
   {
   	if(phint->is_kind_of(&typeid(PaneViewUpdateHint)))
      {
         PaneViewUpdateHint * puh = (PaneViewUpdateHint * ) phint;
         if(puh->IsTypeOf(PaneViewUpdateHint::TypeOnBeforeShowView))
         {
            GetDocument()->OnSaveDocument(GetDocument()->GetPathName());
         }
         else if(puh->IsTypeOf(PaneViewUpdateHint::TypeOnShowView))
         {
            GetDocument()->reload();
         }
      }
   }*/
	
}

void netnodedsView::_001OnDestroy(gen::signal_object * pobj) 
{
	base_edit_plain_text_view::OnDestroy();

}

void netnodedsView::_001OnCreate(gen::signal_object * pobj) 
{
   if(pobj->previous())
      return;

   netnodedsDoc * pdoc = GetDocument();

   SetTimer(100, 100, NULL);
   
}

void netnodedsView::_001OnContextMenu(gen::signal_object * pobj) 
{
   SCAST_PTR(igui::win::message::context_menu, pcontextmenu, pobj)
   int iItem;
   HRESULT hr;
   //point point = pmouse->m_pt;
   point point;
   ::GetCursorPos(&point);
   class point ptClient = point;
   base_wnd::ClientToScreen(&point);
   //ScreenToClient(&ptClient);
   BaseWndMenu menu(get_app());
   Ex1TextFile file(get_app());

   string strModuleFolder;
   strModuleFolder = Application.get_module_folder();

   if(!file.Open(Application.dir().path(strModuleFolder, "netnodeds_contextmenu.xml"), Ex1File::typeText | Ex1File::modeRead))
      return;

   string str;
   file.ReadFullString(str);

   XNode node;

   node.Load(str);

   if (menu.LoadMenu(get_app(), &node))
   {
      //BaseWndMenu* pPopup = (BaseWndMenuItem *) menu.GetSubMenu(0);
      //ASSERT(pPopup != NULL);
      BaseFrameWnd * pframe = dynamic_cast < BaseFrameWnd * > ( dynamic_cast < base_wnd * > (GetParentFrame()));
      //pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,
        // point.x, point.y,
         //(base_wnd *) pframe);
      menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,
         point.x, point.y,
         pframe->GetSafeHwnd());
   }
}





void netnodedsView::_001OnSetCursor(gen::signal_object * pobj) 
{
   ::SetCursor(::LoadCursor(NULL, IDC_ARROW));
	
	pobj->previous();
}
void netnodedsView::_001OnEraseBkgnd(gen::signal_object * pobj) 
{
   SCAST_PTR(igui::win::message::erase_bkgnd, perasebkgnd, pobj)
   perasebkgnd->m_bRet = true;
   perasebkgnd->set_result(TRUE);
}

netnodedsDoc * netnodedsView::GetDocument() const
{
	return (netnodedsDoc *) base_edit_plain_text_view::GetDocument();
}


base_wnd * netnodedsView::VirtualGetWnd()
{
   return this;
}

BOOL netnodedsView::PreTranslateMessage(MSG * pMsg)
{
  return base_edit_plain_text_view::PreTranslateMessage(pMsg);
}

void netnodedsView::_001OnUpdateEditUndo(gen::signal_object * pobj)
{
   SCAST_PTR(BaseCmdUi, pcmdui, pobj)
   pcmdui->m_pcmdui->Enable(m_editfile.CanUndo());
}

void netnodedsView::_001OnUpdateEditRedo(gen::signal_object * pobj)
{
   SCAST_PTR(BaseCmdUi, pcmdui, pobj)
   pcmdui->m_pcmdui->Enable(m_editfile.GetRedoBranchCount() > 0);
}

void netnodedsView::_001OnEditUndo(gen::signal_object * pobj)
{
   Undo();
}

void netnodedsView::_001OnEditRedo(gen::signal_object * pobj)
{
   Redo();
}
