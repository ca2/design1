#pragma once


namespace devedge 
{


   class CLASS_DECL_DEVEDGE pane_view : 
      public ::userex::pane_tab_view
   {
   public:


      bool m_bShowDevEdge;


      pane_view(::aura::application * papp);
      virtual ~pane_view();


      virtual void install_message_handling(::message::dispatch * pinterface);
      virtual void on_update(::user::impact * pSender, LPARAM lHint, ::object* pHint);

      virtual void on_create_view(::user::view_creator_data * pcreatordata);

      void rotate();


      sp(::aura::document) open_file(sp(::create) pcreatecontext);

      void on_show_view();
      DECL_GEN_SIGNAL(_001OnCreate);
   #ifdef DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif


   };


} // namespace devedge


