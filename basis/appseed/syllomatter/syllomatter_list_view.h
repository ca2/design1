#pragma once


namespace syllomatter
{

   class pane_view;
   class svn_view;

   class CLASS_DECL_CA2_SYLLOMATTER list_view :
      public simple_list_view
   {
   public:


      class CLASS_DECL_CA2_SYLLOMATTER update_thread : public simple_thread
      {
      public:
         update_thread(::aura::application * papp);
         sp(list_view) m_plistview;
         ::fs::item_array m_itema;
         int32_t run();
      };

      class CLASS_DECL_CA2_SYLLOMATTER commit_thread : public simple_thread
      {
      public:
         commit_thread(::aura::application * papp);
         sp(list_view) m_plistview;
         stringa m_straStatus;
         stringa m_stra;
         string m_str;
         int32_t run();
      };

      stringa m_straStatus;
      stringa m_stra;

      update_thread m_updatethread;
      commit_thread m_committhread;

      ::user::list_cache               m_cache;
      simple_list_header_control       m_headerctrl;
      ::fs::item_array       m_itema;
      sp(pane_view)    m_ppaneview;
      svn_view *                 m_psvnview;


      list_view(::aura::application * papp);
      virtual ~list_view();


      virtual void install_message_handling(::message::dispatch * pinterface);


      virtual void Commit_(::fs::item_array & itema);
      virtual void Update(::fs::item_array & itema);

      static void Commit_Swap(LPVOID lparg, index dwa, index dwb);
      static int32_t CompareStatus(LPVOID lparg, index dwa, index dwb);
      static int32_t ComparePath(LPVOID lparg, index dwa, index dwb);

      virtual count _001GetItemCount();
      virtual void _001GetItemText(::user::list_item * pitem);

      static index StatusSortWeight(string & strStatus);

      virtual void _001GetItemColor(::user::list_item * pitem);


      void _001GetItemImage(::user::list_item * pitem);





      void _001InsertColumns();

      DECL_GEN_SIGNAL(_001OnCreate);
         DECL_GEN_SIGNAL(_001OnGeneralEvent);

         DECL_GEN_SIGNAL(_001OnAdd);
         DECL_GEN_SIGNAL(_001OnUpdateAdd);
         DECL_GEN_SIGNAL(_001OnDelete);
         DECL_GEN_SIGNAL(_001OnUpdateDelete);
         DECL_GEN_SIGNAL(_001OnRevert);
         DECL_GEN_SIGNAL(_001OnUpdateRevert);
         DECL_GEN_SIGNAL(_001OnDoCommit);
         DECL_GEN_SIGNAL(_001OnUpdateDoCommit);
         DECL_GEN_SIGNAL(_001OnVerisvnwellListMessage);


         virtual void LibsvnMinimalClientTest();


   };


} // namespace syllomatter


