#include "stdafx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new AURA_NEW
#endif


// IMPLEMENT_DYNCREATE(devedgeView, base_edit_plain_text_view)

BEGIN_MESSAGE_MAP(devedgeView, base_edit_plain_text_view)
   //{{AFX_MSG_MAP(devedgeView)
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
   	ON_COMMAND(ID_FILE_PRINT, base_edit_plain_text_view::OnFilePrint)
   	ON_COMMAND(ID_FILE_PRINT_DIRECT, base_edit_plain_text_view::OnFilePrint)
   	ON_COMMAND(ID_FILE_PRINT_PREVIEW, base_edit_plain_text_view::OnFilePrintPreview)
      */
END_MESSAGE_MAP()


devedgeView::devedgeView(::ca::application * papp)
   : base_edit_plain_text_view(papp), Ex1VirtualGuieInterface(papp), BaseVirtualGuie(papp),
     Ex1ScrollViewInterface(papp), BaseScrollView(papp), Ex1EditPlainTextInterface(papp)
{
   m_bMultiLine = true;
   connect_command_probe("edit_undo", &devedgeView::_001OnUpdateEditUndo);
   connect_command("edit_undo", &devedgeView::_001OnEditUndo);
   connect_command_probe("edit_redo", &devedgeView::_001OnUpdateEditRedo);
   connect_command("edit_redo", &devedgeView::_001OnEditRedo);


   LOGFONT lf;

   memset(&lf, 0, sizeof(lf));
   lf.lfHeight = 16;
   strcpy(lf.lfFaceName, "Courier New");

   m_font.CreateFontIndirect(&lf);

}

devedgeView::~devedgeView()
{
}



#ifdef _DEBUG
void devedgeView::AssertValid() const
{
   base_edit_plain_text_view::AssertValid();
}

void devedgeView::Dump(CDumpContext& dc) const
{
   base_edit_plain_text_view::Dump(dc);
}
#endif //_DEBUG

BOOL devedgeView::PreCreateWindow(::user::create_struct& cs)
{
   cs.lpszClass = AfxRegisterWndClass(
                  CS_DBLCLKS |
                  CS_OWNDC,
                  0, 0, 0);
   cs.style &= ~WS_EX_CLIENTEDGE;
   cs.style &= ~WS_BORDER;
   return base_edit_plain_text_view::PreCreateWindow(cs);
}

BOOL devedgeView::OnPreparePrinting(CPrintInfo* pInfo)
{
   return DoPreparePrinting(pInfo);
}

void devedgeView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
}

void devedgeView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
}


base_wnd * devedgeView::_001GetWnd()
{
   return this;
}

void devedgeView::OnUpdate(BaseView* pSender, LPARAM lHint, base_object* phint)
{
   if(lHint == 1001)
   {
      set_need_redraw();
   }
   else if(lHint == 123)
   {
      SetFile(&GetDocument()->m_file);
      CDC * pgraphics = _001GetWnd()->GetDC();
      _001OnCalcLayout(pgraphics);
      _001GetWnd()->ReleaseDC(pgraphics);

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
      set_need_redraw();
      CDC * pgraphics = _001GetWnd()->GetDC();
      _001OnCalcLayout(pgraphics);
      _001GetWnd()->ReleaseDC(pgraphics);

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

void devedgeView::_001OnDestroy(gen::message::sender_object * pobj)
{
   base_edit_plain_text_view::OnDestroy();

}

void devedgeView::_001OnCreate(gen::message::sender_object * pobj)
{
   if(pobj->previous())
      return;

   devedgeDoc * pdoc = GetDocument();

   SetTimer(100, 100, NULL);

}

void devedgeView::_001OnContextMenu(gen::message::sender_object * pobj)
{
   SCAST_PTR(igui::win::message::context_menu, pcontextmenu, pobj);
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

   if(!file.Open(Application.dir().path(strModuleFolder, "devedge_contextmenu.xml"), Ex1File::typeText | Ex1File::modeRead))
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
      //pPopup->track_popup_menu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,
      // point.x, point.y,
      //(base_wnd *) pframe);
      menu.track_popup_menu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,
                            point.x, point.y,
                            pframe->GetSafeHwnd());
   }
}





void devedgeView::_001OnSetCursor(gen::message::sender_object * pobj)
{
   ::SetCursor(::LoadCursor(NULL, IDC_ARROW));

   pobj->previous();
}
void devedgeView::_001OnEraseBkgnd(gen::message::sender_object * pobj)
{
   SCAST_PTR(igui::win::message::erase_bkgnd, perasebkgnd, pobj);
   perasebkgnd->m_bRet = true;
   perasebkgnd->set_result(TRUE);
}

devedgeDoc * devedgeView::GetDocument() const
{
   return (devedgeDoc *) base_edit_plain_text_view::GetDocument();
}


base_wnd * devedgeView::VirtualGetWnd()
{
   return this;
}

BOOL devedgeView::PreTranslateMessage(MSG * pMsg)
{
   return base_edit_plain_text_view::PreTranslateMessage(pMsg);
}

void devedgeView::_001OnUpdateEditUndo(gen::message::sender_object * pobj)
{
   SCAST_PTR(BaseCmdUi, pcommand, pobj);
   pcommand->Enable(m_editfile.CanUndo());
}

void devedgeView::_001OnUpdateEditRedo(gen::message::sender_object * pobj)
{
   SCAST_PTR(BaseCmdUi, pcommand, pobj);
   pcommand->Enable(m_editfile.GetRedoBranchCount() > 0);
}

void devedgeView::_001OnEditUndo(gen::message::sender_object * pobj)
{
   Undo();
}

void devedgeView::_001OnEditRedo(gen::message::sender_object * pobj)
{
   Redo();
}
