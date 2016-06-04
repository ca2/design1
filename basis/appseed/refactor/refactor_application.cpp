#include "framework.h"


namespace refactor
{


   application::application()
   {

      m_strAppName            = "refactor";
      m_strBaseSupportId      = "votagus_ca2_flag";
      m_bLicense              = false;

   }


   application::~application()
   {
   }


   bool application::initialize_instance()
   {

      System.factory().creatable_small < ::refactor::pane_view >();
      System.factory().creatable_small < ::refactor::document >();
      System.factory().creatable_small < ::refactor::frame >();
      System.factory().creatable_small < ::refactor::view >();

      if(!core::application::initialize_instance())
         return false;

	   ::user::single_document_template* pDocTemplate;
	   pDocTemplate = new ::user::single_document_template(
         this,
		   "html/frame",
		   System.template type_info < ::refactor::document > (),
		   System.template type_info < ::refactor::frame > (),       // main SDI frame ::ca::window
		   System.template type_info < ::refactor::pane_view > ());
      add_document_template(pDocTemplate);
      m_ptemplateRefactorMain = pDocTemplate;
	   pDocTemplate = new ::user::single_document_template(
         this,
		   "html/frame",
         System.template type_info < ::refactor::document > (),
		   System.template type_info < ::refactor::frame > (),       // main SDI frame ::ca::window
		   System.template type_info < ::refactor::view > ());
      add_document_template(pDocTemplate);
      m_ptemplateRefactor = pDocTemplate;

      return true;
   }

   int application::exit_instance()
   {
      
      return ::core::application::exit_instance();
   }

   void application::on_request(sp(::create) pcreatecontext)
   {

      if(!pcreatecontext->m_spCommandLine->m_varQuery.has_property("client_only"))
      {
         m_ptemplateRefactorMain->open_document_file(pcreatecontext);
      }

      if(!pcreatecontext->m_spCommandLine->m_varFile.is_empty())
      {
         m_ptemplateRefactor->open_document_file(pcreatecontext);
      }

   }

} // namespace refactor





extern "C"
::aura::library * design_refactor_get_new_library(::aura::application * papp)
{

   return new ::aura::single_application_library < ::refactor::application >(papp,"app-core");

}


