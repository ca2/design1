#include "framework.h"


namespace devedge
{


   solution_view::solution_view(::aura::application * papp) :
      ::object(papp),
      ::user::tree(papp)
   {

   }


   bool solution_view::load()
   {

      sp(solution_document) pdoc =  (get_document());
      
      m_psolution = pdoc->m_psolution;

      ::data::tree * ptree = m_treeptra[0];

      ptree->remove_all();
      //get_base_item()->remove_tree_item_descendants();

      ptree->insert_item(m_psolution,::data::RelativeFirstChild,ptree->get_base_item());

      m_psolution->m_strName = pdoc->get_file_path().name();
      m_psolution->m_strName += ", ";
      ::file::patha straAscendants;
      pdoc->get_file_path().ascendants_name(straAscendants);

      if(straAscendants.get_count() >= 4)
      {
         ::file::path path = straAscendants.implode("/", 3, MIN(straAscendants.get_count(), 3));
         m_psolution->m_strName += path;
      }


      sp(::xml::node) pnodeProjects = m_psolution->node_get_projects();
      if(pnodeProjects != NULL)
      {
         for(int32_t i = 0; i < pnodeProjects->get_children_count(); i++)
         {
            sp(::xml::node) pnodeProject = pnodeProjects->child_at(i);
            if(pnodeProject->get_name() == "project")
            {
               ::devedge::project * pproject = new ::devedge::project(get_app());
               ptree->insert_item(pproject, ::data::RelativeLastChild, m_psolution);
               pproject->m_strName = pnodeProject->attr("path");
               m_psolution->m_projectptra.add(pproject);
               pproject->load(m_psolution, pnodeProject);


               ptree->insert_item(&pproject->m_headers,::data::RelativeLastChild,pproject);
               pproject->m_headers.m_strName = "Header Files";
               
               for(int32_t j = 0; j < pproject->m_headers.get_count(); j++)
               {
                  ptree->insert_item(pproject->m_headers[j],::data::RelativeLastChild,&pproject->m_headers);
                  //pproject->m_headers[j].m_strName = pproject->m_headers[j].m_strName;
               }



               ptree->insert_item(&pproject->m_source, ::data::RelativeLastChild, pproject);
               pproject->m_source.m_strName = "Source Files";
               
               for(int32_t j = 0; j < pproject->m_source.get_count(); j++)
               {
                  ptree->insert_item(pproject->m_source[j],::data::RelativeLastChild,&pproject->m_source);
                  //pproject->m_source[j].m_strName = pproject->m_source[j].m_strName;
               }



            }

         }

      }

      return true;


   }


   void solution_view::install_message_handling(::message::dispatch * pinterface)
   {

      ::user::impact::install_message_handling(pinterface);
      ::user::tree::install_message_handling(pinterface);
      IGUI_WIN_MSG_LINK(WM_CREATE,pinterface,this,&solution_view::_001OnCreate);

   }

   void solution_view::_001OnCreate(signal_details* pobj)
   {
      SCAST_PTR(message::create,pcreate,pobj);

      pcreate->previous();

      merge(new ::devedge::solution_tree_data(get_app()), true);


   }

   void solution_view::_001OnOpenItem(sp(::data::tree_item) pitem)
   {
      
      sp(file) pfile =  pitem;
      
      if(pfile != NULL)
      {
         
         sp(pane_view) pview = Application.::devedge::application::m_ppaneview;
         pview->ensure_pane_by_id("devedgefile://" + pfile->m_strPath);

         sp(::user::interaction) puieParent = pview->get_pane_by_id("devedgefile://" + pfile->m_strPath)->m_pholder;

         pfile->open(puieParent);

         pview->set_cur_tab_by_id("devedgefile://" + pfile->m_strPath);

         puieParent->layout();

/*         ::user::split_layout * psplit = dynamic_cast < ::user::split_layout * > (puieParent);
         if(psplit != NULL)
         {
            psplit->get_pane_window(1)->ShowWindow(SW_HIDE);
            psplit->SetPane(1, pfile->m_pdocument->get_edit_view()->GetParentFrame(), false);
            psplit->layout();
         }*/

      }

   }   


} // namespace devedge



