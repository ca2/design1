#pragma once


namespace user
{


   class CLASS_DECL_DESIGN_TEXTFORMAT color_combo_box :
      virtual public control
   {
   public:


      ::color::hls         m_hls;
      bool                 m_bMouseDown;


      color_combo_box();
      color_combo_box(::aura::application * papp);
      virtual ~color_combo_box();


      virtual void install_message_routing(::message::sender * psender) override;


      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnLButtonDown);
      DECL_GEN_SIGNAL(_001OnLButtonUp);
      DECL_GEN_SIGNAL(_001OnMouseMove);
      DECL_GEN_SIGNAL(_001OnMouseLeave);


      void on_layout() override;


      virtual void _001OnDraw(::draw2d::graphics * pgraphics) override;



   };


} //  namespace user



