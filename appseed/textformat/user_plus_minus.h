#pragma once


namespace user
{


   class CLASS_DECL_DESIGN_TEXTFORMAT plus_minus :
      virtual public control
   {
   public:


      bool                 m_bLabel;

      int                  m_i;
      int                  m_iMin;
      int                  m_iMax;
      int                  m_iStep;
      ::user::still        m_still;
      ::user::button       m_buttonMinus;
      ::user::button       m_buttonPlus;

      string               m_strMin;
      string               m_strMax;
      string               m_strFormat;



      plus_minus();
      plus_minus(::aura::application * papp, bool bLabel = true);
      virtual ~plus_minus();


      virtual void install_message_routing(::message::sender * psender);


      DECL_GEN_SIGNAL(_001OnCreate);
      //DECL_GEN_SIGNAL(_001OnLButtonDown);
      //DECL_GEN_SIGNAL(_001OnLButtonUp);
      //DECL_GEN_SIGNAL(_001OnMouseMove);
      //DECL_GEN_SIGNAL(_001OnMouseLeave);


      void on_layout();


      //virtual void _001OnDraw(::draw2d::graphics * pgraphics) override;

      virtual void on_control_event(::user::control_event * pevent) override;


      virtual string calc_still_label();

      virtual void set_value(int iValue, ::action::context context);

      virtual void on_update();

   };


} //  namespace user



