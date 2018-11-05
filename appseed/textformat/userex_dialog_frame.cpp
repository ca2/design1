#include "framework.h"


namespace userex
{


   dialog_frame::dialog_frame(::aura::application * papp) :
      object(papp),
      simple_frame_window(papp)
   {

      m_bDefaultCreateToolbar = false;

      m_bTransparentFrameEnable = false;

      WfiEnableFullScreen();

      m_bWindowFrame = !Application.handler()->m_varTopicQuery.has_property("client_only");



      if (Application.handler()->m_varTopicQuery.has_property("opaque"))
      {

         m_bExplicitTranslucency = true;

         m_etranslucency = ::user::translucency_none;

      }
      else
      {

         m_bExplicitTranslucency = false;

      }



   }


   dialog_frame::~dialog_frame()
   {

   }


   void dialog_frame::assert_valid() const
   {

      simple_frame_window::assert_valid();

   }


   void dialog_frame::dump(dump_context & dumpcontext) const
   {

      simple_frame_window::dump(dumpcontext);

   }


   bool dialog_frame::pre_create_window(::user::create_struct& cs)
   {

      if (!simple_frame_window::pre_create_window(cs))
      {

         return false;

      }

      cs.style &= ~WS_CHILD;
      cs.dwExStyle |= WS_EX_TOOLWINDOW;
      cs.dwExStyle |= WS_EX_TOPMOST;


      return true;

   }

   void dialog_frame::install_message_routing(::message::sender * psender)
   {

      ::simple_frame_window::install_message_routing(psender);

      IGUI_MSG_LINK(WM_CREATE, psender, this, &dialog_frame::_001OnCreate);
      //IGUI_MSG_LINK(WM_ACTIVATE, psender, this, &combo_list::_001OnActivate);
      IGUI_MSG_LINK(WM_MOUSEACTIVATE, psender, this, &dialog_frame::_001OnMouseActivate);

   }


   void dialog_frame::_001OnActivate(::message::message * pobj)
   {

      SCAST_PTR(::message::activate, pactivate, pobj);

      sp(::user::interaction) pActive = (pactivate->m_nState == WA_INACTIVE ? pactivate->m_pWndOther : this);

      if (pactivate->m_nState == WA_INACTIVE)
      {

         point ptCursor;

         Session.get_cursor_pos(&ptCursor);

         //m_pcombo->ScreenToClient(&ptCursor);

         //if(m_pcombo->hit_test(ptCursor) != element_drop_down)
         //{

         //   m_pcombo->_001ShowDropDown(false);

         //}




         //if(pActive != m_puiDeactivateTogether)
         //{

         //   ::user::wndfrm::frame::WorkSet * pset = m_puiDeactivateTogetherSet;

         //   if(pset != NULL)
         //   {

         //      pset->SetActiveFlag(FALSE);

         //   }

         //}



      }
      else
      {

         //Session.set_keyboard_focus(this);


      }



      //m_pcombo->_001ShowDropDown(false);

      //}

   }

   void dialog_frame::_001OnMouseActivate(::message::message * pobj)
   {

      SCAST_PTR(::message::mouse_activate, pactivate, pobj);

      pactivate->m_lresult = MA_NOACTIVATE;

      pactivate->m_bRet = true;


   }


   void dialog_frame::_001OnCreate(::message::message * pobj)
   {

      if (pobj->previous())
      {

         return;

      }
      ModifyStyleEx(0, WS_EX_TOOLWINDOW, SWP_FRAMECHANGED);

   }


   sp(::user::wndfrm::frame::frame) dialog_frame::create_frame_schema()
   {



      //sp(::user::wndfrm::dialog_frame::dialog_frame) pschema = Application.wndfrm()->get_frame_schema("wndfrm_core", "001");

      sp(::user::wndfrm::frame::frame) pschema = Application.wndfrm()->get_frame_schema(NULL, "013");

      pschema->set_style("LightBlue");

      //       // pschema->m_typeinfoControlBoxButton = System.type_info < MetaButton > ();

      return pschema;

   }

   bool dialog_frame::has_pending_graphical_update()
   {

      return m_bRedraw;

   }


   //bool dialog_frame::get_translucency(::user::e_translucency & etranslucency, ::user::e_element eelement, ::user::interaction * pui)
   //{

   //   if (m_bExplicitTranslucency)
   //   {

   //      etranslucency = m_etranslucency;

   //      return true;

   //   }

   //   //if (userstyle() != NULL)
   //   //{

   //   //   if (m_puserstyle->_001GetMainFrameTranslucency(etranslucency))
   //   //      return true;

   //   //}
   //   //etranslucency = ::user::translucency_present;

   //   ////      etranslucency = ::user::translucency_none;

   //   //return true;

   //   return ::user::style::get_translucency(etranslucency, eelement, pui);

   //}


} // namespace userex







