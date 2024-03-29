﻿#include "framework.h"


namespace tarsila
{


   view::view(::aura::application * papp) :
      ::object(papp)
   {



      connect_command("selection_tool", &view::_001OnSelectionTool);
      connect_command_probe("selection_tool", &view::_001OnUpdateSelectionTool);
      connect_command("polygon_tool", &view::_001OnPolygonTool);
      connect_command_probe("polygon_tool", &view::_001OnUpdatePolygonTool);


   }

   view::~view()
   {
   }

   void view::install_message_routing(::message::sender * pinterface)
   {
      ::user::impact::install_message_routing(pinterface);

      IGUI_MSG_LINK(WM_DESTROY, pinterface, this, &view::_001OnDestroy);
      //IGUI_MSG_LINK(WM_SIZE, pinterface, this, &view::_001OnSize);
      IGUI_MSG_LINK(WM_CREATE, pinterface, this, &view::_001OnCreate);
      IGUI_MSG_LINK(WM_CONTEXTMENU, pinterface, this, &view::_001OnContextMenu);
      IGUI_MSG_LINK(WM_SETCURSOR, pinterface, this, &view::_001OnSetCursor);
      IGUI_MSG_LINK(WM_ERASEBKGND, pinterface, this, &view::_001OnEraseBkgnd);
//
      IGUI_MSG_LINK(WM_MOUSEMOVE, pinterface, this, &view::_001OnMouseMove);
      IGUI_MSG_LINK(WM_LBUTTONDOWN, pinterface, this, &view::_001OnLButtonDown);
      IGUI_MSG_LINK(WM_LBUTTONUP, pinterface, this, &view::_001OnLButtonUp);
      IGUI_MSG_LINK(WM_LBUTTONDBLCLK, pinterface, this, &view::_001OnLButtonDblClk);

   }

   void view::assert_valid() const
   {
      ::user::impact::assert_valid();
   }

