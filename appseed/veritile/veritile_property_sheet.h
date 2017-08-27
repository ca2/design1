#pragma once




namespace veritile
{


   using base_form_list_view = ::user::show < ::user::form_list >;



   class CLASS_DECL_APP_CORE_VERITILE property_sheet:
      virtual public base_form_list_view
   {
   public:

      class CLASS_DECL_APP_CORE_VERITILE callback
      {
      public:


         virtual void on_property_change(property & property);


      };


      general_data *          m_pdata;


      ::draw2d::font_sp       m_font;


      callback *              m_pcallback;


      property_sheet(::aura::application * papp);
      virtual ~property_sheet();

      void install_message_routing(::message::sender * pinterface);

      void on_update(::user::impact * pSender,LPARAM lHint,::object * phint);

      virtual void _001OnAfterChangeText(::action::context actioncontext);

      virtual void _001InsertColumns();


      //virtual void _001OnDraw(::draw2d::graphics * pgraphics);

      virtual void _001GetItemText(::user::mesh_item * pitem);


      virtual void draw_item(::draw2d::graphics * pgraphics,int x,int y,general_data::item * pitem);
      virtual void draw_framing(::draw2d::dib * pdib);

      virtual void load_plain_text(const string & str);


      //sp(::verigrid::document) get_document() const;

      DECL_GEN_SIGNAL(_001OnCreate);

      DECL_GEN_SIGNAL(_001OnContextMenu);
      DECL_GEN_SIGNAL(_001OnUpdateEditUndo);
      DECL_GEN_SIGNAL(_001OnUpdateEditRedo);
      DECL_GEN_SIGNAL(_001OnUpdateMediaTransfer);

      DECL_GEN_SIGNAL(_001OnEditUndo);
      DECL_GEN_SIGNAL(_001OnEditRedo);
      DECL_GEN_SIGNAL(_001OnMediaTransfer);

#ifdef DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
#endif

      virtual void on_command(e_simple_command ecommand,lparam lparam,LRESULT & lresult);


      virtual bool keyboard_focus_OnSetFocus() override;


      virtual bool get_font(::draw2d::font_sp & spfont);

      virtual count _001GetItemCount();

      virtual count _001GetColumnCount();

      bool get_color(COLORREF & cr,::user::e_color ecolor);


      void set_data(general_data * pdata, callback * pcallback);

      virtual bool _001OnSetItemText(::user::interaction * pui,index iItem,index iSubItem) override;
      virtual bool _001OnControlSetFocus(::user::interaction * pui) override;
      
      
      virtual bool validate(::user::interaction * pui, index iItem, bool bInteract);


      bool BaseOnControlEvent(::user::control_event * pevent);


   };


} // namespace verigrid













