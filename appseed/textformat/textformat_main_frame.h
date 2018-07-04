#pragma once


namespace textformat
{


   class CLASS_DECL_APP_CORE_TEXTFORMAT main_frame :
      virtual public simple_frame_window
   {
   public:


      bool                       m_bExplicitTranslucency;
      ::composite::view *        m_pcompositeview;

      main_frame(::aura::application * papp);
      virtual ~main_frame();


      virtual void assert_valid() const override;
      virtual void dump(dump_context & dumpcontext) const override;

      virtual void install_message_routing(::message::sender * psender) override;

      DECL_GEN_SIGNAL(_001OnActivate);
      DECL_GEN_SIGNAL(_001OnMouseActivate);

      virtual bool on_create_bars() override;

      virtual sp(::user::wndfrm::frame::frame) create_frame_schema() override;

      virtual bool has_pending_graphical_update() override;

   };


} // namespace textformat












