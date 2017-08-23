#pragma once

namespace tarsila
{

   class document;

   class CLASS_DECL_APP_CORE_TARSILA pane_view : 
      virtual public ::userex::pane_tab_view
   {
   public:

      sp(::user::single_document_template)    m_pdoctemplateExtractChanges;

      pane_view(::aura::application * papp);
      virtual ~pane_view();

   
      virtual void on_create_view(::user::view_creator_data * pcreatordata);
      virtual void on_show_view();

      virtual void install_message_routing(::message::sender * pinterface);

      virtual void on_update(::user::impact * pSender, LPARAM lHint, ::object* pHint);
      virtual bool pre_create_window(::user::create_struct& cs);


      virtual sp(::user::document) get_veriedit_document(const char * pszUrl);

      virtual void get_opened_documents(stringa & stra);

   #ifdef DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif

      DECL_GEN_SIGNAL(_001OnCreate);
   };

} // namespace tarsila