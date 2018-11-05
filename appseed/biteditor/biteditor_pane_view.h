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

      void install_message_routing(::message::sender * pinterface);


      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;


      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnMenuMessage);


   };


} // namespace biteditor



