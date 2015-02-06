#include "framework.h"


namespace syllomatter
{


   filemanager_template::filemanager_template(::filemanager::filemanager * pfilemanager) :
      element(pfilemanager->get_app()),
      ::filemanager::manager_template(pfilemanager->get_app())
   {
   }

   filemanager_template::~filemanager_template()
   {
   }


   void filemanager_template::Initialize(int32_t iTemplate, const char * pszMatter)
   {

      ::filemanager::manager_template::Initialize(iTemplate, pszMatter);
      return;

      m_iTemplate       = iTemplate;
      m_pdoctemplateMain = new ::user::multiple_document_template(
         get_app(),
         pszMatter,
         System.type_info < filemanager_document > (),
         System.type_info < filemanager_frame > (),       // main SDI frame ::user::interaction_impl
         System.type_info < ::filemanager::tab_view > ());

      m_pdoctemplate = new ::user::multiple_document_template(
         get_app(),
         pszMatter,
         System.type_info < filemanager_document > (),
         System.type_info < filemanager_frame > (),
         System.type_info < ::filemanager::view > ());

      m_pdoctemplateChild = new ::user::multiple_document_template(
         get_app(),
         pszMatter,
         System.type_info < filemanager_document > (),
         System.type_info < filemanager_frame > (),
         System.type_info < ::filemanager::view > ());

      m_pdoctemplateChildList = new ::user::multiple_document_template(
         get_app(),
         pszMatter,
         System.type_info < filemanager_document > (),
         System.type_info < filemanager_frame > (),
         System.type_info < filemanager::file_list > ());
   }


} //  namespace syllomatter