   void view::dump(dump_context & dumpcontext) const
   {
      ::user::impact::dump(dumpcontext);
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

   void view::_001OnDestroy(::message::message * pobj)
   {
      ::user::impact::_001OnDestroy(pobj);
   }

   void view::on_layout()
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

   void view:: _001OnDraw(::draw2d::graphics * pgraphics)
   {



      rect rectClient;

      GetClientRect(rectClient);

      pgraphics->fill_solid_rect(rectClient,ARGB(184 - 66,184,184,177));

      data * pdata = get_document()->get_typed_data < data>();

      if(pdata == NULL)
         return;

      point_array pta;

      pta = pdata->m_pointa;

      if (m_estate == state_polygon_tool_dots)
      {

         point pt;

         Session.get_cursor_pos(&pt);

         ScreenToClient(&pt);

         pta.add(pt);

      }

      ::draw2d::pen_sp pen(allocer());

      pen->create_solid(1.0,ARGB(184,0,255,0));

      pgraphics->SelectObject(pen);

      ::draw2d::brush_sp br(allocer());

      br->create_solid(ARGB(184,255,255,0));

      pgraphics->SelectObject(br);

      pgraphics->polygon(pta);

      br->create_solid(ARGB(184,255,255,255));

      pdata->m_drawing._001OnDraw(pgraphics);

   }


   void view::_001OnCreate(::message::message * pobj)
   {
      if(pobj->previous())
         return;

      SetTimer(123, 240, NULL);


   }

   void view::_001OnContextMenu(::message::message * pobj)
   {
      SCAST_PTR(::message::context_menu, pcontextmenu, pobj);
      point point = pcontextmenu->GetPoint();
   }

   void view::_001OnTabClick(int32_t iTab)
   {
   }

   void view::_001OnSetCursor(::message::message * pobj)
   {

      SCAST_PTR(::message::mouse, pmouse, pobj);

      pmouse->m_ecursor = ::visual::cursor_arrow;

      pobj->previous();

   }


   void view::_001OnEraseBkgnd(::message::message * pobj)
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

   void view::_001OnMouseMove(::message::message * pobj)
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


   void view::_001OnLButtonDown(::message::message * pobj)
   {

      SCAST_PTR(::message::mouse, pmouse, pobj);

      data * pdata = get_document()->get_typed_data < data>();

      point pt = pmouse->m_pt;

      ScreenToClient(&pt);

      if(pdata->m_drawing.m_emode == drawing::mode_selection)
      {

         ::tarsila::element * pelement = pdata->m_drawing.hit_test(pt);




         if(pelement != NULL)
         {

            if(pdata->m_drawing.m_elementptraSelected.contains(pelement))
            {


               auto iSelPoint = pelement->sel_point_hit_test(pt);

               if(iSelPoint >= 0)
               {

                  if(!pelement->sel_point_selected(iSelPoint))
                  {

                     if(!Session.is_key_pressed(::user::key_control))
                     {

                        pdata->m_drawing.m_elementptraSelected.sel_point_clear();

                     }

                     pelement->sel_point_select(iSelPoint);

                  }

                  pdata->m_drawing.m_bMovingPoint = true;

               }
               else
               {

                  pdata->m_drawing.m_elementptraSelected.sel_point_clear();

                  pdata->m_drawing.m_bMoving = true;

               }

               SetCapture();

               pdata->m_drawing.m_ptStart = pt;

               pdata->m_drawing.m_ptMove = pt;


               m_bMouseDown = true;

            }
            else
            {

               if(!Session.is_key_pressed(::user::key_control))
               {

                  pdata->m_drawing.m_elementptraSelected.remove_all();

               }

               pdata->m_drawing.m_elementptraSelected.add(pelement);

            }

         }
         else
         {
            if(!Session.is_key_pressed(::user::key_control))
            {

               pdata->m_drawing.m_elementptraSelected.remove_all();

            }

         }

      }
      else if(pdata->m_drawing.m_emode == drawing::mode_polygon_tool)
      {

         if(m_estate == state_polygon_tool_initial)
         {

            m_estate = state_polygon_tool_dots;

            pdata->m_pointa.add(pt);

         }
         else if(m_estate == state_polygon_tool_dots)
         {

            pdata->m_pointa.add(pt);

         }

      }

      pobj->m_bRet = true;

   }

   void view::_001OnLButtonDblClk(::message::message * pobj)
   {
      SCAST_PTR(::message::mouse, pmouse, pobj);
      point pt = pmouse->m_pt;
      ScreenToClient(&pt);

      data * pdata = get_document()->get_typed_data < data>();
      if (m_estate == state_polygon_tool_dots)
      {

         m_estate = state_polygon_tool_initial;

         pdata->m_pointa.add(pt);

         sp(polygon) sppolygon(canew(polygon(get_app())));

         sppolygon->m_pointa =pdata->m_pointa;

         pdata->m_drawing.m_polygona.add(sppolygon);

         pdata->m_drawing.m_elementptra.add(sppolygon);

         pdata->m_pointa.remove_all();

      }

      pobj->m_bRet = true;

   }


   void view::_001OnLButtonUp(::message::message * pobj)
   {
      SCAST_PTR(::message::mouse, pmouse, pobj);
      point pt = pmouse->m_pt;
      ScreenToClient(&pt);
      data * pdata = get_document()->get_typed_data < data>();
      if(pdata->m_drawing.m_emode == drawing::mode_selection)
      {

         if(pdata->m_drawing.m_bMoving)
         {

            pdata->m_drawing.m_bMoving = false;

            pdata->m_drawing.m_elementptraSelected.translate(pdata->m_drawing.m_ptMove - pdata->m_drawing.m_ptStart);

         }
         else if(pdata->m_drawing.m_bMovingPoint)
         {

            pdata->m_drawing.m_bMovingPoint = false;

            pdata->m_drawing.m_elementptraSelected.move_to_sel_points(&pdata->m_drawing);


         }


      }

      pmouse->m_bRet = true;

   }

   void view::_001OnSelectionTool(::message::message * pobj)
   {
      data * pdata = get_document()->get_typed_data < data>();
      pdata->m_drawing.m_emode = drawing::mode_selection;
      pobj->m_bRet = true;
   }

   void view::_001OnUpdateSelectionTool(::message::message * pobj)
   {
      SCAST_PTR(::user::command, pcommand, pobj);
      pcommand->Enable(TRUE);
   }


   void view::_001OnPolygonTool(::message::message * pobj)
   {
      data * pdata = get_document()->get_typed_data < data>();
      pdata->m_drawing.m_emode = drawing::mode_polygon_tool;
      pdata->m_pointa.remove_all();
      m_estate = state_polygon_tool_initial;

      pobj->m_bRet = true;
   }

   void view::_001OnUpdatePolygonTool(::message::message * pobj)
   {
      SCAST_PTR(::user::command, pcommand, pobj);
      pcommand->Enable(TRUE);
   }

} // namespace tarsila
