#include "framework.h"


namespace tarsila
{


   application::application()
   {

      m_strAppName         = "tarsila";
      //m_strInstallToken    = "tarsila";
      m_bLicense = false;

   }


   application::~application()
   {

   }

   bool application::initialize_application()
   {


      m_pxmlschemaDrawing = canew(::xml::tree_schema);

      m_pxmlschemaDrawing->set_node_name(drawing_polygon, "polygon");


      System.factory().cloneable_small < document >();
      System.factory().cloneable_small < frame >();
      System.factory().creatable_small < view >();
      System.factory().creatable_small < polygon >();

      System.factory().cloneable_small < main_document >();
      System.factory().cloneable_small < main_frame >();
      System.factory().creatable_small < pane_view >();




      if(!::tesseract::application::initialize_application())
         return false;

      m_dataid += ".local://";

      SetRegistryKey("ca2core");

      ::user::multiple_document_template* pDocTemplate;
      pDocTemplate = new ::user::multiple_document_template(
         this,
         "system/form",
         System.type_info < document > (),
         System.type_info < frame > (),       // main SDI frame ::user::interaction_impl
         System.type_info < view > ());
      add_document_template(pDocTemplate);
      m_pdoctemplate = pDocTemplate;

      ::user::single_document_template* pDocTemplateMain;
      pDocTemplateMain = new ::user::single_document_template(
         this,
         "system/form",
         System.type_info < main_document >(),
         System.type_info < main_frame >(),       // main SDI frame ::user::interaction_impl
         System.type_info < pane_view >());
      add_document_template(pDocTemplateMain);
      m_pdoctemplateMain = pDocTemplateMain;

      return TRUE;
   }

   int32_t application::exit_application()
   {

      int32_t iExitCode = 0;

      try
      {

         iExitCode = ::tesseract::application::exit_application();

      }
      catch(...)
      {

         iExitCode = -1;

      }

      return iExitCode;

   }

   void application::on_request(::create * pcreatecontext)
   {

      if(m_pdoctemplateMain->get_document_count() <= 0)
      {

         m_pdoctemplateMain->open_document_file(NULL, true);

      }

      if(spcreatecontext->m_spCommandLine->m_ecommand == ::command_line::command_application_start)
      {

         stringa stra;
         m_ppaneview->get_begins_ci_eat_id(stra,"tarsila://");
         if( stra.get_count() <= 0)
         {

            string strPath;
            string strFormatTime;
            strFormatTime = System.datetime().international().get_gmt_date_time();
            strFormatTime.replace(":","-");
            strPath = Session.filemanager_get_initial_browse_path()/strFormatTime + ".tarsila";
            if(!Application.file().exists(strPath))
            {
               Application.file().put_contents(strPath,"");
            }
            string strId = "tarsila://" + strPath;
            m_ppaneview->set_cur_tab_by_id(strId);

         }

      }
      else if(spcreatecontext->m_spCommandLine->m_ecommand == ::command_line::command_file_new)
      {

         string strPath;
         string strFormatTime;
         strFormatTime = System.datetime().international().get_gmt_date_time();
         strFormatTime.replace(":","-");
         strPath = Session.filemanager_get_initial_browse_path()/ strFormatTime + ".tarsila";
         if(!Application.file().exists(strPath))
         {
            Application.file().put_contents(strPath,"");
         }
         string strId = "tarsila://" + strPath;
         m_ppaneview->set_cur_tab_by_id(strId);

      }
      else if (spcreatecontext->m_spCommandLine->m_ecommand == ::command_line::command_file_open)
      {

         m_ppaneview->set_cur_tab_by_id("tarsila://" + spcreatecontext->m_spCommandLine->m_varFile.get_string());

      }

   }


   bool application::on_install()
   {


      if(!tesseract::application::on_install())
         return false;

      System.os().file_association_set_shell_open_command("jpg", "ca.tarsila.jpegfile", System.dir().ca2module()/ "app.exe", NULL);

      return true;

   }

} // namespace tarsila



extern "C"
::aura::library * design_tarsila_get_new_library(::aura::application * papp)
{

   return new ::aura::single_application_library < ::tarsila::application >(papp, "design");

}



