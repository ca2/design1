#include "framework.h"


namespace tarsila 
{


   frame::frame(::aura::application * papp) :
      ::object(papp),
      simple_frame_window(papp)
   {

      

      WfiEnableFullScreen();

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
//      

   }


   void frame::_001OnCreate(signal_details * pobj)
   {

      pobj->previous();

      if (pobj->m_bRet)
         return;

      LoadToolBar("main", "toolbar.xml");

   }



   void frame::_001OnTimer(::timer * ptimer)
   {

      simple_frame_window::_001OnTimer(ptimer);


   }

   bool frame::get_translucency(::user::ETranslucency  & etranslucency)
   {
      
      etranslucency = ::user::TranslucencyPresent;

      return true;

   }



} // namespace tarsila 



