#pragma once


namespace user
{


   class CLASS_DECL_DESIGN_TEXTFORMAT menu_view :
      virtual public ::user::impact
   {
   public:


      ::draw2d::dib_sp     m_dibMem;
      ::xml::document      m_xmldoc;
      ::draw2d::dib_sp     m_dibLogo;
      ::draw2d::font_sp    m_fontTitle;
      ::draw2d::font_sp    m_font;
      ::draw2d::brush_sp   m_brBkSel;
      ::draw2d::brush_sp   m_brBkHoverSel;
      ::draw2d::pen_sp     m_penBkSel;
      ::draw2d::pen_sp     m_pen;
      int                  m_iHover;
      int                  m_iMenuHover;
      int                  m_iCommandHover;
      int                  m_iMenuSel;
      int                  m_iCommandSel;
      string_map < ::draw2d::dib_sp >  m_dibMap;
      string_map < ::draw2d::dib_sp >  m_dibMapGray;
      int_array            m_iaPopup;

      menu_view(::aura::application * papp);
      virtual ~menu_view();

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

      virtual void _001OnDraw(::draw2d::graphics * pgraphics) override;

      virtual void on_update(::user::impact * pSender, LPARAM lHint, object* pHint) override;

      ::user::document * get_document();

      bool load_xml(var varFile);

      virtual void on_layout() override;

      DECL_GEN_SIGNAL(_001OnLayout);
      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnDestroy);
      DECL_GEN_SIGNAL(_001OnLButtonDown);
      DECL_GEN_SIGNAL(_001OnMouseMove);
      DECL_GEN_SIGNAL(_001OnMouseLeave);

      virtual bool get_item_rect(int i, LPRECT lprect);

      virtual int hit_test(point pt, int & iCommand, int & iMenu);

      virtual void draw_border_rectangle(::draw2d::graphics * pgraphics, LPCRECT lpcrect);
      virtual void draw_header_separator(::draw2d::graphics * pgraphics, LPPOINT ppt1, LPPOINT ppt2);
      virtual void draw_header_rectangle(::draw2d::graphics * pgraphics, LPCRECT lpcrect);
      virtual void draw_item_rectangle(::draw2d::graphics * pgraphics, LPCRECT lpcrect);
      virtual void draw_item_rectangle_hover001(::draw2d::graphics * pgraphics, LPCRECT lpcrect);
      virtual void draw_item_rectangle_sel001(::draw2d::graphics * pgraphics, LPCRECT lpcrect);
      virtual void draw_item_rectangle_hover_sel001(::draw2d::graphics * pgraphics, LPCRECT lpcrect);
      virtual void draw_item_separator(::draw2d::graphics * pgraphics, LPPOINT ppt1, LPPOINT ppt2);


   };


} // namespace user


