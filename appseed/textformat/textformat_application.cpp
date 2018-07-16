#include "framework.h"


namespace textformat
{


   application::application()
   {

      m_ptemplateTextFormatMain = NULL;
      m_ptemplateTextFormatView = NULL;

      m_strAppId = "design/textformat";
      m_strAppName = "design/textformat";
      m_strBaseSupportId = "ca2_flag";
      m_bLicense = false;

      m_strTextFormatDefault = "Text Format!!";
      m_strAlternateTextFormatDefault = "Hello!!";

      m_strTextFormat = m_strTextFormatDefault;
      m_strAlternateTextFormat = m_strAlternateTextFormatDefault;

   }


   application::~application()
   {
   }


   bool application::init_instance()
   {

      set_local_data_key_modifier();

      ::core::session * pcoression = m_pauraapp->m_pcoresession;

      pcoression->will_use_view_hint(::userex::view_font_sel);

      System.factory().creatable_small < ::textformat::document >();
      System.factory().creatable_small < ::textformat::frame >();
      System.factory().creatable_small < ::textformat::main_frame >();
      System.factory().creatable_small < ::textformat::view >();
      System.factory().creatable_small < ::textformat::pane_view >();
      System.factory().creatable_small < ::composite::view >();
      System.factory().creatable_small < ::composite::pic >();
      System.factory().creatable_small < ::user::pic >();
      System.factory().creatable_small < ::user::rich_text::edit >();
      System.factory().creatable_small < ::composite::pic_tool >();

      System.factory().creatable_small < ::user::rich_text::format >();
      System.factory().creatable_small < ::user::rich_text::box >();


      System.factory().creatable_small < ::userex::group_image_list_view >();
      System.factory().creatable_small < ::userex::image_list_view >();
      System.factory().creatable_small < ::user::image_list_view >();


      if (!::core::application::init_instance())
      {

         return false;

      }

      string str = handler()->m_varTopicQuery["textformat"];

      if (str.has_char())
      {

         m_strTextFormat = str;

      }


      ::user::single_document_template* pDocTemplate;


      pDocTemplate = canew(::user::single_document_template(
                           this,
                           "main",
                           System.type_info < document >(),
                           System.type_info < main_frame >(),
                           System.type_info < pane_view >()));
      m_ptemplateTextFormatMain = pDocTemplate;
      add_document_template(pDocTemplate);


      pDocTemplate = canew(::user::single_document_template(
                           this,
                           "main",
                           System.type_info < document >(),
                           System.type_info < frame >(),
                           System.type_info < ::composite::view >()));
      m_ptemplateTextFormatView = pDocTemplate;
      add_document_template(pDocTemplate);


      add_document_template(pDocTemplate);


      return true;

   }


   void application::term_application()
   {

      ::core::application::term_application();

   }


   void application::on_request(::create * pcreate)
   {

#if 0

#ifdef DEBUG

      output_debug_string("DEBUG build? (basis)");

      ASSERT(FALSE);

#else

      output_debug_string("RELEASE build? (stage)");

      ASSERT(FALSE);

#endif

#endif

      if (m_ptemplateTextFormatMain->get_document_count() == 0)
      {

         m_ptemplateTextFormatMain->request_create(pcreate);

      }

      if (pcreate->m_spCommandLine->m_varFile.has_char())
      {

         m_ptemplateTextFormatView->request_create(pcreate);

      }

      if (handler()->m_varTopicQuery["wfi_maximize"].is_set())
      {

         pcreate->m_spCommandLine->m_varQuery["document"].cast < document >()->get_typed_view < ::userex::pane_tab_view >()->GetTopLevelFrame()->_001WindowMaximize();

      }

      output_debug_string("\nfinished textformat::on_request");

   }


   string application::preferred_userschema()
   {

      return "core";

   }


   int64_t application::add_ref()
   {

      return ::object::add_ref();

   }

   int64_t application::dec_ref()
   {

      return ::object::dec_ref();

   }


} // namespace textformat




extern "C"
::aura::library * design_textformat_get_new_library(::aura::application * papp)
{

   return new ::aura::single_application_library < ::textformat::application >(papp, "design/textformat");

}


aura_app design_core_textformat("design/textformat", &design_textformat_get_new_library);


