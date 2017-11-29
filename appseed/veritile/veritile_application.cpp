#include "framework.h"


namespace veritile
{


   application::application()
   {

      m_strAppName         = "veritile";
      //m_strInstallToken    = "veritile";
      m_bLicense = false;

   }


   application::~application()
   {

   }

   bool application::init_instance()
   {


      m_pxmlschemaDrawing = canew(::xml::tree_schema);

      m_pxmlschemaDrawing->set_node_name(drawing_polygon, "polygon");


      System.factory().cloneable_small < document >();
      System.factory().cloneable_small < frame >();
      System.factory().creatable_small < view >();
      System.factory().creatable_small < tileset_view >();
      System.factory().creatable_small < polygon >();

      System.factory().cloneable_small < main_document >();
      System.factory().cloneable_small < main_frame >();
      System.factory().creatable_small < pane_view >();
      System.factory().creatable_small < tileset_pane_view >();
      System.factory().creatable_small < property_sheet >();




      if(!::tesseract::application::init_instance())
         return false;

      set_local_data_key_modifier();

      SetRegistryKey("ca2core");

      ::user::multiple_document_template* pDocTemplate;
      pDocTemplate = new ::user::multiple_document_template(
         this,
         "system/form",
         System.type_info < document > (),
         System.type_info < frame > (),       // main SDI frame ::user::interaction_impl
         System.type_info < ::user::split_view > ());
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

   void application::on_request(::create * pcreate)
   {

      if(m_pdoctemplateMain->get_document_count() <= 0)
      {

         m_pdoctemplateMain->open_document_file(NULL, true);

      }

      if(spcreate->m_spCommandLine->m_ecommand == ::command_line::command_application_start)
      {

         stringa stra;
         m_ppaneview->get_begins_ci_eat_id(stra,"veritile://");
         if( stra.get_count() <= 0)
         {

            string strPath;
            string strFormatTime;
            strFormatTime = System.datetime().international().get_gmt_date_time();
            strFormatTime.replace(":","-");
            strPath = Session.filemanager_get_initial_browse_path()/strFormatTime + ".veritile";
            if(!Application.file().exists(strPath))
            {
               Application.file().put_contents(strPath,"");
            }
            string strId = "veritile://" + strPath;
            m_ppaneview->set_cur_tab_by_id(strId);

         }

      }
      else if(spcreate->m_spCommandLine->m_ecommand == ::command_line::command_file_new)
      {

         string strPath;
         string strFormatTime;
         strFormatTime = System.datetime().international().get_gmt_date_time();
         strFormatTime.replace(":","-");
         strPath = Session.filemanager_get_initial_browse_path()/ strFormatTime + ".veritile";
         if(!Application.file().exists(strPath))
         {
            Application.file().put_contents(strPath,"");
         }
         string strId = "veritile://" + strPath;
         m_ppaneview->set_cur_tab_by_id(strId);

      }
      else if(spcreate->m_spCommandLine->m_ecommand == ::command_line::command_file_open)
      {

         if(spcreate->m_spCommandLine->m_varFile.get_string().ends_ci(".png"))
         {
            
            if(m_ppaneview->m_pdocCur != NULL            && m_ppaneview->m_pviewCur != NULL)
            {

               m_ppaneview->m_pdocCur->add_tileset(spcreate->m_spCommandLine->m_varFile);

            }
            else
            {
               
               Application.simple_message_box(NULL, "You should create a tile first", MB_OK);

            }
         }
         else
         {
          
            m_ppaneview->set_cur_tab_by_id("veritile://" + spcreate->m_spCommandLine->m_varFile.get_string());

         }

      }


   }


   bool application::on_install()
   {


      if(!tesseract::application::on_install())
         return false;

      System.os().file_association_set_shell_open_command("jpg", "ca.veritile.jpegfile", System.dir().ca2module()/ "app.exe", NULL);

      return true;

   }


   void application::ensure_tileset_dock(id idVeritile)
   {
      
      m_ppaneview->create_tab_by_id(idVeritile);

      m_ppaneview->set_cur_tab_by_id(idVeritile);

      ::user::tab_pane * ppane = m_ppaneview->get_pane_by_id(idVeritile);

      if(ppane == NULL)
         throw new simple_exception(get_app(),"could not ensure tileset dock (1)");

      sp(::user::place_holder) pholder =  ppane->m_pholder;

      if(pholder.is_null())
         throw new simple_exception(get_app(),"could not ensure tileset dock (2)");

      sp(::user::split_view) pview = pholder->first_child()->get_child_by_id("pane_first");

      if(pview.is_null())
         throw new simple_exception(get_app(),"could not ensure tileset dock (3)");

      if(pview->GetParentFrame()->get_child_by_id(idVeritile + ".tilesetdock") != NULL)
         return;

      m_ppaneview->create_view < ::user::split_view > (
         pview->get_document(),
         ::null_rect(),pview->get_pane_holder(1),string(idVeritile) + ".tilesetdock");

   }


   void application::on_create_split_view(::user::split_view * psplit)
   {

      if(psplit->get_document()->get_document_template() == m_pdoctemplate && psplit->m_id == "pane_first")
      {

         if(psplit->get_pane_count() > 0)
            return;

         psplit->SetPaneCount(2);

         psplit->SetSplitOrientation(orientation_vertical);

         psplit->set_position_rate(0,0.77);

         psplit->initialize_split_layout();

         psplit->create_view < view >(psplit->get_document(),::null_rect(),psplit->get_pane_holder(0),"tile_view");

         psplit->create_view < property_sheet >(psplit->get_document(),::null_rect(),psplit->get_pane_holder(1),"tileset_view");


      }
      else if(string(psplit->m_id).ends_ci(".tilesetdock"))
      {


         if(psplit->get_pane_count() > 0)
            return;

         psplit->SetPaneCount(2);

         psplit->SetSplitOrientation(orientation_horizontal);

         psplit->set_position_rate(0,0.5);

         psplit->initialize_split_layout();

         psplit->SetPane(0,psplit->get_document()->get_typed_view < property_sheet >(), false, "tile_view");

         psplit->create_view < tileset_pane_view > (psplit->get_document(),::null_rect(),psplit->get_pane_holder(1),"tileset_pane_view");

      }

   }




} // namespace veritile



extern "C"
::aura::library * design_veritile_get_new_library(::aura::application * papp)
{

   return new ::aura::single_application_library < ::veritile::application >(papp, "design");

}



