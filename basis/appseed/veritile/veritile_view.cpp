#include "framework.h"


namespace veritile
{


   view::view(::aura::application * papp) :
      ::object(papp)
   {

      m_emode = mode_place;

      connect_command("tool_place", &view::_001OnModePlace);
      connect_update_cmd_ui("tool_place", &view::_001OnUpdateModePlace);
      connect_command("tool_random", &view::_001OnModeRandom);
      connect_update_cmd_ui("tool_random", &view::_001OnUpdateModeRandom);
      // connect_command("selection_tool", &view::_001OnSelectionTool);

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

      return MAX(1,abs(get_data()->m_data.m_set["tilex"].int32()));

   }

   int view::tiley()
   {

      return MAX(1,abs(get_data()->m_data.m_set["tiley"].int32()));

   }

   int view::xcount()
   {

      return MAX(1,abs(get_data()->m_data.m_set["xcount"].int32()));

   }

   int view::ycount()
   {

      return MAX(1,abs(get_data()->m_data.m_set["ycount"].int32()));

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

      if (lHint == 0)
      {

         get_data()->m_data.m_set["tilex"] = 20;
         get_data()->m_data.m_map["tilex"].m_validate.m_rules["natural"] = true;
         get_data()->m_data.m_map["tilex"].m_validate.m_rules["m_iMin"] = 16;
         get_data()->m_data.m_map["tilex"].m_validate.m_rules["m_iMax"] = 256;


         get_data()->m_data.m_set["tiley"] = 20;
         get_data()->m_data.m_map["tiley"].m_validate.m_rules["natural"] = true;
         get_data()->m_data.m_map["tiley"].m_validate.m_rules["m_iMin"] = 16;
         get_data()->m_data.m_map["tiley"].m_validate.m_rules["m_iMax"] = 256;


         get_data()->m_data.m_set["xcount"] = 20;
         get_data()->m_data.m_map["xcount"].m_validate.m_rules["natural"] = true;
         get_data()->m_data.m_map["xcount"].m_validate.m_rules["m_iMin"] = 1;
         get_data()->m_data.m_map["xcount"].m_validate.m_rules["m_iMax"] = 1024;


         get_data()->m_data.m_set["ycount"] = 20;
         get_data()->m_data.m_map["ycount"].m_validate.m_rules["natural"] = true;
         get_data()->m_data.m_map["ycount"].m_validate.m_rules["m_iMin"] = 1;
         get_data()->m_data.m_map["ycount"].m_validate.m_rules["m_iMax"] = 1024;

         update_layer();

      }
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

   void view:: _001OnDraw(::draw2d::dib * pdib)
   {

      ::draw2d::graphics * pdc = pdib->get_graphics();
      
      rect rectClient;

      GetClientRect(rectClient);

      pdc->FillSolidRect(rectClient,ARGB(128,184,188,184));
      
      for (auto & player : get_data()->m_spalayer)
      {
       
         draw_layer(pdc, *player);

      }

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

      get_document()->get_typed_view < property_sheet >()->set_data(&get_data()->m_data,this);

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

      if(m_bMouseDown)
      {

         point ptLayer;

         if (hit_test(ptLayer, pt))
         {

            if (m_ptMove != ptLayer)
            {
             
               m_ptMove = ptLayer;

               do_place(ptLayer, 0);


            }

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

      m_bMouseDown = true;

      point ptLayer;

      if(hit_test(ptLayer,pt))
      {

         do_place(ptLayer,0);

      }




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

      m_bMouseDown = false;

   }

   void view::_001OnModePlace(signal_details * pobj)
   {
      //data * pdata = get_document()->get_typed_data < data>();
      m_emode = mode_place;
      pobj->m_bRet = true;
   }

   void view::_001OnUpdateModePlace(signal_details * pobj)
   {
      SCAST_PTR(::aura::cmd_ui, pcmdui, pobj);
         pcmdui->m_pcmdui->Enable(m_emode != mode_place);
   }


   void view::_001OnModeRandom(signal_details * pobj)
   {
      m_emode = mode_random;
      pobj->m_bRet = true;
   }

   void view::_001OnUpdateModeRandom(signal_details * pobj)
   {
      SCAST_PTR(::aura::cmd_ui, pcmdui, pobj);
         pcmdui->m_pcmdui->Enable(m_emode != mode_random);
   }

   void view::on_property_change(property & property)
   {

      if(property.m_element1 == "xcount")
      {

         update_layer();

      }
      else if(property.m_element1 == "ycount")
      {

         update_layer();

      }



   }

   

   tileset_view * view::get_cur_tileset_view()
   {

      if(get_document() == NULL)
      {

         return NULL;

      }

      tileset_pane_view * ppaneview = get_document()->get_typed_view < tileset_pane_view >();

      if(ppaneview == NULL)
      {

         return NULL;

      }

      ::user::tab_pane * ppane = ppaneview->get_pane_by_id(ppaneview->get_cur_tab_id());

      if(ppane == NULL)
      {

         return NULL;

      }

      if(ppane->m_pholder.is_null())
      {

         return NULL;

      }

      ::user::interaction * pui = ppane->m_pholder->top_child();

      if(pui == NULL)
      {

         return NULL;

      }

      tileset_view * pview = dynamic_cast <tileset_view *> (pui);

      if(pview == NULL)
      {

         return NULL;

      }

      return pview;

   }

   tileset * view::get_cur_tileset()
   {

      tileset_view * pview = get_cur_tileset_view();

      if(pview == NULL)
      {

         return NULL;

      }

      return pview->m_ptileset;

   }



   void view::update_layer()
   {

      get_data()->m_spalayer[0]->update(xcount(),ycount());

   }


   bool view::hit_test(point & ptTile,point pt)
   {

      ptTile.x =  pt.x / tilex();

      ptTile.y =  pt.y / tiley();

      if(ptTile.x < 0)
         return false;

      if(ptTile.y < 0)
         return false;

      if(ptTile.x >= xcount())
         return false;

      if(ptTile.y >= ycount())
         return false;

      return true;

   }


   void view::draw_layer(::draw2d::graphics * pdc,layer & l)
   {

      int iTileX = tilex();

      int iTileY = tiley();

      for(int y = 0; y < l.m_size.cy; y++)
      {

         for(int x = 0; x < l.m_size.cx; x++)
         {

            layer::tile & tile = l.m_tile2a[y][x];

            if(tile.m_iTile >= 0)
            {

               tileset * pset = get_cur_tileset();

               pdc->BitBlt(x * iTileX,y * iTileY,MIN(iTileX,pset->tilex()),MIN(iTileY,pset->tiley()),
                  pset->m_dib->get_graphics(),
                  tile.m_pt.x * pset->tilex(),
                  tile.m_pt.y * pset->tiley(),SRCCOPY);

            }

         }

      }

   }



   void view::do_place(point pt, int iTile)
   {

      tileset * pset = get_cur_tileset();

      if (pset == NULL || !pset->m_ptaSel.has_elements())
      {

         return;

      }

      if (m_emode == mode_place)
      {

         point ptMin(0x7fffffff, 0x7fffffff);
         for (auto & ptSel : pset->m_ptaSel)
         {

            ptMin.x = MIN(ptMin.x, ptSel.x);
            ptMin.y = MIN(ptMin.y, ptSel.y);

         }

         

         for (auto & ptSel : pset->m_ptaSel)
         {
            
            point ptRel = ptSel - ptMin;
            
            point ptNew = pt + ptRel;

            get_data()->m_spalayer[0]->m_tile2a[ptNew.y][ptNew.x].m_iTile = iTile;

            get_data()->m_spalayer[0]->m_tile2a[ptNew.y][ptNew.x].m_pt = ptSel;

         }

      }
      else if (m_emode == mode_random)
      {

         get_data()->m_spalayer[0]->m_tile2a[pt.y][pt.x].m_iTile = iTile;

         get_data()->m_spalayer[0]->m_tile2a[pt.y][pt.x].m_pt = pset->pick_random_from_sel();

      }

   }


} // namespace veritile
