#include "framework.h"


namespace textformat
{


   frame::frame(::aura::application * papp) :
      object(papp),
      simple_frame_window(papp)
   {

      m_bDefaultCreateToolbar = false;

   }


   frame::~frame()
   {

   }


   void frame::assert_valid() const
   {

      simple_frame_window::assert_valid();

   }


   void frame::dump(dump_context & dumpcontext) const
   {

      simple_frame_window::dump(dumpcontext);

   }


   bool frame::get_translucency(::user::e_translucency & etranslucency)
   {

      etranslucency = ::user::translucency_present;

      return true;

   }


} // namespace textformat







