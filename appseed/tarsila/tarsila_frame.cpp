#include "framework.h"


namespace tarsila 
{


   frame::frame(::aura::application * papp) :
      element(papp),
      simple_frame_window(papp)
   {
      m_iFrameData = 10;
      m_dataid = "app-core.tarsila.frame";

      WfiEnableFullScreen();

      m_dataidWindow = "WindowData";
   }

   frame::~frame()
   {
   }


#ifdef DEBUG


   void frame::assert_valid() const
   {
      simple_frame_window::assert_valid();
   }

   void frame::dump(dump_context & dumpcontext) const
   {
      simple_frame_window::dump(dumpcontext);
   }


#endif //DEBUG
   void frame::install_message_handling(::message::dispatch * pinterface)
   {
      simple_frame_window::install_message_handling(pinterface);

      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &frame::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_TIMER, pinterface, this, &frame::_001OnTimer);

   }


   void frame::_001OnCreate(signal_details * pobj)
   {

      pobj->previous();

      if (pobj->m_bRet)
         return;

      LoadToolBar("main", "toolbar.xml");

   }



   void frame::_001OnTimer(signal_details * pobj)
   {

      SCAST_PTR(::message::timer, ptimer, pobj)


   }

   bool frame::get_translucency(::user::ETranslucency  & etranslucency)
   {
      
      etranslucency = ::user::TranslucencyPresent;

      return true;

   }



} // namespace tarsila 



