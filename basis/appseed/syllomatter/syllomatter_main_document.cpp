#include "framework.h"


namespace syllomatter
{


   main_document::main_document(::aura::application * papp) :
      element(papp),
      ::data::data_container_base(papp),
      ::aura::document(papp)
   {

      connect_command("syllomatter_commit", &::syllomatter::main_document::_001OnCommit_);
      connect_command("syllomatter_update", &::syllomatter::main_document::_001OnUpdate);

   }
   
   main_document::~main_document()
   {
   }


   void main_document::_001OnCommit_(::signal_details * pobj)
   {
  
   
      UNREFERENCED_PARAMETER(pobj);


      ::fs::item_array itema;


      get_typed_view < pane_view > ()->filemanager_manager().GetActiveViewSelection(itema);
      get_typed_view < pane_view > ()->set_cur_tab_by_id(syllomatter::PaneViewSVN);
      get_typed_view < pane_view > ()->m_psvnview->m_plistview->Commit_(itema);


   }


   void main_document::_001OnUpdate(::signal_details * pobj)
   {
   
      UNREFERENCED_PARAMETER(pobj);
   
      ::fs::item_array itema;

      itema.add(get_typed_view < pane_view > ()->filemanager_manager().m_item);

      get_typed_view < pane_view > ()->set_cur_tab_by_id(syllomatter::PaneViewSVN);

      get_typed_view < pane_view > ()->m_psvnview->m_plistview->Update(itema);


   }

} // namespace syllomatter


