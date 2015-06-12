#pragma once


#include "syllomatter_pane_view_update_hint.h"


namespace syllomatter
{


   class CLASS_DECL_CA2_SYLLOMATTER pane_view : 
      virtual public ::userex::pane_tab_view
   {
   public:

      sp(::user::single_document_template)    m_pdoctemplateExtractChanges;
      ::syllomatter::svn_view *                 m_psvnview;
      sp(::syllomatter::document)                 m_pdocForm;
      ::syllomatter::view  *                    m_pviewForm;

      pane_view(::aura::application * papp);
      virtual ~pane_view();


      virtual void on_create_view(::user::view_creator_data * pcreatordata);
      virtual void on_show_view();

      virtual void install_message_handling(::message::dispatch * pinterface);

      virtual void on_update(::user::impact * pSender, LPARAM lHint, ::object* pHint);
      virtual bool pre_create_window(::user::create_struct& cs);



#ifdef DEBUG
         virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
#endif


      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnMenuMessage);
      DECL_GEN_SIGNAL(_001OnStartVerisvnwellExtract);



   };



} // namespace syllomatter



