#pragma once


namespace textformat
{


   class CLASS_DECL_DESIGN_TEXTFORMAT view :
      virtual public ::user::impact
   {
   public:


      string                              m_strServer;
      ::visual::dib_sp                    m_dibAi1;
      ::visual::dib_sp                    m_dibAi2;

      string                              m_strImage;
      ::draw2d::dib_sp                    m_dibColor;

      bool                                m_bOkPending;
      spa(::user::rich_text::edit)        m_edita;
      int                                 m_iTurn;


      view(::aura::application * papp);
      virtual ~view();


      virtual void assert_valid() const override;
      virtual void dump(dump_context & dumpcontext) const override;


      virtual int64_t add_ref() override
      {

         return ::object::add_ref();

      }

      virtual int64_t dec_ref() override
      {

         return ::object::dec_ref();

      }

      virtual void install_message_routing(::message::sender * psender) override;

      virtual void on_update(::user::impact * pSender, LPARAM lHint, object* pHint) override;

      ::user::document * get_document();

      virtual void _001OnDraw(::draw2d::graphics * pgraphics) override;

      virtual void on_layout() override;

      void fill(::user::rich_text::edit * pedit);

      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnDestroy);
      DECL_GEN_SIGNAL(_001OnLButtonDown);


   };


} // namespace textformat


