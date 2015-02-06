#pragma once


namespace biteditor
{


   class CLASS_DECL_CA2_BITEDITOR pane_view : 
      virtual public ::userex::pane_tab_view
   {
   public:


      pane_view(::aura::application * papp);
      virtual ~pane_view();


      void on_create_view(::user::view_creator_data * pcreatordata);

      void install_message_handling(::message::dispatch * pinterface);
      
   #ifdef DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif

      DECL_GEN_SIGNAL(_001OnCreate);


   };


} // namespace biteditor



