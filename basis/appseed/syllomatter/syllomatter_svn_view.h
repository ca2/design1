#pragma once


namespace syllomatter
{


   class CLASS_DECL_CA2_SYLLOMATTER svn_view :
      public ::user::split_view
   {
   public:
      
      sp(pane_view)                            m_ppaneview;
      ::user::edit_plain_text_view *     m_peditview;
      sp(list_view)                            m_plistview;


      svn_view(::aura::application * papp);
      virtual ~svn_view();

      void CreateViews();


   };


} // namespace syllomatter


