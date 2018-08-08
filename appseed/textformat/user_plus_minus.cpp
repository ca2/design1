#include "framework.h"


namespace user
{


   plus_minus::plus_minus() :
      plus_minus(get_app())
   {

   }


   plus_minus::plus_minus(::aura::application * papp, bool bLabel) :
      ::object(papp),
      m_still(papp),
      m_buttonMinus(papp),
      m_buttonPlus(papp)
   {

      m_bLabel = true;

      m_i = 100;
      m_iMin = 0;
      m_iMax = 100;
      m_iStep = 5;


   }


   plus_minus::~plus_minus()
   {

   }


   void plus_minus::install_message_routing(::message::sender * psender)
   {

      ::user::control::install_message_routing(psender);

      IGUI_MSG_LINK(WM_CREATE, psender, this, &::user::plus_minus::_001OnCreate);

   }


   void plus_minus::_001OnCreate(::message::message * pmessage)
   {

      SCAST_PTR(::message::create, pcreate, pmessage);

      pcreate->previous();

      if (m_bLabel)
      {

         m_puiLabel = &m_still;

         m_still.create_window(null_rect(), GetParent(), "still_" + m_id);

      }

      m_buttonMinus.create_window(null_rect(), this, m_id + "_minus");

      m_buttonMinus.set_window_text("-");

      m_buttonPlus.create_window(null_rect(), this, m_id + "_plus");

      m_buttonPlus.set_window_text("+");

   }


   void plus_minus::set_value(int iValue, ::action::context context)
   {

      m_i = iValue;

      on_update();

      ::user::control_event event;

      event.m_eevent = ::user::event_action;
      event.m_puie = this;
      event.m_id = m_id;
      event.m_actioncontext = context;

      on_control_event(&event);

   }


   void plus_minus::on_update()
   {

      int i = m_i;

      ::sort::sort(m_iMin, m_iMax);

      if (m_iStep <= 0)
      {

         m_iStep = 1;

      }

      i = m_iMin + (i - m_iMin) / m_iStep * m_iStep;

      if (m_iMin == m_iMax)
      {

         i = m_iMin;

         m_buttonMinus.enable_window(false);
         m_buttonPlus.enable_window(false);

      }
      else if (i <= m_iMin)
      {

         i = m_iMin;

         m_buttonMinus.enable_window(false);
         m_buttonPlus.enable_window(true);

      }
      else if (i >= m_iMax)
      {

         i = m_iMax;

         m_buttonMinus.enable_window(true);
         m_buttonPlus.enable_window(false);

      }
      else
      {

         m_buttonMinus.enable_window(true);
         m_buttonPlus.enable_window(true);

      }

      m_i = i;

      if (m_bLabel)
      {

         m_still.set_window_text(calc_still_label());

      }

   }


   string plus_minus::calc_still_label()
   {

      ::sort::sort(m_iMin, m_iMax);

      if (m_i >= m_iMax)
      {

         if (m_strMax.has_char())
         {

            return m_strMax;

         }

      }
      else if (m_i <= m_iMin)
      {

         if (m_strMin.has_char())
         {

            return m_strMin;

         }

      }

      if (m_strFormat.has_char())
      {

         string str;

         str.Format(m_strFormat, m_i);

         return str;

      }

      return "";

   }


   void plus_minus::on_layout()
   {

      int wPadding = 10;

      rect rectClient;

      GetClientRect(rectClient);

      int iM = rectClient.center().x;

      rect rL(rectClient);

      rL.right = iM - wPadding / 2;

      m_buttonMinus.SetWindowPos(ZORDER_TOP, rL, SWP_SHOWWINDOW);

      rect rR(rectClient);

      rR.left = iM + wPadding / 2;

      m_buttonPlus.SetWindowPos(ZORDER_TOP, rR, SWP_SHOWWINDOW);

   }



   void plus_minus::on_control_event(::user::control_event * pevent)
   {

      if (pevent->m_eevent == ::user::event_button_clicked)
      {

         if (pevent->m_puie == &m_buttonMinus || pevent->m_puie == &m_buttonPlus)
         {

            int i = m_i;

            if (m_iStep <= 0)
            {

               m_iStep = 1;

            }

            if (pevent->m_puie == &m_buttonMinus)
            {

               i -= m_iStep;

            }
            else
            {

               i += m_iStep;

            }

            set_value(i, ::action::source_user);

            pevent->m_bRet = true;

            return;

         }

      }

      ::user::control::on_control_event(pevent);

   }


} //  namespace user



