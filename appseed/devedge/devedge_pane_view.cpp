#include "framework.h"


namespace devedge
{


   pane_view::pane_view(::aura::application * papp) :
      ::object(papp),
      ::user::tab(papp),
      
      ::user::tab_view(papp),
      ::userex::pane_tab_view(papp),
      place_holder_container(papp)
   {
//      m_etranslucency      = TranslucencyPresent;
      m_bShowDevEdge       = false;
   }

   pane_view::~pane_view()
   {
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

      sp(::devedge::application) papp =  (get_app());

      papp->m_ppaneview = this;

      add_tab("Front", PaneViewContextMenu);
      add_tab("DevEdge", PaneViewDevEdge);
      add_tab("HtmlDesigner", PaneViewHtmlEdit);
      add_tab("HtmlView", PaneViewHtmlStage);
      add_tab("FileManager", "file_manager");


      set_cur_tab_by_id(PaneViewDevEdge);


   }


   void pane_view::on_update(::user::impact * pSender, LPARAM lHint, ::object* pHint) 
   {

      sp(::devedge::application) papp =  (( (GetParentFrame()))->get_app());
      papp->devedge().m_ptemplate_devedge->update_all_views(pSender, lHint, pHint);
      papp->devedge().m_ptemplateHtmlEdit->update_all_views(pSender, lHint, pHint);

      if(pHint != NULL)
      {
         if(base_class < main_document >::bases(pHint))
         {
            ::devedge::pane_view_update_hint * puh = dynamic_cast < ::devedge::pane_view_update_hint * > (pHint);
            if(puh->is_type_of(::devedge::pane_view_update_hint::TypeGetView))
            {
               puh->m_eview = (EPaneView) atoi(get_cur_tab_id());
            }
            else if(puh->is_type_of(::devedge::pane_view_update_hint::TypeSetView))
            {
               set_cur_tab_by_id(puh->m_eview);
            }
         }
      }
         if(pHint != NULL)
      {
         if(base_class < main_document >::bases(pHint))
         {
            ::devedge::pane_view_update_hint * puh = dynamic_cast < ::devedge::pane_view_update_hint * > (pHint);
            if(puh->is_type_of(::devedge::pane_view_update_hint::TypeOnShowView))
            {
               if(puh->m_eview == PaneViewHtmlStage)
               {
                  sp(::devedge::application) papp =  (( (GetParentFrame()))->get_app());
                  sp(html_stage_document) pdocHtml =  (papp->devedge().m_ptemplateHtmlStage->get_document());
                  sp(::devedge::document) pdoc =  (papp->devedge().m_ptemplate_devedge->get_document());
                  string str;
                  pdoc->m_pview->_001GetText(str);
                  pdocHtml->get_html_data()->load(str);
                  pdocHtml->update_all_views(NULL, 123);
               }
            }
         }
      }
   }


