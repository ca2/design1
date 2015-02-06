#include "framework.h"


namespace syllomatter
{


   application::application()
   {

      m_ptemplateSyllomatter = NULL;

   }


   void application::construct()
   {

      m_strAppName         = "syllomatter";
      m_strBaseSupportId   = "ca2_syllomatter";
      m_bLicense           = false;

   }

   application::~application()
   {
   }


   bool application::initialize_instance()
   {
      System.factory().creatable_small < syllomatter::main_document >();
      System.factory().creatable_small < syllomatter::main_frame >();
      System.factory().creatable_small < syllomatter::pane_view >();
      System.factory().creatable_small < syllomatter::document >();
      System.factory().creatable_small < syllomatter::frame >();
      System.factory().creatable_small < syllomatter::view >();
      System.factory().creatable_small < syllomatter::filemanager_document >();
      System.factory().creatable_small < syllomatter::filemanager_frame >();
      System.factory().creatable_small < syllomatter::list_view >();
      System.factory().creatable_small < syllomatter::svn_view >();

      if(!tesseract::application::initialize_instance())
         return FALSE;

      InitializeFileManager("syllomatter/frame");
      Platform.filemanager().std().m_strLevelUp.Empty();
      //Platform.filemanager().std().m_strToolBar = "syllomatter_::filemanager::toolbar.xml";
      Platform.filemanager().std().m_dataidStatic = "FileManagerFavoritesList";
      //Platform.filemanager().std().m_uiDialogBar = 0;
      //Platform.filemanager().std().m_uiMenuBar = 0;
      Platform.filemanager().std().m_strFilePopup = "filemanager\\file_popup.xml";
      //Platform.filemanager().std().m_uiFilePopupSubstId = 0;
      Platform.filemanager().std().m_strFolderPopup = "filemanager\\folder_popup.xml";
      Platform.filemanager().std().m_strPopup = "filemanager\\popup.xml";
      //Platform.filemanager().std().m_uiExpandBox = 0;
      //Platform.filemanager().std().m_uiCollapseBox = 0;
   //   Platform.filemanager().std().m_pfilelistcallback = this;
     // Platform.filemanager().std().m_pfilelistcallback->set_app(this);


      ::user::single_document_template* pDocTemplate;
      pDocTemplate = new ::user::single_document_template(
         this,
         "filemanager/frame",
         System.type_info < main_document > (),
         System.type_info < main_frame > (),       // main SDI frame ::user::interaction_impl
         System.type_info < pane_view > ());
      add_document_template(pDocTemplate);
      m_ptemplateSyllomatter = pDocTemplate;


      connect_command("add_working_copy", &::syllomatter::application::_001OnAddWorkingCopy);

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

   void application::on_request(sp(::create) pcreatecontext)
   {

      m_ptemplateSyllomatter->open_document_file(pcreatecontext);

   }

   void application::InitializeFileManager(const char * pszMatter)
   {
      Platform.filemanager().m_ptemplateStd = new syllomatter::filemanager_template(&Platform.filemanager());
      Platform.userex()->shellimageset().initialize();
      Platform.filemanager().m_ptemplateStd->Initialize(0, pszMatter);

      Platform.filemanager().m_ptemplateForm = new ::user::multiple_document_template(
         this,
         "system/form",
         System.type_info < ::filemanager::form_document > (),
         System.type_info < ::filemanager::form_child_frame > (),
         System.type_info < ::filemanager::form_view > ());

      Platform.filemanager().m_ptemplateOperation = new ::user::single_document_template(
         this,
         "system/form",
         System.type_info < ::filemanager::operation_document > (),
         System.type_info < ::filemanager::operation_child_frame > (),
         System.type_info < ::filemanager::operation_view > ());
   }

   void application::create(const char * psz)
   {
      UNREFERENCED_PARAMETER(psz);
   }

   void application::commit(const char * pszDescriptor, const char * pszWorkingCopy)
   {
      UNREFERENCED_PARAMETER(pszDescriptor);
      UNREFERENCED_PARAMETER(pszWorkingCopy);
   }

   void application::checkout(const char * pszRepos, const char * pszWorkingCopy)
   {

      string strHead;

      {

         property_set set(get_app());

         strHead = Application.http().get("https://api.ca2.cc/syllomatter/head", set);

      }

      string strFileList;

      {

         property_set set(get_app());

         strFileList = Application.http().get("https://api.ca2.cc/syllomatter/checkout_list?revision=" + strHead + "repos=" + string(pszRepos), set);

      }

      stringa stra;
      stra.explode(strFileList, "\n");
      string strSrcBase = System.dir().appdata("syllomatter", pszWorkingCopy);
      string strDstBase = System.dir().element("syllomatter", pszWorkingCopy);
      string strFileSrc;
      string strFileDst;
      
      for(int32_t i = 0; i < stra.get_size(); i++)
      {
         strFileSrc = System.dir().path(strSrcBase, stra[i]);

         property_set set(get_app());

         System.http().download("https://api.ca2.cc/syllomatter/get?revision=" + strHead + "repos=" + string(pszRepos) + "&file=" + System.url().url_encode(stra[i]), strFileSrc, set);

         strFileDst = System.dir().path(strDstBase, stra[i]);

         Application.file().copy(strFileDst, strFileSrc);

      }

   }

   void application::update(const char * pszWorkingCopy)
   {
      UNREFERENCED_PARAMETER(pszWorkingCopy);
   }


   void application::OnFileManagerOpenContextMenuFolder(::filemanager::data * pdata, const ::fs::item & item, stringa & straCommand, stringa & straCommandTitle)
   {

      UNREFERENCED_PARAMETER(pdata);
      UNREFERENCED_PARAMETER(item);

      straCommand.add("add_working_copy");
      straCommandTitle.add("Add Working Copy");
   }


   void application::_001OnAddWorkingCopy(::signal_details * pobj)
   {

      UNREFERENCED_PARAMETER(pobj);
      
      simple_message_box(NULL, "GoingToAddWorkingCopy", 0);


   }


   

} // namespace syllomatter



#ifndef _WIN32
extern "C"
#endif
::aura::library * app_core_syllomatter_get_new_library(::aura::application * papp)
{

   return new ::aura::single_application_library < ::syllomatter::application >(papp, "app-core");

}





