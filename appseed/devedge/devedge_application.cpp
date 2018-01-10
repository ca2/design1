﻿#include "framework.h"


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


   bool application::init_instance()
   {


      if(!::core::application::init_instance())
         return false;

      set_local_data_key_modifier();


      KickDevEdgeFront(this);

      Session.filemanager()->m_strLevelUp = "levelup";
//      Session.filemanager()->m_strToolBar = "filemanager_toolbar.xml";

      return true;
   }


   void application::term_instance()
   {

      try
      {

         ::core::application::term_instance();

      }
      catch(...)
      {

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


   void application::_001OnCmdMsg(::user::command * pcommand)
   {

      ::core::application::_001OnCmdMsg(pcommand);

   }


   /*
   void application::OnFileManagerOpenFile(::filemanager::data * pdata, ::fs::item_array & itema)
      {
         UNREFERENCED_PARAMETER(pdata);
         string strExtension = System.file().extension(itema[0].m_strPath);
         if(strExtension.compare_ci("ca2solution") == 0)
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


   void application::on_request(::create * pcreate)
   {

      sp(::user::document) pdoc = NULL;

      if(devedge().m_ptemplateEdge->get_document_count() == NULL)
      {

         devedge().m_ptemplateEdge->request_create(pcreate);

      }

      sp(main_document) pmaindoc = NULL;

      if (devedge().m_ptemplateEdge->get_document(0) != NULL)
      {


         pmaindoc = (devedge().m_ptemplateEdge->get_document(0));

      }


      if(pmaindoc != NULL)
      {
         string strExtension = pcreate->m_spCommandLine->m_varFile.get_file_path().ext();
         sp(::devedge::pane_view) pview = pmaindoc->get_typed_view < ::devedge::pane_view > ();
         if(pview != NULL)
         {
            if(strExtension.compare_ci("ca2solution") == 0)
            {
               pview->set_cur_tab_by_id(PaneViewDevEdge, pcreate);
               sp(::user::single_document_template) ptemplate = (devedge().m_ptemplateEdge);
               if(ptemplate != NULL)
               {
                  if(ptemplate->get_document_count() == NULL)
                  {
                     ptemplate->open_new_document();
                  }
               }

               pcreate->m_puiParent = pview->get_pane_by_id(PaneViewDevEdge)->m_pholder;

               devedge().m_ptemplate_solution->request_create(pcreate);

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


