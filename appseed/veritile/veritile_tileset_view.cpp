#include "framework.h"


namespace veritile
{


   tileset_view::tileset_view(::aura::application * papp):
      ::object(papp),
      m_data(papp)
   {



      connect_command("selection_tool",&tileset_view::_001OnSelectionTool);
      connect_update_cmd_ui("selection_tool",&tileset_view::_001OnUpdateSelectionTool);
      connect_command("polygon_tool",&tileset_view::_001OnPolygonTool);
      connect_update_cmd_ui("polygon_tool",&tileset_view::_001OnUpdatePolygonTool);


   }

   tileset_view::~tileset_view()
   {
   }

   void tileset_view::install_message_handling(::message::dispatch * pinterface)
   {
      BASE_VIEW::install_message_handling(pinterface);

      IGUI_WIN_MSG_LINK(WM_DESTROY,pinterface,this,&tileset_view::_001OnDestroy);
      IGUI_WIN_MSG_LINK(WM_SIZE,pinterface,this,&tileset_view::_001OnSize);
      IGUI_WIN_MSG_LINK(WM_CREATE,pinterface,this,&tileset_view::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_CONTEXTMENU,pinterface,this,&tileset_view::_001OnContextMenu);
      IGUI_WIN_MSG_LINK(WM_SETCURSOR,pinterface,this,&tileset_view::_001OnSetCursor);
      IGUI_WIN_MSG_LINK(WM_ERASEBKGND,pinterface,this,&tileset_view::_001OnEraseBkgnd);
      //      
      IGUI_WIN_MSG_LINK(WM_MOUSEMOVE,pinterface,this,&tileset_view::_001OnMouseMove);
      IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN,pinterface,this,&tileset_view::_001OnLButtonDown);
      IGUI_WIN_MSG_LINK(WM_LBUTTONUP,pinterface,this,&tileset_view::_001OnLButtonUp);
      IGUI_WIN_MSG_LINK(WM_LBUTTONDBLCLK,pinterface,this,&tileset_view::_001OnLButtonDblClk);

      //   IGUI_WIN_MSG_LINK(WM_USER + 177     , this, this, &tileset_view::_001OnTabClick);
      //   IGUI_WIN_MSG_LINK(WM_APP + 119      , this, this, &tileset_view::_001OnWavePlayerEvent);
      //connect_command(ID_FILE_PRINT, ::user::impact::OnFilePrint)
      //connect_command(ID_FILE_PRINT_DIRECT, ::user::impact::OnFilePrint)
      //connect_command(ID_FILE_PRINT_PREVIEW, ::user::impact::OnFilePrintPreview)


   }

#ifdef DEBUG
   void tileset_view::assert_valid() const
   {
      ::user::impact::assert_valid();
   }

   void tileset_view::dump(dump_context & dumpcontext) const
   {
      ::user::impact::dump(dumpcontext);
   }
