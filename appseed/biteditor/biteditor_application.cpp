#include "framework.h"



namespace biteditor
{


   application::application()
   {
   }

   void application::construct()
   {
      m_bLicense           = false;
      m_strAppName         = "biteditor";
      m_strBaseSupportId   = "ca2_biteditor";
      m_strInstallToken    = "biteditor";
   }

   application::~application()
   {
   }

   bool application::initialize_application()
   {
      System.factory().creatable_small < main_document > ();
      System.factory().creatable_small < frame > ();
      System.factory().creatable_small < biteditor::pane_view > ();


      System.factory().creatable_small < biteditor::document > ();
      System.factory().creatable_small < biteditor::child_frame > ();
      System.factory().creatable_small < biteditor::view > ();

      System.factory().creatable_small < biteditor::front_document > ();
      System.factory().creatable_small < biteditor::front_child_frame > ();
      System.factory().creatable_small < biteditor::front_view > ();

      if(!::tesseract::application::initialize_application())
         return false;


#ifdef WINDOWS

      ::CoInitialize(NULL);

#endif

      m_ptemplateEdge = new ::user::single_document_template(
         this,
         "biteditor/frame",
         System.type_info < main_document > (),
         System.type_info < frame > (),
         System.type_info < biteditor::pane_view > ());

      m_ptemplate_devedge = new ::user::single_document_template(
         this,
         "biteditor/frame",
         System.type_info < document > (),
         System.type_info < child_frame > (),
         System.type_info < view > ());


      m_ptemplateFront = new ::user::single_document_template(
         this,
         "biteditor/frame",
         System.type_info < front_document > (),
         System.type_info < front_child_frame > (),
         System.type_info < front_view > ());

      Session.filemanager()->m_strLevelUp = "levelup";


      return true;
   }


   void application::on_request(::create * pcreate)
   {

      if(m_ptemplateEdge->get_document() == NULL)
      {

         m_ptemplateEdge->request_create(pcreate);

      }

      m_ptemplate_devedge->request_create(pcreate);

   }



} // namespace biteditor







extern "C"
::aura::library * design_biteditor_get_new_library(::aura::application * papp)
{

   return new ::aura::single_application_library < biteditor::application > (papp, "app-core");

}




