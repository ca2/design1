#include "framework.h"


namespace veritile
{


   tileset_view::tileset_view(::aura::application * papp):
      ::object(papp)
   {



      connect_command("selection_tool",&tileset_view::_001OnSelectionTool);
      connect_command_probe("selection_tool",&tileset_view::_001OnUpdateSelectionTool);
      connect_command("polygon_tool",&tileset_view::_001OnPolygonTool);
      connect_command_probe("polygon_tool",&tileset_view::_001OnUpdatePolygonTool);


      m_bMouseDown = false;

   }

   tileset_view::~tileset_view()
   {
   }

   void tileset_view::install_message_routing(::message::sender * pinterface)
   {
      BASE_VIEW::install_message_routing(pinterface);

      IGUI_MSG_LINK(WM_DESTROY,pinterface,this,&tileset_view::_001OnDestroy);
      IGUI_MSG_LINK(WM_SIZE,pinterface,this,&tileset_view::_001OnSize);
      IGUI_MSG_LINK(WM_CREATE,pinterface,this,&tileset_view::_001OnCreate);
      IGUI_MSG_LINK(WM_CONTEXTMENU,pinterface,this,&tileset_view::_001OnContextMenu);
      IGUI_MSG_LINK(WM_SETCURSOR,pinterface,this,&tileset_view::_001OnSetCursor);
      IGUI_MSG_LINK(WM_ERASEBKGND,pinterface,this,&tileset_view::_001OnEraseBkgnd);
      //
      IGUI_MSG_LINK(WM_MOUSEMOVE,pinterface,this,&tileset_view::_001OnMouseMove);
      IGUI_MSG_LINK(WM_LBUTTONDOWN,pinterface,this,&tileset_view::_001OnLButtonDown);
      IGUI_MSG_LINK(WM_LBUTTONUP,pinterface,this,&tileset_view::_001OnLButtonUp);
      IGUI_MSG_LINK(WM_LBUTTONDBLCLK,pinterface,this,&tileset_view::_001OnLButtonDblClk);

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

   void tileset_view::_001OnDestroy(::message::message * pobj)
   {
      ::user::impact::_001OnDestroy(pobj);
   }

   void tileset_view::on_layout()
   {

      BASE_VIEW::on_layout();
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

   void tileset_view::_001OnDrawSel(::draw2d::graphics * pgraphics,const point_array & ptaSel)
   {

      int iTileX = m_ptileset->tilex();

      int iTileY = m_ptileset->tiley();

      for(index i = 0; i < ptaSel.get_size(); i++)
      {

         point pt =  ptaSel[i];

         pgraphics->FillSolidRect(iTileX * pt.x,iTileY * pt.y,iTileX,iTileY,ARGB(127,245,250,255));

      }

   }

   void tileset_view:: _001OnDraw(::draw2d::graphics * pgraphics)
   {



      rect rectClient;

      GetClientRect(rectClient);

      if(m_ptileset.is_null())
         return;

      pgraphics->FillSolidRect(rectClient,ARGB(184,245,250,255));

      int cx = m_ptileset->width();
      int cy = m_ptileset->height();

      pgraphics->BitBlt(0,0,cx,cy, m_ptileset->m_dib->get_graphics(),0, 0,SRCCOPY);

      int wm = cx - 1;
      int hm = cy - 1;

      ::draw2d::pen_sp pen(allocer());

      pen->create_solid(1.0,ARGB(127,255,255,255));

      pgraphics->SelectObject(pen);

      int iTileX = m_ptileset->tilex();

      int iTileY = m_ptileset->tiley();

      for(int x = iTileX; x < cx; x+= iTileX)
      {
         pgraphics->MoveTo(x, 0);
         pgraphics->LineTo(x,hm);
      }

      for(int y = iTileY; y < cy; y+= iTileY)
      {
         pgraphics->MoveTo(0,y);
         pgraphics->LineTo(wm,y);
      }

      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

      if(m_ptileset->m_ptBeg.x >= 0 && m_ptileset->m_ptBeg.y >= 0
            && m_ptileset->m_ptEnd.x >= 0 && m_ptileset->m_ptEnd.y >= 0)
      {

         point_array pta;

         pta = m_ptileset->m_ptaSel;

         pta.add_unique_range(m_ptileset->m_ptBeg,m_ptileset->m_ptEnd);

         _001OnDrawSel(pgraphics,pta);

      }
      else
      {

         _001OnDrawSel(pgraphics,m_ptileset->m_ptaSel);

      }


   }


   void tileset_view::_001OnCreate(::message::message * pobj)
   {
      if(pobj->previous())
         return;

      SetTimer(123,240,NULL);


   }

   void tileset_view::_001OnContextMenu(::message::message * pobj)
   {
      SCAST_PTR(::message::context_menu,pcontextmenu,pobj);
      point point = pcontextmenu->GetPoint();
   }

   void tileset_view::_001OnTabClick(int32_t iTab)
   {
   }

   void tileset_view::_001OnSetCursor(::message::message * pobj)
   {

      SCAST_PTR(::message::mouse,pmouse,pobj);

      pmouse->m_ecursor = ::visual::cursor_arrow;

      pobj->previous();

   }


   void tileset_view::_001OnEraseBkgnd(::message::message * pobj)
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

   void tileset_view::_001OnLButtonDown(::message::message * pobj)
   {

      SCAST_PTR(::message::mouse,pmouse,pobj);

      pobj->previous();

      point pt = pmouse->m_pt;

      ScreenToClient(&pt);

      point ptSel;

      if(hit_test(ptSel,pt))
      {

         if(!Session.is_key_pressed(::user::key_control))
         {

            m_ptileset->m_ptaSel.remove_all();

         }

         m_ptileset->m_ptBeg = ptSel;

         m_ptileset->m_ptEnd = ptSel;

      }

      GetCapture();

      m_bMouseDown = true;

      pobj->m_bRet = true;

   }

   void tileset_view::_001OnMouseMove(::message::message * pobj)
   {

      SCAST_PTR(::message::mouse,pmouse,pobj);

      data * pdata = get_document()->get_typed_data < data>();

      point pt = pmouse->m_pt;

      ScreenToClient(&pt);

      if(m_bMouseDown)
      {

         point pt = pmouse->m_pt;

         ScreenToClient(&pt);

         point ptSel;

         if(hit_test(ptSel,pt))
         {

            m_ptileset->m_ptEnd = ptSel;

         }


      }


   }

   void tileset_view::_001OnLButtonUp(::message::message * pobj)
   {

      SCAST_PTR(::message::mouse,pmouse,pobj);

      pobj->previous();

      if(m_bMouseDown)
      {

         point pt = pmouse->m_pt;

         ScreenToClient(&pt);

         point ptSel;

         if(hit_test(ptSel,pt))
         {

            m_ptileset->m_ptEnd = ptSel;

         }

         ReleaseCapture();

         if(m_ptileset->m_ptBeg.x >= 0 && m_ptileset->m_ptBeg.y >= 0
               && m_ptileset->m_ptEnd.x >= 0 && m_ptileset->m_ptEnd.y >= 0)
         {

            m_ptileset->m_ptaSel.add_unique_range(m_ptileset->m_ptBeg,m_ptileset->m_ptEnd);

            m_ptileset->m_ptBeg = point(-1,-1);
            m_ptileset->m_ptEnd = point(-1,-1);

         }

      }

      pmouse->m_bRet = true;

   }



   void tileset_view::_001OnLButtonDblClk(::message::message * pobj)
   {
      SCAST_PTR(::message::mouse,pmouse,pobj);
      point pt = pmouse->m_pt;
      ScreenToClient(&pt);


      pobj->m_bRet = true;

   }


   void tileset_view::_001OnSelectionTool(::message::message * pobj)
   {
      data * pdata = get_document()->get_typed_data < data>();
//      pdata->m_drawing.m_emode = drawing::mode_place;
      pobj->m_bRet = true;
   }

   void tileset_view::_001OnUpdateSelectionTool(::message::message * pobj)
   {
      SCAST_PTR(::user::command,pcommand,pobj);
      pcommand->Enable(TRUE);
   }


   void tileset_view::_001OnPolygonTool(::message::message * pobj)
   {
      pobj->m_bRet = true;
   }

   void tileset_view::_001OnUpdatePolygonTool(::message::message * pobj)
   {
      SCAST_PTR(::user::command,pcommand,pobj);
      pcommand->Enable(TRUE);
   }

   bool tileset_view::keyboard_focus_is_focusable()
   {

      return true;

   }


   bool tileset_view::keyboard_focus_OnSetFocus()
   {

      if(!::user::impact::keyboard_focus_OnSetFocus())
         return false;

      get_document()->get_typed_view < property_sheet >()->set_data(&m_ptileset->m_data, m_ptileset);

      return true;

   }

   bool tileset_view::hit_test(point & ptTile,point pt)
   {

      if(m_ptileset.is_null())
      {

         return false;

      }

      if(!m_ptileset->hit_test(ptTile,pt))
      {

         return false;

      }

      return true;

   }


   bool tileset_view::initialize(tileset * ptileset)
   {

      m_ptileset = ptileset;

      on_layout();

      return true;

   }

   ::size tileset_view::get_total_size()
   {

      if(m_ptileset.is_null())
         return size(0,0);

      return m_ptileset->size();

   }


} // namespace veritile
