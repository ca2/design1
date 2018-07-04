#pragma once


namespace userex
{


   class CLASS_DECL_APP_CORE_TEXTFORMAT font_format_tool :
      virtual public ::user::tool_window
   {
   public:


      ::user::rich_text::attribute_flags     m_eattributea;
      ::user::rich_text::format              m_format;
      ::user::button                         m_buttonBold;
      ::user::button                         m_buttonItalic;
      ::user::button                         m_buttonUnderline;
      ::user::font_combo_box                 m_comboFamily;
      ::user::combo_box                      m_comboSize;
      ::user::button                         m_buttonForeground;
      ::user::button                         m_buttonBackground;
      ::user::button                         m_buttonSubscript;
      ::user::button                         m_buttonSuperscript;
      ::user::button                         m_buttonLineHeight;
      ::user::button                         m_buttonAlignLeft;
      ::user::button                         m_buttonAlignCenter;
      ::user::button                         m_buttonAlignRight;



      font_format_tool();
      font_format_tool(::aura::application * papp);
      virtual ~font_format_tool();


      virtual void install_message_routing(::message::sender * psender) override;

      DECL_GEN_SIGNAL(_001OnCreate);

      virtual void set_font_size(double d);

      virtual void _001OnDraw(::draw2d::graphics * pgraphics) override;


      virtual void on_layout() override;

      virtual void show_for_ui(::user::interaction * pui);

      virtual void on_control_event(::user::control_event * pevent) override;


      virtual bool update_data(bool bSaveAndValidate) override;




   };




} // namespace user


