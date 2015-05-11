#include "framework.h"


namespace syllomatter
{


   main_document::main_document(::aura::application * papp) :
      ::object(papp),
      ::data::data_container_base(papp),
      ::aura::document(papp)
   {

      connect_command("syllomatter_commit", &::syllomatter::main_document::_001OnCommit_);
      connect_command("syllomatter_update", &::syllomatter::main_document::_001OnUpdate);
      connect_command("major_checkout",&::syllomatter::main_document::_001OnMajorCheckout);

   }
   
   main_document::~main_document()
   {
   }

   void main_document::_001OnMajorCheckout(::signal_details * pobj)
   {
      ::fs::item_array itema;


      get_typed_view < pane_view >()->filemanager_manager().GetActiveViewSelection(itema);
      get_typed_view < pane_view >()->set_cur_tab_by_id(syllomatter::PaneViewSVN);
      

      if(itema.get_count() == 1 && Application.dir().is(itema[0]->m_strPath))
      {
      
         ::MessageBox(NULL,itema[0]->m_strPath,"Going to Major Checkout... :",MB_ICONINFORMATION);
      }
      else
      {
         ::MessageBox(NULL,get_typed_view < pane_view >()->filemanager_manager().get_filemanager_item().m_strPath,"Going to Major Checkout... :",MB_ICONINFORMATION);

      }



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


