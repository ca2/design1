#pragma once


namespace userex
{


   class CLASS_DECL_DESIGN_TEXTFORMAT dialog_frame :
      virtual public ::simple_frame_window
   {
   public:


      bool                       m_bExplicitTranslucency;


      dialog_frame(::aura::application * papp);
      virtual ~dialog_frame();


      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;


      virtual bool pre_create_window(::user::create_struct& cs) override;

      virtual void install_message_routing(::message::sender * pinterface);


      //using ::sphere::dialog_frame::get_translucency;
      //virtual bool get_translucency(::user::e_translucency & etranslucency, ::user::e_element eelement, ::user::style_context * pcontext) override;
      virtual sp(::user::wndfrm::frame::frame) create_frame_schema();

      virtual bool has_pending_graphical_update();


      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnActivate);
      DECL_GEN_SIGNAL(_001OnMouseActivate);


   };


} // namespace userex












