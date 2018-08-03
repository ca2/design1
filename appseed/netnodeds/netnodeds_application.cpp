#include "framework.h"


namespace netnodeds
{


   application::application()
   {

   }


   application::~application()
   {

      m_pnetnodeds = NULL;

   }


   void application::construct()
   {

      m_strAppName         = "netnodeds";
      m_strBaseSupportId   = "ca2_netnodeds";
      m_strInstallToken    = "netnodeds";
      m_ppaneview          = NULL;

      m_pnetnodeds = new ::netnodeds::netnodeds(this);

      m_pnetnodeds->construct(this);

      m_pnetnodeds->connect_to_application_signal();

   }


   bool application::init_instance()
   {


      if(!::core::application::init_instance())
         return false;




      KickDevEdgeFront(this);

      Session.filemanager()->m_strLevelUp = "levelup";
      //Session.filemanager()->m_strToolBar = "filemanager_toolbar.xml";

      return true;
   }



   void application::term_instance()
   {

      int32_t iExitCode = 0;

      try
      {

         ::core::application::term_instance();

      }
      catch(...)
      {

         m_error.m_iaErrorCode2.add(-1);

      }

   }


   void application::pre_translate_message(::message::message * pobj)
   {
      SCAST_PTR(::message::base, pbase, pobj);
      if(pbase->m_id == WM_KEYDOWN)
      {
         int32_t i = 1;
         i = i + 1;
      }
      else if(pbase->m_id == WM_KEYUP)
      {
         int32_t i = 1;
         i = i + 1;
      }
      ::core::application::pre_translate_message(pobj);
   }

   void application::route_command_message(::user::command * pcommand)

   {
      ::core::application::route_command_message(pcommand);
   }
   /*
   void application::OnFileManagerOpenFile(::filemanager::data * pdata, ::fs::item_array & itema)
      {
         UNREFERENCED_PARAMETER(pdata);
         string strExtension = System.file().extension(itema[0].m_strPath);
         if(strExtension.compare_ci("ca2solution") == 0)
         {
            m_ptemplate_solution->open_document_file(this, itema[0].m_strPath);
         }
         else
         {
            string strId = "netnodeds://" +itema[0].m_strPath;
            m_ppaneview->add_tab(strId, strId);
            m_ppaneview->set_cur_tab_by_id(strId);
         }
      }
   */


   void application::on_request(::create * pcreate)
   {

      sp(::user::document) pdoc = NULL;

      if(netnodeds().m_ptemplateEdge->get_document_count() == NULL)
      {

         netnodeds().m_ptemplateEdge->request_create(pcreate);

      }

      sp(main_document) pmaindoc = NULL;

      if (netnodeds().m_ptemplateEdge->get_document(0) != NULL)
      {

         pmaindoc = (netnodeds().m_ptemplateEdge->get_document(0));

      }

      if(pmaindoc != NULL)
      {

         string strExtension = pcreate->m_spCommandLine->m_varFile.get_file_path().ext();

         sp(::netnodeds::pane_view) pview = pmaindoc->get_typed_view < ::netnodeds::pane_view > ();
         if(pview != NULL)
         {
            if(strExtension.compare_ci("ca2solution") == 0)
            {
               pview->set_cur_tab_by_id(PaneViewDevEdge, pcreate);
               sp(::user::single_document_template) ptemplate = (netnodeds().m_ptemplateEdge);
               if(ptemplate != NULL)
               {
                  
                  if(ptemplate->get_document_count() == NULL)
                  {
                     
                     ptemplate->open_new_document(this);

                  }

               }

               pcreate->m_puiParent = pview->get_pane_by_id(PaneViewDevEdge)->m_pholder;

               netnodeds().m_ptemplate_solution->request_create(pcreate);

               pdoc = ::user::get_document(pcreate);

            }
            else
            {
               pdoc = pview->open_file(pcreate);
            }
         }
      }
   }

   /*   void application::_001OnFileNew()
      {
         netnodeds()m_ptemplateEdge->open_document_file(this, NULL, TRUE, System.m_puiInitialPlaceHolderContainer);
      }*/

   bool application::on_install()
   {

      System.os().file_association_set_shell_open_command("txt", "ca.netnodeds.txtfile", System.dir().ca2module() / "app.exe", NULL);

      /*if(VistaTools::IsVista() && VistaTools::IsElevated() == S_OK)
      {
         string strCommand = m_strModulePath;
         strCommand = System.url().url_encode(strCommand);
         uint32_t dwSessId;

         HANDLE hProcess = ::GetCurrentProcess();
         uint32_t dwId = ::GetProcessId(hProcess);

         ProcessIdToSessionId(dwId, &dwSessId);
         sp(::xml::node) pnode = new xml::node;
         pnode->m_strName = "run";
         pnode->add_attr("sessionid", dwSessId);
         pnode->add_attr("command", strCommand);
         machine_event_central().command(pnode);
      }*/

      return ::core::application::on_install();

   }


} // namespace netnodeds






extern "C"
::aura::library * design_netnodeds_get_new_library(::aura::application * papp)
{

   return new ::aura::single_application_library < ::netnodeds::application >(papp,"app-core");

}


