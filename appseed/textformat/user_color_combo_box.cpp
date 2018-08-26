#include "framework.h"

#ifdef WINDOWSEX
#include <Commdlg.h>
#endif


namespace user
{


   color_combo_box::color_combo_box() :
      color_combo_box(get_app())
   {

      m_pview = NULL;
      m_pframe = NULL;
      m_pdoc = NULL;
      m_iHover = -1;
      m_bMouseDown = false;

   }


   color_combo_box::color_combo_box(::aura::application * papp) :
      ::object(papp)
   {


   }


   color_combo_box::~color_combo_box()
   {

   }


   void color_combo_box::install_message_routing(::message::sender * psender)
   {

      ::user::control::install_message_routing(psender);

      IGUI_MSG_LINK(WM_CREATE, psender, this, &::user::color_combo_box::_001OnCreate);
      IGUI_MSG_LINK(WM_LBUTTONDOWN, psender, this, &::user::color_combo_box::_001OnLButtonDown);
      IGUI_MSG_LINK(WM_LBUTTONUP, psender, this, &::user::color_combo_box::_001OnLButtonUp);
      IGUI_MSG_LINK(WM_MOUSEMOVE, psender, this, &::user::color_combo_box::_001OnMouseMove);
      IGUI_MSG_LINK(WM_MOUSELEAVE, psender, this, &::user::color_combo_box::_001OnMouseLeave);
      IGUI_MSG_LINK(WM_SHOWWINDOW, psender, this, &::user::color_combo_box::_001OnShowWindow);

   }


   void color_combo_box::_001OnCreate(::message::message * pmessage)
   {

      SCAST_PTR(::message::create, pcreate, pmessage);

      ::rectd r(2, 2, 2, 2);

      create_rect(::user::rect_edit_padding, r, ::draw2d::unit_pixel);


   }


   void color_combo_box::_001OnLButtonDown(::message::message * pmessage)
   {

      SCAST_PTR(::message::mouse, pmouse, pmessage);

      m_bMouseDown = true;

      SetCapture();

      pmouse->m_bRet = true;

   }

   
   

   void color_combo_box::_001OnLButtonUp(::message::message * pmessage)
   {

      SCAST_PTR(::message::mouse, pmouse, pmessage);

      ReleaseCapture();

      if (m_bMouseDown)
      {

         m_bMouseDown = false;
         
         if(m_pframe != NULL && m_pframe->IsWindowVisible())
         {
            
            m_pframe->ShowWindow(SW_HIDE);
            
         }
         else
         {
         
            
            bool bNew = m_pdoc == NULL;
            
            if(bNew)
            {

               Session.will_use_view_hint("color_sel");
            
               m_pdoc = Session.userex()->m_mapimpactsystem["color_sel"]->open_document_file(get_app(), ::var::type_null, false);
               
               
            
               m_pview = m_pdoc->get_typed_view < ::userex::color_view >();
            
               m_pview->m_bCompact = true;
            
               Session.set_bound_ui("color_sel", this);
            
               m_pframe = m_pview->GetTopLevelFrame()->cast < ::simple_frame_window >();
               
               m_pframe->SetOwner(this);
               
               m_pframe->m_workset.m_ebuttonaHide.add(::user::wndfrm::frame::button_dock);
               m_pframe->m_workset.m_ebuttonaHide.add(::user::wndfrm::frame::button_down);
               m_pframe->m_workset.m_ebuttonaHide.add(::user::wndfrm::frame::button_up);
               m_pframe->m_workset.m_ebuttonaHide.add(::user::wndfrm::frame::button_minimize);

            }

            m_pview->m_hls = m_hls;
               
            if(bNew)
            {
               
               rect rectWindow;
               
               GetWindowRect(rectWindow);
               
               m_pframe->m_sizeMinimum.cx = 300;
               
               m_pframe->m_sizeMinimum.cy = 150;
               
               m_pframe->SetWindowPos(ZORDER_TOPMOST, rectWindow.left, rectWindow.bottom, 400, 200, SWP_SHOWWINDOW);
               
            }
            else
            {
               
               m_pframe->SetWindowPos(ZORDER_TOPMOST, 0, 0, 0, 0,
                                      SWP_NOSIZE | SWP_NOMOVE | SWP_SHOWWINDOW);

            }
            
         }

         pmouse->m_bRet = true;

      }


   }
   
   
   void color_combo_box::on_control_event(::user::control_event * pevent)
   {
      
      if(pevent->m_puie == m_pview)
      {
         
         pevent->m_puie = this;
         
         pevent->m_id = m_id;
         
         m_hls = m_pview->m_hls;
         
      }
      
      ::user::control::on_control_event(pevent);
      
   }
   

