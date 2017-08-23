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
   void frame::install_message_routing(::message::sender * pinterface)
   {
      simple_frame_window::install_message_routing(pinterface);

      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &frame::_001OnCreate);
//      

   }


   void frame::_001OnCreate(::message::message * pobj)
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

   bool frame::get_translucency(::user::e_translucency  & etranslucency)
   {
      
      etranslucency = ::user::translucency_present;

      return true;

   }



} // namespace tarsila 



