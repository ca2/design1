#include "framework.h"


namespace devedge 
{


   application::application()
   {
      m_strAppName         = "devedge";
      m_bLicense = false;
      m_ppaneview          = NULL;

      m_pdevedge = new ::devedge::devedge(this);

      m_pdevedge->construct(this);

      m_pdevedge->connect_to_application_signal();

   }


   application::~application()
   {

      m_pdevedge = NULL;

   }


   //void application::construct()
   //{

   //   m_strBaseSupportId   = "ca2_devedge";
   //   m_strInstallToken    = "devedge";

   //}


   bool application::initialize_instance()
   {
      

      if(!::core::application::initialize_instance())
         return false;

      m_dataid += ".local://";


      KickDevEdgeFront(this);

      Session.filemanager().std().m_strLevelUp = "levelup";
      Session.filemanager().std().m_strToolBar = "filemanager_toolbar.xml";

      return true;
   }



   int32_t application::exit_instance()
   {

      int32_t iExitCode = 0;

      try
      {

         iExitCode = ::core::application::exit_instance();

      }
      catch(...)
      {

         iExitCode = -1;

      }
      
      return iExitCode;

   }




   void application::pre_translate_message(::signal_details * pobj)
   {
      SCAST_PTR(::message::base, pbase, pobj);
      if(pbase->m_uiMessage == WM_KEYDOWN)
      {
         int32_t i = 1;
         i = i + 1;
      }
      else if(pbase->m_uiMessage == WM_KEYUP)
      {
         int32_t i = 1;
         i = i + 1;
      }
      ::core::application::pre_translate_message(pobj);
   }

   bool application::_001OnCmdMsg(::aura::cmd_msg * pcmdmsg)

   {
      return ::core::application::_001OnCmdMsg(pcmdmsg);
   }
/*
void application::OnFileManagerOpenFile(::filemanager::data * pdata, ::fs::item_array & itema)
   {
      UNREFERENCED_PARAMETER(pdata);
      string strExtension = System.file().extension(itema[0].m_strPath);
      if(strExtension.CompareNoCase("ca2solution") == 0)
      {
         m_ptemplate_solution->open_document_file(itema[0].m_strPath);
      }
      else
      {
         string strId = "devedge://" +itema[0].m_strPath;
         m_ppaneview->add_tab(strId, strId);
         m_ppaneview->set_cur_tab_by_id(strId);
      }
   }
*/
   void application::on_request(sp(::create) pcreatecontext)
   {
      sp(::user::document) pdoc = NULL;
      if(devedge().m_ptemplateEdge->get_document_count() == NULL)
      {
         devedge().m_ptemplateEdge->open_document_file(pcreatecontext);
      }
     sp(main_document) pmaindoc = NULL;
      if(devedge().m_ptemplateEdge->get_document(0) != NULL)
         pmaindoc =  (devedge().m_ptemplateEdge->get_document(0));
      if(pmaindoc != NULL)
      {
         string strExtension = pcreatecontext->m_spCommandLine->m_varFile.get_file_path().ext();
         sp(::devedge::pane_view) pview = pmaindoc->get_typed_view < ::devedge::pane_view > ();
         if(pview != NULL)
         {
            if(strExtension.CompareNoCase("ca2solution") == 0)
            {
               pview->set_cur_tab_by_id(PaneViewDevEdge, pcreatecontext);
               sp(::user::single_document_template) ptemplate = (devedge().m_ptemplateEdge);
               if(ptemplate != NULL)
               {
                  if(ptemplate->get_document_count() == NULL)
                  {
                     ptemplate->open_new_document();
                  }
               }
               pcreatecontext->m_puiParent = pview->get_pane_by_id(PaneViewDevEdge)->m_pholder;
               pdoc = devedge().m_ptemplate_solution->open_document_file(pcreatecontext);
            }
            else
            {
               pdoc = pview->open_file(pcreatecontext);
            }
         }
      }
   }

/*   void application::_001OnFileNew()
   {
      devedge()m_ptemplateEdge->open_document_file(NULL, TRUE, System.m_puiInitialPlaceHolderContainer);
   }*/

   bool application::on_install()
   {

      System.os().file_association_set_shell_open_command("txt","ca.devedge.txtfile",System.dir().ca2module() / "app.exe",NULL);

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


} // namespace devedge






extern "C"
::aura::library * design_devedge_get_new_library(::aura::application * papp)
{

   return new ::aura::single_application_library < ::devedge::application >(papp,"design");

}