   void pane_view::on_create_view(::user::view_creator_data * pcreatordata)
   {
      ::devedge::application & app = Application;
      if(pcreatordata->m_id.is_text())
      {
         string strPath(pcreatordata->m_id);
         if(::str::begins_eat_ci(strPath, "devedgefile://"))
         {
            pcreatordata->m_eflag.signalize(::user::view_creator_data::flag_hide_all_others_on_show);
            return;
         }
         else if(::str::begins_eat_ci(strPath, "devedge://"))
         {
            sp(::create) cc(get_app());
            cc->m_spCommandLine->m_varFile = strPath;
            cc->m_puiParent = this;
            sp(::user::document) pdoc =  (app.devedge().m_ptemplate_devedge->open_document_file(cc));
            if(pdoc != NULL)
            {
               sp(::user::impact) pview = pdoc->get_view();
               if(pview != NULL)
               {
                  sp(::user::frame_window) pframe =  (pview->GetParentFrame());
                  if(pframe != NULL)
                  {
                     pcreatordata->m_pdoc = pdoc;
                     pcreatordata->m_pwnd = pframe;
                  }
               }
            }
            return;
         }
      }
      else if(pcreatordata->m_id.is_integer())
      {
         switch(pcreatordata->m_id)
         {
         case PaneViewContextMenu:
            {
               sp(::create) cc(get_app());
               cc->m_spCommandLine->m_varFile = "http://localhost:10011/";
               cc->m_puiParent = pcreatordata->m_pholder;
               sp(front_document) pdoc =  (Application.devedge().m_ptemplateFront->open_document_file(cc));
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
         case PaneViewDevEdge:
            {
               sp(::user::document) pdoc =  (app.devedge().m_ptemplate_devedge->open_document_file(NULL, true, pcreatordata->m_pholder));
               pcreatordata->m_eflag.signalize(::user::view_creator_data::eflag::flag_hide_all_others_on_show);
               if(pdoc != NULL)
               {
                  sp(::user::impact) pview = pdoc->get_view(0);
                  if(pview != NULL)
                  {
                     sp(::user::frame_window) pframe =  (pview->GetParentFrame());
                     if(pframe != NULL)
                     {
                        pcreatordata->m_pdoc = pdoc;
                        pcreatordata->m_pwnd = pframe;


                     }
                  }
               }
            }
            break;
         case PaneViewHtmlEdit:
            {
               sp(::create) cc(get_app());
               cc->m_spCommandLine->m_varFile = "E:\\temp\\html.html";
               cc->m_puiParent = this;
               sp(::user::document) pdoc =  (Application.devedge().m_ptemplateHtmlEdit->open_document_file(cc));
               if(pdoc != NULL)
               {
                  sp(::user::impact) pview = pdoc->get_view();
                  if(pview != NULL)
                  {
                     sp(::user::frame_window) pframe =  (pview->GetParentFrame());
                     if(pframe != NULL)
                     {
                        pcreatordata->m_pdoc = pdoc;
                        pcreatordata->m_pwnd = pframe;
                     }
                  }
               }
            }
            break;
         case PaneViewHtmlStage:
            {
               sp(html_stage_document) pdoc =  (app.devedge().m_ptemplateHtmlStage->open_document_file(NULL, true, pcreatordata->m_pholder));
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
         case PaneViewSolution:
            {
               sp(::create) cc(get_app());
               cc->m_puiParent = this;
               sp(::devedge::solution_document) pdoc =  (app.devedge().m_ptemplate_solution->open_document_file(cc));
               if(pdoc != NULL)
               {
                  sp(::user::impact) pview = pdoc->get_view();
                  if(pview != NULL)
                  {
                     sp(::user::frame_window) pframe =  (pview->GetParentFrame());
                     if(pframe != NULL)
                     {
                        pcreatordata->m_pdoc = pdoc;
                        pcreatordata->m_pwnd = pframe;


                     }
                  }
               }
            }
            break;

         default:
            break;
         }
      }

      ::userex::pane_tab_view::on_create_view(pcreatordata);

   }


   void pane_view::rotate()
   {
   }

   void pane_view::install_message_handling(::message::dispatch * pinterface)
   {
      ::userex::pane_tab_view::install_message_handling(pinterface);
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &pane_view::_001OnCreate);
   }


   void pane_view::on_show_view()
   {
      if(m_pviewdata->m_id == PaneViewDevEdge)
      {
         if(m_spcreatecontext.is_set())
         {
            Application.devedge().m_ptemplate_devedge->get_document(0)->on_open_document(m_spcreatecontext->m_spCommandLine->m_varFile);
         }

      }
      ::userex::pane_tab_view::on_show_view();
      /*if(m_pviewdata->m_id == PaneViewDevEdge 
      && !m_pviewdata->m_idSplit.has_char())
      {
         if(!m_bShowDevEdge)
         {
            keeper < bool > keepShowDevEdge(&m_bShowDevEdge, true, false, true);
            set_cur_tab_by_id(PaneViewSolution);
            m_pviewdata->m_pwnd->m_etranslucency = TranslucencyNone;
         }
      }*/
   }

   sp(::user::document) pane_view::open_file(sp(::create) pcreatecontext)
   {
      ensure_tab_by_id("devedge://" + string(pcreatecontext->m_spCommandLine->m_varFile));
      return get("devedge://" + string(pcreatecontext->m_spCommandLine->m_varFile))->m_pdoc;
   }


} // namespace devedge


