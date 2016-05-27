#pragma once


namespace refactor
{


   class document;


   class CLASS_DECL_CA2_REFACTOR view :
      public ::user::plain_edit_view
   {
   public:


      string                  m_strServer;
      ::visual::fastblur      m_dib;
      ::draw2d::dib_sp        m_dibColor;
      ::draw2d::font_sp       m_font;
      string                  m_strHelloMultiverse;


      view(::aura::application * papp);
	   virtual ~view();

   #ifdef DEBUG
	   virtual void assert_valid() const;
	   virtual void dump(dump_context & dumpcontext) const;
   #endif

      virtual void _001OnDraw(::draw2d::graphics * pgraphics);

      virtual void on_update(::user::impact * pSender, LPARAM lHint, ::object* pHint);

      sp(document) get_document();

      virtual void on_auto_complete(index iSel, stringa & stra);

      void install_message_handling(::message::dispatch * pinterface);

      DECL_GEN_SIGNAL(_001OnUserMessage);


   };

} // namespace refactor
