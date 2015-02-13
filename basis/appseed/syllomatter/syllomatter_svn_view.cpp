#include "framework.h"


namespace syllomatter
{


   svn_view::svn_view(::aura::application * papp) :
      ::object(papp),
      ::user::split_layout(papp),
      
      ::user::split_view(papp),
      place_holder_container(papp)
   {
   }

   svn_view::~svn_view()
   {
   }



   void svn_view::CreateViews()
   {

      SetPaneCount(2);

      SetSplitOrientation(orientation_horizontal);

      set_position_rate(0, 0.3);

      initialize_split_layout();

      /*   create_context cc;
      cc.m_pCurrentDoc = get_document();
      cc.m_typeinfoNewView =  System.type_info < ::user::edit_plain_text_view > ();*/

      ::user::edit_plain_text_view * ptopview = create_view < ::user::edit_plain_text_view > ();
      m_peditview = ptopview;
      if(ptopview == NULL)
      {
         System.simple_message_box(NULL, "Could not create folder tree ::view");
      }
      SetPane(0, ptopview, true);

      //   cc.m_pCurrentDoc = get_document();
      //cc.m_typeinfoNewView =  &ca;


      sp(list_view) plistview = create_view < list_view > ();
      m_plistview = plistview;
      if(m_plistview == NULL)
      {
         System.simple_message_box(NULL, "Could not create file list ::view");
      }
      m_plistview->m_psvnview = this;
      SetPane(1, m_plistview, true);
      layout();
   }




} // namespace syllomatter




