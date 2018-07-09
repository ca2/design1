#pragma once


namespace user
{


   namespace rich_text
   {


      class CLASS_DECL_DESIGN_TEXTFORMAT edit :
         virtual public ::user::control,
         virtual public ::user::pic
      {
      public:


         data                          m_data;
         bool                          m_bSelDrag;
         ::message::key                m_keymessageLast;
         bool                          m_bKeyPressed;


         edit();
         edit(::aura::application * papp);
         virtual ~edit();

         virtual void on_after_change(::user::e_event eevent);
         virtual double get_rotate() override;

         virtual index hit_test(point point, ::user::e_element & eelement) override;

         virtual bool get_item_rect(LPRECT lprect, index i);
         virtual bool get_element_rect(LPRECT lprect, index i, e_element eelement);

         virtual ::sized get_size() override;

         virtual void assert_valid() const override;
         virtual void dump(dump_context & dumpcontext) const override;

         virtual bool _001GetItemText(string & str, index iItem);
         virtual bool _001IsPointInside(point64 pt) override;
         virtual bool update_data(bool bSaveAndValidate) override;
         virtual void update_placement() override;


         virtual int64_t add_ref() override
         {
            return ::object::add_ref();
         }
         virtual int64_t dec_ref() override
         {
            return ::object::dec_ref();
         }


         virtual void on_selection_change();

         virtual void install_message_routing(::message::sender * psender) override;

         virtual void _001OnDraw(::draw2d::graphics * pgraphics) override;

         virtual void draw_impl(::draw2d::graphics * pgraphics, LPCRECT lpcrect) override;

         ::userex::font_format_tool * get_sys_format_tool();

         virtual void _001GetText(string & str) const override;
         virtual void _001GetLayoutText(string & str) const;

         virtual void on_layout() override;

         DECL_GEN_SIGNAL(_001OnCreate);
         DECL_GEN_SIGNAL(_001OnDestroy);
         DECL_GEN_SIGNAL(_001OnLButtonDown);
         DECL_GEN_SIGNAL(_001OnLButtonUp);
         DECL_GEN_SIGNAL(_001OnMouseMove);
         DECL_GEN_SIGNAL(_001OnMouseLeave);
         DECL_GEN_SIGNAL(_001OnChar);
         DECL_GEN_SIGNAL(_001OnKeyDown);
         DECL_GEN_SIGNAL(_001OnKeyUp);


         virtual void _001OnTimer(::timer * ptimer) override;


         virtual void key_to_char(::message::key * pkey);


         virtual bool keyboard_focus_is_focusable() override;


         virtual void keyboard_focus_OnChar(::message::message * pobj) override;


         virtual void on_control_event(::user::control_event * pevent) override;


         virtual strsize _001GetTextLength() const override;

         virtual void stream(serialize & serialize) override;

      };


   } // namespace rich_text


} // namespace user



