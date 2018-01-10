#pragma once


namespace refactor
{

   class view;

   class CLASS_DECL_CA2_REFACTOR pane_view : 
      public ::userex::pane_tab_view
   {
   public:


      ::refactor::view *                     m_pflagview;


      pane_view(::aura::application * papp);
	   virtual ~pane_view();

	   virtual void assert_valid() const;
	   virtual void dump(dump_context & dumpcontext) const;
      
      void on_create_view(::user::view_creator_data * pcreatordata);

      virtual void install_message_routing(::message::sender * pinterface);


      DECL_GEN_SIGNAL(_001OnCreate);

   };


} // namespace refactor


