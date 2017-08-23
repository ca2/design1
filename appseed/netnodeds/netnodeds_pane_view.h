#pragma once


namespace netnodeds 
{


   class CLASS_DECL_DESIGN_NETNODEDS pane_view : 
      public ::userex::pane_tab_view
   {
   public:


      bool m_bShowDevEdge;


      pane_view(::aura::application * papp);
      virtual ~pane_view();


      virtual void install_message_routing(::message::sender * pinterface);
      virtual void on_update(::user::impact * pSender, LPARAM lHint, ::object* pHint);

      virtual void on_create_view(::user::view_creator_data * pcreatordata);

      void rotate();


      sp(::user::document) open_file(::create * pcreate);

      void on_show_view();
      DECL_GEN_SIGNAL(_001OnCreate);
   #ifdef DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif


   };


} // namespace netnodeds


