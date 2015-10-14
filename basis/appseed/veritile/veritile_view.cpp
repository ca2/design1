#include "framework.h"


namespace veritile
{


   view::view(::aura::application * papp) :
      ::object(papp),
      m_data(papp)
   {

      

      connect_command("selection_tool", &view::_001OnSelectionTool);
      connect_update_cmd_ui("selection_tool", &view::_001OnUpdateSelectionTool);
      connect_command("polygon_tool", &view::_001OnPolygonTool);
      connect_update_cmd_ui("polygon_tool", &view::_001OnUpdatePolygonTool);


   }

   view::~view()
   {
   }

   void view::install_message_handling(::message::dispatch * pinterface)
   {
      ::user::impact::install_message_handling(pinterface);

      IGUI_WIN_MSG_LINK(WM_DESTROY, pinterface, this, &view::_001OnDestroy);
      IGUI_WIN_MSG_LINK(WM_SIZE, pinterface, this, &view::_001OnSize);
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &view::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_CONTEXTMENU, pinterface, this, &view::_001OnContextMenu);
      IGUI_WIN_MSG_LINK(WM_SETCURSOR, pinterface, this, &view::_001OnSetCursor);
      IGUI_WIN_MSG_LINK(WM_ERASEBKGND, pinterface, this, &view::_001OnEraseBkgnd);
//      
      IGUI_WIN_MSG_LINK(WM_MOUSEMOVE, pinterface, this, &view::_001OnMouseMove);
      IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN, pinterface, this, &view::_001OnLButtonDown);
      IGUI_WIN_MSG_LINK(WM_LBUTTONUP, pinterface, this, &view::_001OnLButtonUp);
      IGUI_WIN_MSG_LINK(WM_LBUTTONDBLCLK, pinterface, this, &view::_001OnLButtonDblClk);

   //   IGUI_WIN_MSG_LINK(WM_USER + 177     , this, this, &view::_001OnTabClick);
   //   IGUI_WIN_MSG_LINK(WM_APP + 119      , this, this, &view::_001OnWavePlayerEvent);
      //connect_command(ID_FILE_PRINT, ::user::impact::OnFilePrint)
      //connect_command(ID_FILE_PRINT_DIRECT, ::user::impact::OnFilePrint)
      //connect_command(ID_FILE_PRINT_PREVIEW, ::user::impact::OnFilePrintPreview)


   }

   #ifdef DEBUG
   void view::assert_valid() const
   {
      ::user::impact::assert_valid();
   }

   void view::dump(dump_context & dumpcontext) const
   {
      ::user::impact::dump(dumpcontext);
   }
   #endif 

   int view::tilex()
   {

      return MAX(1,abs(m_data.m_set["tilex"].int32()));

   }

   int view::tiley()
   {

      return MAX(1,abs(m_data.m_set["tiley"].int32()));

   }

   int view::xcount()
   {

      return MAX(1,abs(m_data.m_set["xcount"].int32()));

   }

   int view::ycount()
   {

      return MAX(1,abs(m_data.m_set["ycount"].int32()));

   }

   int view::width()
   {

      return xcount() * tilex();

   }

   int view::height()
   {

      return ycount() * tiley();

   }

   ::size view::size()
   {

      return ::size(width(),height());

   }

   bool view::pre_create_window(::user::create_struct& cs)
   {

      cs.style &= ~WS_EX_CLIENTEDGE;

      return ::user::impact::pre_create_window(cs);

   }


   void view::_001OnInitialUpdate() 
   {
      ::user::impact::_001OnInitialUpdate();

   }

   void view::on_update(::user::impact * pSender, LPARAM lHint, ::object* phint) 
   {
      UNREFERENCED_PARAMETER(pSender);
      UNREFERENCED_PARAMETER(lHint);
      ::user::view_update_hint * puh = dynamic_cast < ::user::view_update_hint * > (phint);
   }

   void view::_001OnDestroy(signal_details * pobj) 
   {
      ::user::impact::_001OnDestroy(pobj);
   }

   void view::layout() 
   {


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

   void view:: _001OnDraw(::draw2d::graphics * pdc)
   {


      rect rectClient;

      GetClientRect(rectClient);


      pdc->FillSolidRect(rectClient,ARGB(128,184,188,184));


      ::draw2d::pen_sp pen(allocer());

      pen->create_solid(1.0,ARGB(127,255,255,255));

      pdc->SelectObject(pen);

      int cx = width();
      int cy = height();

//      pdc->BitBlt(0,0,cx,cy,m_ptileset->m_dib->get_graphics(),0,0,SRCCOPY);

      int wm = cx - 1;
      int hm = cy - 1;

      
      int iTileX = tilex();

      int iTileY = tiley();

      for(int x = iTileX; x < cx; x+= iTileX)
      {
         pdc->MoveTo(x,0);
         
         pdc->LineTo(x,hm);

      }

      for(int y = iTileY; y < cy; y+= iTileY)
      {
         
         pdc->MoveTo(0,y);

         pdc->LineTo(wm,y);

      }



   }


   void view::_001OnCreate(signal_details * pobj) 
   {

      if(pobj->previous())
         return;
      
      SetTimer(123, 240, NULL);

      m_data.m_set["tilex"] = 20;
      m_data.m_map["tilex"].m_validate.m_rules["natural"] = true;
      m_data.m_map["tilex"].m_validate.m_rules["m_iMin"] = 16;
      m_data.m_map["tilex"].m_validate.m_rules["m_iMax"] = 256;


      m_data.m_set["tiley"] = 20;
      m_data.m_map["tiley"].m_validate.m_rules["natural"] = true;
      m_data.m_map["tiley"].m_validate.m_rules["m_iMin"] = 16;
      m_data.m_map["tiley"].m_validate.m_rules["m_iMax"] = 256;


      m_data.m_set["xcount"] = 20;
      m_data.m_map["xcount"].m_validate.m_rules["natural"] = true;
      m_data.m_map["xcount"].m_validate.m_rules["m_iMin"] = 1;
      m_data.m_map["xcount"].m_validate.m_rules["m_iMax"] = 1024;


      m_data.m_set["ycount"] = 20;
      m_data.m_map["ycount"].m_validate.m_rules["natural"] = true;
      m_data.m_map["ycount"].m_validate.m_rules["m_iMin"] = 1;
      m_data.m_map["ycount"].m_validate.m_rules["m_iMax"] = 1024;



   }


   void view::_001OnContextMenu(signal_details * pobj) 
   {
      SCAST_PTR(::message::context_menu, pcontextmenu, pobj);
      point point = pcontextmenu->GetPoint();
   }

   void view::_001OnTabClick(int32_t iTab)
   {
   }

   
   bool view::keyboard_focus_is_focusable()
   {
   
      return true;

   }


   bool view::keyboard_focus_OnSetFocus()
   {

      if(!::user::impact::keyboard_focus_OnSetFocus())
         return false;

      get_document()->get_typed_view < property_sheet >()->set_data(&m_data,this);

      return true;

   }


   void view::_001OnSetCursor(signal_details * pobj) 
   {

      SCAST_PTR(::message::mouse, pmouse, pobj);

      pmouse->m_ecursor = ::visual::cursor_arrow;
      
      pobj->previous();

   }


   void view::_001OnEraseBkgnd(signal_details * pobj) 
   {
      SCAST_PTR(::message::erase_bkgnd, perasebkgnd, pobj);
      perasebkgnd->m_bRet = true;
      perasebkgnd->set_result(TRUE);
   }

   void view::_001OnTimer(::timer * ptimer) 
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

   void view::_001OnMouseMove(signal_details * pobj) 
   {
      
      SCAST_PTR(::message::mouse, pmouse, pobj);

      data * pdata = get_document()->get_typed_data < data>();
      
      point pt = pmouse->m_pt;
      
      ScreenToClient(&pt);

      if(pdata->m_drawing.m_emode == drawing::mode_selection)
      {

         if(m_bMouseDown && (pdata->m_drawing.m_bMoving || pdata->m_drawing.m_bMovingPoint))
         {

            pdata->m_drawing.m_ptMove = pt;

         }
         
      }
      else if(pdata->m_drawing.m_emode == drawing::mode_polygon_tool)
      {

         if (m_estate == state_polygon_tool_initial)
         {

            pobj->m_bRet = true;

         }
         else if (m_estate == state_polygon_tool_dots)
         {

            pobj->m_bRet = true;

         }

      }

   }


   void view::_001OnLButtonDown(signal_details * pobj) 
   {

      SCAST_PTR(::message::mouse,pmouse,pobj);

      pobj->previous();

      point pt = pmouse->m_pt;

      ScreenToClient(&pt);

      pobj->m_bRet = true;



   }


   void view::_001OnLButtonDblClk(signal_details * pobj)
   {
      
      SCAST_PTR(::message::mouse, pmouse, pobj);
      
      pobj->previous();

      point pt = pmouse->m_pt;

      ScreenToClient(&pt);

      pobj->m_bRet = true;


   }


   void view::_001OnLButtonUp(signal_details * pobj) 
   {
      SCAST_PTR(::message::mouse, pmouse, pobj);
      point pt = pmouse->m_pt;
      ScreenToClient(&pt);

   }

   void view::_001OnSelectionTool(signal_details * pobj)
   {
      data * pdata = get_document()->get_typed_data < data>();
      pdata->m_drawing.m_emode = drawing::mode_selection;
      pobj->m_bRet = true;
   }

   void view::_001OnUpdateSelectionTool(signal_details * pobj)
   {
      SCAST_PTR(::aura::cmd_ui, pcmdui, pobj);
         pcmdui->m_pcmdui->Enable(TRUE);
   }


   void view::_001OnPolygonTool(signal_details * pobj)
   {
      data * pdata = get_document()->get_typed_data < data>();
      pdata->m_drawing.m_emode = drawing::mode_polygon_tool;
      pdata->m_pointa.remove_all();
      m_estate = state_polygon_tool_initial;

      pobj->m_bRet = true;
   }

   void view::_001OnUpdatePolygonTool(signal_details * pobj)
   {
      SCAST_PTR(::aura::cmd_ui, pcmdui, pobj);
         pcmdui->m_pcmdui->Enable(TRUE);
   }

   void view::on_property_change(property & property)
   {

   }


} // namespace veritile
