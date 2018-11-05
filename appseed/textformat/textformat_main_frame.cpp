#include "framework.h"


namespace textformat
{


   main_frame::main_frame(::aura::application * papp) :
      object(papp),
      simple_frame_window(papp)
   {

      m_pcompositeview = NULL;

      m_bDefaultCreateToolbar = false;

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


   main_frame::~main_frame()
   {

   }


   void main_frame::assert_valid() const
   {

      simple_frame_window::assert_valid();

   }


   void main_frame::dump(dump_context & dumpcontext) const
   {

      simple_frame_window::dump(dumpcontext);

   }


   sp(::user::wndfrm::frame::frame) main_frame::create_frame_schema()
   {



      //sp(::user::wndfrm::main_frame::main_frame) pschema = Application.wndfrm()->get_frame_schema("wndfrm_core", "001");

      sp(::user::wndfrm::frame::frame) pschema = Application.wndfrm()->get_frame_schema(NULL, "013");

      pschema->set_style("LightBlue");

      //       // pschema->m_typeinfoControlBoxButton = System.type_info < MetaButton > ();

      return pschema;

   }

   bool main_frame::has_pending_graphical_update()
   {

      return IsWindowVisible();

   }


   void main_frame::install_message_routing(::message::sender * psender)
   {

      simple_frame_window::install_message_routing(psender);

      IGUI_MSG_LINK(WM_ACTIVATE, psender, this, &main_frame::_001OnActivate);
      IGUI_MSG_LINK(WM_MOUSEACTIVATE, psender, this, &main_frame::_001OnMouseActivate);

   }

   void main_frame::_001OnMouseActivate(::message::message * pmessage)
   {

      SCAST_PTR(::message::mouse_activate, pmouseactivate, pmessage);

      pmouseactivate->set_lresult(MA_ACTIVATEANDEAT);

      pmouseactivate->m_bRet = true;

   }

   void main_frame::_001OnActivate(::message::message * pmessage)
   {

      SCAST_PTR(::message::activate, pactivate, pmessage);

      if (pactivate->m_nState)
      {

         if (m_pcompositeview != NULL)
         {

            m_pcompositeview->SetFocus();

         }

      }

   }

   bool  main_frame::on_create_bars()
   {

      if (!LoadToolBar("main", "main_toolbar.xml"))
      {

         return false;

      }

      //sp(simple_toolbar) p = m_toolbarmap["main"];

      //if (p.is_set())
      //{

      //   p->m_sizeSpacing.cx = 8;

      //   p->m_rectItemPad.set(9, 9);

      //   p->m_rectBorder.set(9, 9);

      //}

      return true;

   }



} // namespace textformat








