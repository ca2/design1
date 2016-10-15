#include "framework.h"


namespace netnodeds
{


   child_frame::child_frame(::aura::application * papp) :
      ::object(papp),
      simple_child_frame(papp)
   {
      
   }

   void child_frame::install_message_handling(::message::dispatch * pinterface)
   {
      simple_child_frame::install_message_handling(pinterface);
      IGUI_WIN_MSG_LINK(::axis::application::APPM_LANGUAGE, this, this, &child_frame::_001OnAppLanguage);
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &child_frame::_001OnCreate);
   }

   child_frame::~child_frame()
   {
   }

   bool child_frame::on_create_bars()
   {
//      DestroyBars();




      string strModuleFolder;
      strModuleFolder = System.dir().module();


      LoadToolBar(0, "netnodeds_toolbar.xml");

      string str = Application.file().as_string(Application.dir().matter(""));

      on_layout();

      return true;
   }


   void child_frame::_001OnCreate(::signal_details * pobj) 
   {
      pobj->previous();


   }


   void child_frame::_001OnAppLanguage(::signal_details * pobj)
   {
      // xyzxyz || see the code below!! in App Language!!
      on_create_bars();
      pobj->m_bRet = false;
   }


   sp(::filemanager::manager) child_frame::GetFileManager()
   {
      return (GetActiveDocument());
   }

   /*void child_frame::GetSelected(::fs::item_array &itema)
   {
   sp(::filemanager::SimpleFileListInterface) plistinterface = 
   (GetActiveView());
   if(plistinterface != NULL)
   {
   plistinterface->GetSelected(itema);
   }
   }*/


} // namespace netnodeds






