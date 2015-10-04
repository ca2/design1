#pragma once




namespace veritile
{


   using base_grid_view = ::user::show < ::user::form_mesh >;



   class CLASS_DECL_APP_CORE_VERITILE property_sheet:
      virtual public base_grid_view
   {
   public:



      general_data *          m_pdata;


      ::draw2d::font_sp       m_font;

      property_sheet(::aura::application * papp);
      virtual ~property_sheet();

      void install_message_handling(::message::dispatch * pinterface);

      void on_update(::user::impact * pSender,LPARAM lHint,::object * phint);

      virtual void _001OnAfterChangeText(::action::context actioncontext);


      //virtual void _001OnDraw(::draw2d::graphics * pgraphics);

      //*virtual void _001GetItemText(::user::mesh_item * pitem);*/


      virtual void draw_item(::draw2d::graphics * pgraphics,int x,int y,item * pitem);
      virtual void draw_framing(::draw2d::graphics * pgraphics);

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

      virtual bool on_simple_command(e_simple_command ecommand,lparam lparam,LRESULT & lresult);


      virtual bool keyboard_focus_OnSetFocus() override;


      virtual bool get_font(::draw2d::font_sp & spfont);

      virtual count _001GetItemCount();

      virtual count _001GetColumnCount();

      bool get_color(COLORREF & cr,::user::e_color ecolor);


      void set_data(general_data * pdata);


   };


} // namespace verigrid













