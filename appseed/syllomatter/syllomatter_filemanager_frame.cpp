#include "framework.h"



namespace syllomatter
{


   filemanager_frame::filemanager_frame(::aura::application * papp) :
      ::object(papp),
      simple_frame_window(papp),
      ::filemanager::frame (papp)
   {
   }

   filemanager_frame::~filemanager_frame()
   {
   }


} //  namespace syllomatter