   void color_combo_box::_001OnMouseMove(::message::message * pmessage)
   {

      SCAST_PTR(::message::mouse, pmouse, pmessage);


      if (m_iHover != 0)
      {

         m_iHover = 0;

         set_need_redraw();

      }

      track_mouse_leave();

   }


   void color_combo_box::_001OnMouseLeave(::message::message * pmessage)
   {

      SCAST_PTR(::message::mouse, pmouse, pmessage);

      m_iHover = -1;

      set_need_redraw();

   }

   
   void color_combo_box::_001OnShowWindow(::message::message * pmessage)
   {
      
      SCAST_PTR(::message::show_window, pshowwindow, pmessage);

      if(!pshowwindow->m_bShow)
      {
         
         if(m_pframe && m_pframe->IsWindowVisible())
         {
          
            m_pframe->ShowWindow(SW_HIDE);
            
         }
         
      }

      
   }
   
   
   

   void color_combo_box::on_layout()
   {


   }


   void color_combo_box::_001OnDraw(::draw2d::graphics * pgraphics)
   {

      ::draw2d::brush_sp br(allocer());

      ::user::e_color colorDropDown = color_button_background_disabled;

      if (m_pdrawcontext != NULL)
      {

         if (m_pdrawcontext->is_control_selected())
         {

            if (m_pdrawcontext->is_control_hover())
            {

               colorDropDown = color_action_hover_border_color;

            }
            else
            {

               colorDropDown = color_action_hover_border_color;

            }

         }
         else
         {

            if (m_pdrawcontext->is_control_hover())
            {

               colorDropDown = color_action_hover_border_color;

            }
            else
            {

               colorDropDown = color_button_background_disabled;

            }

         }

      }
      else if (!is_window_enabled())
      {

         colorDropDown = color_button_background_disabled;

      }
      else
      {

         if (Session.get_focus_ui() == this)
         {

            if (m_iHover >= 0)
            {

               colorDropDown = color_action_hover_border_color;

            }
            else
            {

               colorDropDown = color_action_hover_border_color;

            }

         }
         else
         {

            if (m_iHover >= 0)
            {

               colorDropDown = color_action_hover_border_color;

            }
            else
            {

               colorDropDown = color_button_background;

            }

         }

      }

      {

         color c(m_hls);

         c.m_uchA = 255;

         ::draw2d::brush_sp b(allocer());

         if (!is_window_enabled())
         {

            c.hls_rate(0.0, 0.4, -0.7);

         }

         b->create_solid(c);

         rect rEdit;

         get_element_rect(rEdit, element_combo_edit);

         {

            color c(_001GetColor(colorDropDown, ARGB(210, 230, 230, 230)));

            c.hls_rate(0.0, 0.6, -0.3);

            pgraphics->fill_solid_rect(rEdit, c.get_rgba());

         }

         {

            color c(_001GetColor(colorDropDown, ARGB(210, 230, 230, 230)));

            c.hls_rate(0.0, 0.3, 0.5);

            pgraphics->draw3d_rect(rEdit, c.get_rgba());

         }

         rect rectPadding = _001GetRect(::user::rect_edit_padding);

         rEdit.deflate(rectPadding);

         pgraphics->fill_solid_rect(rEdit, c.get_rgba());

      }

      rect rectDropDown;

      get_element_rect(rectDropDown, element_drop_down);

      rect rectDropIn(rectDropDown);

      color c(_001GetColor(colorDropDown, ARGB(210, 230, 230, 230)));

      c.hls_rate(0.0, 0.5, 0.1);

      br->create_solid(c);

      pgraphics->SelectObject(br);

      pgraphics->fill_rect(rectDropIn);

      ::draw2d::path_sp path(allocer());

      point_array pointa;

      get_simple_drop_down_open_arrow_polygon(pointa);

      br->create_solid(ARGB(210, 0, 0, 0));

      pgraphics->SelectObject(br);

      pgraphics->fill_polygon(pointa);

   }


} //  namespace user



