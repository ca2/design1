#include "framework.h"


namespace tarsila
{


   application::application()
   {

      m_strAppName         = "tarsila";
      m_strInstallToken    = "tarsila";
      m_bLicense = false;

   }


   application::~application()
   {

   }

   bool application::initialize_instance()
   {


      m_pxmlschemaDrawing = canew(::xml::tree_schema);

      m_pxmlschemaDrawing->set_node_name(drawing_polygon, "polygon");


      System.factory().cloneable_small < document >();
      System.factory().cloneable_small < frame >();
      System.factory().creatable_small < view >();
      System.factory().creatable_small < polygon >();

      if(!::tesseract::application::initialize_instance())
         return false;

      SetRegistryKey("ca2core");

      ::user::single_document_template* pDocTemplate;
      pDocTemplate = new ::user::single_document_template(
         this,
         "system/form",
         System.type_info < document > (),
         System.type_info < frame > (),       // main SDI frame ::user::interaction_impl
         System.type_info < view > ());
      add_document_template(pDocTemplate);
      m_pdoctemplate = pDocTemplate;


      return TRUE;
   }

   int32_t application::exit_instance()
   {

      int32_t iExitCode = 0;

      try
      {

         iExitCode = ::tesseract::application::exit_instance();

      }
      catch(...)
      {

         iExitCode = -1;

      }

      return iExitCode;

   }

   void application::on_request(sp(::create) spcreatecontext)
   {
      
      m_pdoctemplate->open_document_file(spcreatecontext->m_spCommandLine->m_varFile);


   }


   bool application::on_install()
   {


      if(!tesseract::application::on_install())
         return false;

      System.os().file_association_set_shell_open_command("jpg", "ca.tarsila.jpegfile", System.dir().ca2module("app.exe"), NULL);

      return true;

   }

} // namespace tarsila



#ifdef CUBE

extern "C"
::aura::library * app_core_tarsila_get_new_library(::aura::application * papp)
{

   return new ::aura::single_application_library < ::tarsila::application >(papp, "app-core");

}


#else



extern "C"
::aura::library * get_new_library(::aura::application * papp)
{

   return new ::aura::single_application_library < ::tarsila::application >(papp, "app-core");

}


#endif