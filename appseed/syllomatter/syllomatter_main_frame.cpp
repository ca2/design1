#include "framework.h"


namespace syllomatter
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

   bool main_frame::on_create_bars()
   {
      
      if (!LoadToolBar(0, m_pdocumenttemplate->m_strMatter /  "toolbar.xml"))
      {
         TRACE0("Failed to create toolbar\n");
         return false;      // fail to create
      }

      layout();

      return true;

   }


} // namespace syllomatter



