#include "framework.h"


namespace tarsila
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


   bool main_frame::get_translucency(::user::e_translucency & etranslucency)
   {

      etranslucency = ::user::translucency_present;

      return true;

   }


} // namespace syllomatter
