#endif 

   bool tileset_view::pre_create_window(::user::create_struct& cs)
   {

      cs.style &= ~WS_EX_CLIENTEDGE;

      return ::user::impact::pre_create_window(cs);

   }


   void tileset_view::_001OnInitialUpdate()
   {
      ::user::impact::_001OnInitialUpdate();

   }

   void tileset_view::on_update(::user::impact * pSender,LPARAM lHint,::object* phint)
   {
      UNREFERENCED_PARAMETER(pSender);
      UNREFERENCED_PARAMETER(lHint);
      ::user::view_update_hint * puh = dynamic_cast < ::user::view_update_hint * > (phint);
   }

   void tileset_view::_001OnDestroy(signal_details * pobj)
   {
      ::user::impact::_001OnDestroy(pobj);
   }

   void tileset_view::layout()
   {

      BASE_VIEW::layout();
      /*   pobj->previous();

      double d = psize->height();
      d /= GetSystemMetrics(SM_CYSCREEN);
      SetScale(d);

      GetClientRect(m_rectKaraokeView);


      rect rectClient;
      GetClientRect(rectClient);
      rect rect = rectClient;

      rect.top = rect.bottom - 24;
      m_viewlineStatus.SetPlacement(rect);


      m_rectKaraokeView.bottom -= 16;

      LayoutTitleLines();
      LayoutLyricTemplateLines();
      LayoutLyricLines();
      LayoutKaraokeBouncingBall();*/
   }

   void tileset_view:: _001OnDraw(::draw2d::graphics * pdc)
   {

      rect rectClient;

      GetClientRect(rectClient);

      if(m_ptileset.is_null())
         return;

      int cx = m_ptileset->width();
      int cy = m_ptileset->height();

      pdc->BitBlt(0,0,cx,cy, m_ptileset->m_dib->get_graphics(),0, 0,SRCCOPY);

      int wm = cx - 1;
      int hm = cy - 1;
      
      ::draw2d::pen_sp pen(allocer());

      pen->create_solid(1.0,ARGB(127,255,255,255));

      pdc->SelectObject(pen);

      for(int x = iTileX; x < cx; x+= iTileX)
      {
         pdc->MoveTo(x, 0);
         pdc->LineTo(x,hm);
      }

      for(int y = iTileY; y < cy; y+= iTileY)
      {
         pdc->MoveTo(0,y);
         pdc->LineTo(wm,y);
      }


   }


   void tileset_view::_001OnCreate(signal_details * pobj)
   {
      if(pobj->previous())
         return;

      SetTimer(123,240,NULL);


   }

   void tileset_view::_001OnContextMenu(signal_details * pobj)
   {
      SCAST_PTR(::message::context_menu,pcontextmenu,pobj);
         point point = pcontextmenu->GetPoint();
   }

   void tileset_view::_001OnTabClick(int32_t iTab)
   {
   }

   void tileset_view::_001OnSetCursor(signal_details * pobj)
   {

      SCAST_PTR(::message::mouse,pmouse,pobj);

      pmouse->m_ecursor = ::visual::cursor_arrow;

      pobj->previous();

   }


   void tileset_view::_001OnEraseBkgnd(signal_details * pobj)
   {
      SCAST_PTR(::message::erase_bkgnd,perasebkgnd,pobj);
         perasebkgnd->m_bRet = true;
      perasebkgnd->set_result(TRUE);
   }

   void tileset_view::_001OnTimer(::timer * ptimer)
   {

      ::user::impact::_001OnTimer(ptimer);

      if(ptimer->m_nIDEvent == 123)
      {

         ::property_set post;
         ::property_set headers;
         string strQuery;
         point pt;
         Session.get_cursor_pos(&pt);
         ScreenToClient(&pt);

      }

   }

   void tileset_view::_001OnMouseMove(signal_details * pobj)
   {

      SCAST_PTR(::message::mouse,pmouse,pobj);

         data * pdata = get_document()->get_typed_data < data>();

      point pt = pmouse->m_pt;

      ScreenToClient(&pt);


   }


   void tileset_view::_001OnLButtonDown(signal_details * pobj)
   {

      SCAST_PTR(::message::mouse,pmouse,pobj);

      pobj->previous();

      point pt = pmouse->m_pt;

      ScreenToClient(&pt);

      pobj->m_bRet = true;

   }


   void tileset_view::_001OnLButtonDblClk(signal_details * pobj)
   {
      SCAST_PTR(::message::mouse,pmouse,pobj);
         point pt = pmouse->m_pt;
      ScreenToClient(&pt);


      pobj->m_bRet = true;

   }


   void tileset_view::_001OnLButtonUp(signal_details * pobj)
   {
      
      SCAST_PTR(::message::mouse,pmouse,pobj);

      pobj->previous();
      
      point pt = pmouse->m_pt;
      
      ScreenToClient(&pt);

      pmouse->m_bRet = true;

   }

   void tileset_view::_001OnSelectionTool(signal_details * pobj)
   {
      data * pdata = get_document()->get_typed_data < data>();
      pdata->m_drawing.m_emode = drawing::mode_selection;
      pobj->m_bRet = true;
   }

   void tileset_view::_001OnUpdateSelectionTool(signal_details * pobj)
   {
      SCAST_PTR(::aura::cmd_ui,pcmdui,pobj);
         pcmdui->m_pcmdui->Enable(TRUE);
   }


   void tileset_view::_001OnPolygonTool(signal_details * pobj)
   {
      pobj->m_bRet = true;
   }

   void tileset_view::_001OnUpdatePolygonTool(signal_details * pobj)
   {
      SCAST_PTR(::aura::cmd_ui,pcmdui,pobj);
         pcmdui->m_pcmdui->Enable(TRUE);
   }

   bool tileset_view::keyboard_focus_is_focusable()
   {

      return true;

   }


   bool tileset_view::keyboard_focus_OnSetFocus()
   {

      if(!::user::impact::keyboard_focus_OnSetFocus())
         return false;

      get_document()->get_typed_view < property_sheet >()->set_data(&m_data);

      return true;

   }

   bool tileset_view::hit_test(int & iTileX,int & iTileY,point pt)
   {

      if(m_ptileset.is_null())
      {

         return false;

      }

      if(m_ptileset->hit_test(iTileX,iTileY,pt))
      {

         return false;

      }

      return true;

   }


   bool tileset_view::initialize(tileset * ptileset)
   {

      m_ptileset = ptileset;

      layout();

   }

   ::size tileset_view::get_total_size()
   {

      return m_ptileset->size();

   }

} // namespace veritile
