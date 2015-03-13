#include "framework.h"


namespace tarsila
{


   pane_view::pane_view(::aura::application * papp) :
      ::object(papp),
      ::user::tab(papp),
      
      ::user::tab_view(papp),
      ::userex::pane_tab_view(papp),
      place_holder_container(papp)
   {


      m_dataid = ".local://";

      get_data()->m_bVertical = true;

      get_data()->m_matchanyRestore.add(new ::core::match::prefix("tarsila://"));

      

   }

   pane_view::~pane_view()
   {
   }



   #ifdef DEBUG
   void pane_view::assert_valid() const
   {
      ::aura::impact::assert_valid();
   }

   void pane_view::dump(dump_context & dumpcontext) const
   {
      ::aura::impact::dump(dumpcontext);
   }
   #endif //DEBUG


   void pane_view::_001OnCreate(::signal_details * pobj) 
   {
//      SCAST_PTR(::message::create, pcreate, pobj)
      if(pobj->previous())
         return;

      set_tab("menu", tarsila::pane_view_context_menu);
      //set_tab("Plain Text Media", tarsila::PaneViewEdit);
      set_tab("File Manager", "file_manager");
      //set_tab("Printer", "printer", false);


      sp(::tarsila::application) papp = get_app();
      papp->m_ppaneview = this;
   }


   void pane_view::on_update(::aura::impact * pSender, LPARAM lHint, ::object* pHint) 
   {
      UNREFERENCED_PARAMETER(pSender);
      UNREFERENCED_PARAMETER(lHint);
      UNREFERENCED_PARAMETER(pHint);

   }

   void pane_view::on_show_view()
   {
      ::userex::pane_tab_view::on_show_view();
      if(::str::begins_ci(m_pviewdata->m_id, "tarsila://"))
      {
         GetParentFrame()->LoadToolBar(0, "edit_toolbar.xml");
//         show_tab_by_id("printer");
      }
      else if(m_pviewdata->m_id == "printer")
      {
         ::simple_printer_list_view * pview = get_document()->get_typed_view < ::simple_printer_list_view >();
         pview->m_pview = m_pviewdataOld->m_pdoc->get_view();
      }
      else
      {
         show_tab_by_id("printer", false);
      }
   }


   bool pane_view::pre_create_window(::user::create_struct& cs) 
   {
      cs.dwExStyle &= ~WS_EX_CLIENTEDGE;   

      return ::aura::impact::pre_create_window(cs);
   }


   void pane_view::on_create_view(::user::view_creator_data * pcreatordata)
   {

      

      ::file::path strPath(pcreatordata->m_id.str());

      if(::str::begins_eat_ci(strPath, "tarsila://"))
      {

         sp(::aura::document) pdoc = NULL;

         try
         {
            pdoc =  (Application.m_pdoctemplate->open_document_file(strPath, true, pcreatordata->m_pholder));
         }
         catch(::file::exception & e)
         {

            if(e.m_cause == ::file::exception::badPath)
            {

               throw ::user::view_creator::create_exception(pcreatordata->m_id);

            }

         }

         if(pdoc != NULL)
         {

            sp(::aura::impact) pview = pdoc->get_view();

            if(pview != NULL)
            {

               sp(::user::frame_window) pframe =  (pview->GetParentFrame());

               if(pframe != NULL)
               {

                  pcreatordata->m_pdoc = pdoc;

                  pcreatordata->m_strTitle = strPath.name();

               }

            }

         }

         return;
      }

      if(pcreatordata->m_id == "printer")
      {
         {

            sp(::aura::impact) pview = ::aura::impact::create_view < ::simple_printer_list_view > (pcreatordata);
            if(pview != NULL)
            {
//               sp(::user::menu_list_view) pmenuview = (sp(::user::menu_list_view)) pview;
               pcreatordata->m_pdoc = get_document();
               pcreatordata->m_pwnd = pview;
            }
         }
         return;
      }
      //switch(pcreatordata->m_id)
      //{
      ////case tarsila::PaneViewContextMenu:
      ////   /*{
      ////      sp(front_document) pdoc = (devedgeFrontDoc *) (dynamic_cast < verieditsp(::core::application) > (((sp(::user::frame_window)) GetParentFrame())->m_pauraapp->m_pcoreapp))->m_ptemplateFront->open_document_file("http://localhost:10011/");
      ////      if(pdoc != NULL)
      ////      {
      ////         POSITION pos = pdoc->get_view_count();
      ////         sp(::aura::impact) pview = pdoc->get_view(pos);
      ////         if(pview != NULL)
      ////         {
      ////            sp(::user::frame_window) pframe = (sp(::user::frame_window)) pview->GetParentFrame();
      ////            if(pframe != NULL)
      ////            {
      ////               pcreatordata->m_pdoc = pdoc;
      ////               pcreatordata->m_pwnd = pframe;


      ////            }
      ////         }
      ////      }
      ////   }*/
      ////      break;
      ////case tarsila::PaneViewEdit:
      ////   {
      ////      sp(::aura::document) pdoc =  (papp->m_ptemplateEdit->open_document_file(NULL, true, pcreatordata->m_pholder));
      ////      if(pdoc != NULL)
      ////      {
      ////         sp(::aura::impact) pview = pdoc->get_view();
      ////         if(pview != NULL)
      ////         {
      ////            sp(::user::frame_window) pframe = pview->GetParentFrame();
      ////            if(pframe != NULL)
      ////            {
      ////               pcreatordata->m_pdoc = pdoc;
      ////               pcreatordata->m_pwnd = pframe;
      ////            }
      ////         }
      ////      }
      ////   }
      ////   break;
      /////*case tarsila::PaneViewFileManager:
      ////   {
      ////      sp(::filemanager::manager) pdoc = Plat(papp).filemanager().std().open_child(papp, false, true, pcreatordata->m_pholder);
      ////      m_pfilemanagerdoc = pdoc;
      ////      if(pdoc != NULL)
      ////      {
      ////         sp(::aura::impact) pview = pdoc->get_view();
      ////         if(pview != NULL)
      ////         {
      ////            frame_window * pframe = (frame_window *) pview->GetParentFrame();
      ////            if(pframe != NULL)
      ////            {
      ////               pcreatordata->m_pdoc = pdoc;
      ////               pcreatordata->m_pwnd = pframe;

      ////               pdoc->Initialize(true);
      ////            }
      ////         }
      ////      }
      ////   }
      ////   break;*/


      //default:
      //   break;
      //}
      ::userex::pane_tab_view::on_create_view(pcreatordata);
   }


   void pane_view::install_message_handling(::message::dispatch * pinterface)
   {
      ::userex::pane_tab_view::install_message_handling(pinterface);
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &pane_view::_001OnCreate);
   }

   sp(::aura::document) pane_view::get_veriedit_document(const char * pszUrl)
   {
      sp(::tarsila::application) papp =  (get_app());
      ::count count = papp->m_pdoctemplate->get_document_count();
      string strPath(pszUrl);
      ::str::begins_eat_ci(strPath, "tarsila://");
      for(index i = 0; i < count; i++)
      {
         sp(::aura::document) pdoc =  (papp->m_pdoctemplate->get_document(i));
         if(pdoc != NULL && pdoc->get_file_path().CompareNoCase(strPath) == 0)
         {
            return pdoc;
         }
      }
      return NULL;
   }

   void pane_view::get_opened_documents(stringa & stra)
   {
      var_array vara;
      get_restore_tab(vara);
      stra = vara;
   }

} // namespace tarsila