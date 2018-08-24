#include "framework.h"

#ifdef WINDOWSEX
#include <Commdlg.h>
#endif


namespace user
{


   color_combo_box::color_combo_box() :
      color_combo_box(get_app())
   {

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

#ifdef WINDOWSEX
         fork([this]()
         {

            CHOOSECOLOR cc;
            COLORREF crCustColors[16];

            // init-int this array did not affect the mouse problem
            // uint idx ;
            // for (idx=0; idx<16; idx++) {
            // crCustColors[idx] = RGB(idx, idx, idx) ;
            // }

            ::color c(m_hls);

            ZeroMemory(&cc, sizeof(cc));
            cc.lStructSize = sizeof(CHOOSECOLOR);
            cc.rgbResult = c.get_rgb();
            cc.lpCustColors = crCustColors;
            cc.Flags = CC_RGBINIT | CC_FULLOPEN;
            cc.hwndOwner = get_safe_handle(); // this hangs parent, as well as me

            if (::ChooseColor(&cc))
            {

               c.set_COLORREF(cc.rgbResult | (255 << 24));

               c.get_hls(m_hls);

               ::user::control_event event;

               event.m_eevent = ::user::event_action;
               event.m_puie = this;
               event.m_id = m_id;
               event.m_actioncontext = ::action::source_user;

               on_control_event(&event);

            }

         });
#endif

         pmouse->m_bRet = true;

      }


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



