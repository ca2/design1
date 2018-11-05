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


   bool application::init_instance()
   {

      System.factory().creatable_small < ::refactor::pane_view >();
      System.factory().creatable_small < ::refactor::document >();
      System.factory().creatable_small < ::refactor::frame >();
      System.factory().creatable_small < ::refactor::view >();

      if(!core::application::init_instance())
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

   void application::term_instance()
   {
      
      ::core::application::term_instance();

   }

   
   void application::on_request(::create * pcreate)
   {

      if(!pcreate->m_spCommandLine->m_varQuery.has_property("client_only"))
      {

         m_ptemplateRefactorMain->request_create(pcreate);

      }

      if(!pcreate->m_spCommandLine->m_varFile.is_empty())
      {
         
         m_ptemplateRefactor->request_create(pcreate);

      }

   }


} // namespace refactor





extern "C"
::aura::library * design_refactor_get_new_library(::aura::application * papp)
{

   return new ::aura::single_application_library < ::refactor::application >(papp,"app-core");

}


