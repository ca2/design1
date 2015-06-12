#include "framework.h"


namespace biteditor
{


   pane_view::pane_view(::aura::application * papp) :
      ::object(papp),
      ::user::tab(papp),
      
      ::user::tab_view(papp),
      ::userex::pane_tab_view(papp),
      place_holder_container(papp)
   {

      

      m_pviewdata              = NULL;
      m_pviewdataOld              = NULL;

      /*   ::user::single_document_template* pdoctemplate;
      pdoctemplate = new ::user::single_document_template(
      IDR_ALBUM,
      System.type_info < MediaLibraryDoc > (),
      System.type_info < MediaLibraryChildFrame > (),
      System.type_info < ::mplite::library::view > ());
      m_pdoctemplateAlbum = pdoctemplate;

      pdoctemplate = new ::user::single_document_template(
      IDR_ALBUM,
      System.type_info < OptionsDoc > (),
      System.type_info < OptionsChildFrame > (),
      System.type_info < OptionsView > ());


      m_pdoctemplateOptions = pdoctemplate;

      pdoctemplate = new ::user::single_document_template(
      IDR_ALBUM,
      System.type_info < GoodMixerDoc > (),
      System.type_info < simple_child_frame > (),
      System.type_info < MixerMainView > ());

      m_pdoctemplateAudioControl = pdoctemplate;*/


   }

   pane_view::~pane_view()
   {
   }

   void pane_view::install_message_handling(::message::dispatch * pinterface)
   {
      ::userex::pane_tab_view::install_message_handling(pinterface);
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &pane_view::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_USER + 1122  , pinterface, this, &pane_view::_001OnMenuMessage);
   }



#ifdef DEBUG
   void pane_view::assert_valid() const
   {
      ::user::impact::assert_valid();
   }

   void pane_view::dump(dump_context & dumpcontext) const
   {
      ::user::impact::dump(dumpcontext);
   }
#endif //DEBUG


   void pane_view::_001OnCreate(::signal_details * pobj) 
   {
      
      if(pobj->previous())
         return;

      add_tab("bit editor", pane_view_bit_editor);

      add_tab("file manager", "file_manager");

      set_cur_tab_by_id(pane_view_bit_editor);

   }



   void pane_view::on_create_view(::user::view_creator_data * pcreatordata)
   {

      switch(pcreatordata->m_id)
      {
      case pane_view_context_menu:
         {
            sp(::create) cc(allocer());
            cc->m_spCommandLine->m_varFile = "http://localhost:10011/";
            cc->m_puiParent = pcreatordata->m_pholder;

            sp(front_document) pdoc =  (Application.::biteditor::application::m_ptemplateFront->open_document_file(cc));

            if(pdoc != NULL)
            {
               sp(::user::impact) pview = pdoc->get_view();
               if(pview != NULL)
               {
                  sp(::user::frame_window) pframe =  (pview->GetParentFrame());
                  if(pframe != NULL)
                  {
                     pcreatordata->m_pdoc = pdoc;
                  }
               }
            }
         }
         break;
      case pane_view_bit_editor:
         {
            sp(::create) cc(allocer());
            cc->m_puiParent = pcreatordata->m_pholder;
            sp(::user::document) pdoc =  (Application.m_ptemplate_devedge->open_document_file(cc));
            if(pdoc != NULL)
            {
               sp(::user::impact) pview = pdoc->get_view();
               if(pview != NULL)
               {
                  sp(::user::frame_window) pframe =  (pview->GetParentFrame());
                  if(pframe != NULL)
                  {
                     pcreatordata->m_pdoc = pdoc;
                     pcreatordata->m_eflag.signalize(::user::view_creator_data::flag_hide_all_others_on_show);
                  }
               }
            }
         }
         break;
      default:
         break;
      }

      ::userex::pane_tab_view::on_create_view(pcreatordata);

   }


} // namespace biteditor


