#include "framework.h"


namespace netnodeds
{


   main_frame::main_frame(::aura::application * papp) :
      ::object(papp),
      simple_frame_window(papp)
   {



      WfiEnableFullScreen();

   }


   main_frame::~main_frame()
   {
   }

   void main_frame::_001OnCreate(::message::message * pobj)
   {

      UNREFERENCED_PARAMETER(pobj);

      SetTimer(8913, 5000, 0);
      SetTimer(4033, 100, 0);
      ModifyStyleEx(WS_EX_OVERLAPPEDWINDOW, 0);

   }

   void main_frame::install_message_routing(::message::sender * pinterface)
   {
      simple_frame_window::install_message_routing(pinterface);
      IGUI_MSG_LINK(WM_CREATE, pinterface, this, &main_frame::_001OnClose);
      IGUI_MSG_LINK(WM_CLOSE,          pinterface, this, &main_frame::_001OnClose);
   }

   void main_frame::_001OnClose(::message::message * pobj)
   {

   }

   bool main_frame::pre_create_window(::user::create_struct& cs)
   {

      if( !simple_frame_window::pre_create_window(cs) )
         return FALSE;

      cs.dwExStyle &= ~WS_EX_WINDOWEDGE;

      return TRUE;

   }



   void main_frame::assert_valid() const
   {
      simple_frame_window::assert_valid();
   }

   void main_frame::dump(dump_context & dumpcontext) const
   {
      simple_frame_window::dump(dumpcontext);
   }





   void main_frame::_001OnTimer(::timer * ptimer)
   {
      simple_frame_window::_001OnTimer(ptimer);

   }


   void main_frame::ShowControlBars(bool bShow)
   {
      uint32_t nShow;
      if(bShow)
      {
         nShow = SW_SHOW;
      }
      else
      {
         nShow = SW_HIDE;
      }

      /*   m_toolbar.ShowWindow(nShow);
         m_toolbarView.ShowWindow(nShow);
      //   m_statusbar.ShowWindow(nShow);
         m_menubar.ShowWindow(nShow);
         m_dialogbar.ShowWindow(nShow);*/

   }


   bool main_frame::is_application_main_window()
   {
      return true;
   }


} // namespace netnodeds


