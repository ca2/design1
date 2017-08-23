#pragma once

namespace devedge
{

   class document;

   class CLASS_DECL_DEVEDGE view : 
      public ::user::plain_edit_view
   {
   public:
      
      view(::aura::application * papp);
      virtual ~view();

      void install_message_routing(::message::sender * pinterface);

      void on_update(::user::impact * pSender, LPARAM lHint, ::object * phint);

      virtual void _001OnAfterChangeText();


      sp(::devedge::document) get_document() const;
      
      DECL_GEN_SIGNAL(_001OnContextMenu);
      DECL_GEN_SIGNAL(_001OnUpdateEditUndo);
      DECL_GEN_SIGNAL(_001OnUpdateEditRedo);
      DECL_GEN_SIGNAL(_001OnEditUndo);
      DECL_GEN_SIGNAL(_001OnEditRedo);
      DECL_GEN_SIGNAL(_001OnUserMessage);

   #ifdef DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif

   };

} // namespace devedge