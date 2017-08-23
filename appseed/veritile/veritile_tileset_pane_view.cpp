#include "framework.h"


namespace veritile
{


   tileset_pane_view::tileset_pane_view(::aura::application * papp):
      ::object(papp),
      ::user::tab(papp),

      ::user::tab_view(papp),
      ::userex::pane_tab_view(papp),
      place_holder_container(papp)
   {

      m_dataid = ".local://";

      get_data()->m_bVertical = false;

   }

   tileset_pane_view::~tileset_pane_view()
   {
   }



#ifdef DEBUG
   void tileset_pane_view::assert_valid() const
   {
      ::user::impact::assert_valid();
   }

   void tileset_pane_view::dump(dump_context & dumpcontext) const
   {
      ::user::impact::dump(dumpcontext);
   }
#endif //DEBUG


   void tileset_pane_view::_001OnCreate(::message::message * pobj)
   {
      if(pobj->previous())
         return;


   }


   void tileset_pane_view::on_update(::user::impact * pSender,LPARAM lHint,::object* pHint)
   {
      UNREFERENCED_PARAMETER(pSender);
      UNREFERENCED_PARAMETER(lHint);
      UNREFERENCED_PARAMETER(pHint);

   }

   void tileset_pane_view::on_show_view()
   {

      ::userex::pane_tab_view::on_show_view();

      get_pane_by_id(get_current_id())->m_bPermanent = true;

      if(::str::begins_ci(m_pviewdata->m_id,"veritile://"))
      {

         //m_pdocCur = dynamic_cast < document * > (m_pviewdata->m_pdoc);

         m_pviewCur = dynamic_cast <tileset_view *> (m_pviewdata->m_pholder->top_child());

         GetParentFrame()->LoadToolBar(0,"edit_toolbar.xml");

         //         show_tab_by_id("printer");

      }
      else if(m_pviewdata->m_id == "printer")
      {
         ::simple_printer_list_view * pview = get_document()->get_typed_view < ::simple_printer_list_view >();
         pview->m_pview = m_pviewdataOld->m_pdoc->get_view();
      }
      else
      {
         show_tab_by_id("printer",false);
      }
   }


   bool tileset_pane_view::pre_create_window(::user::create_struct& cs)
   {
      cs.dwExStyle &= ~WS_EX_CLIENTEDGE;

      return ::user::impact::pre_create_window(cs);
   }


   void tileset_pane_view::on_create_view(::user::view_creator_data * pcreatordata)
   {

      ::file::path strId(pcreatordata->m_id.str());

      sp(tileset) ptileset = Application.m_ppaneview->m_pdocCur->get_tileset(strId);

      sp(tileset_view) pview = create_view < tileset_view >(Application.m_ppaneview->m_pdocCur,::null_rect(),pcreatordata->m_pholder);

      pview->initialize(ptileset);

      pcreatordata->m_eflag.signalize(::user::view_creator_data::flag_hide_all_others_on_show);

   }


   void tileset_pane_view::install_message_routing(::message::sender * pinterface)
   {
      ::userex::pane_tab_view::install_message_routing(pinterface);
      IGUI_WIN_MSG_LINK(WM_CREATE,pinterface,this,&tileset_pane_view::_001OnCreate);
   }

   sp(::user::document) tileset_pane_view::get_veriedit_document(const char * pszUrl)
   {
      sp(::veritile::application) papp =  (get_app());
      ::count count = papp->m_pdoctemplate->get_document_count();
      string strPath(pszUrl);
      ::str::begins_eat_ci(strPath,"veritile://");
      for(index i = 0; i < count; i++)
      {
         sp(::user::document) pdoc =  (papp->m_pdoctemplate->get_document(i));
         if(pdoc != NULL && pdoc->get_file_path().compare_ci(strPath) == 0)
         {
            return pdoc;
         }
      }
      return NULL;
   }

   void tileset_pane_view::get_opened_documents(stringa & stra)
   {
      var_array vara;
      get_restore_tab(vara);
      stra = vara;
   }

   //void tileset_pane_view::on_property_change(property & property)
   //{
   //}


} // namespace veritile