#pragma once


namespace composite
{


   class CLASS_DECL_DESIGN_TEXTFORMAT view :
      virtual public ::user::impact,
      virtual public ::serialize
   {
   public:


      enum e_timer
      {

         timer_drag = 1000,

      };

      enum e_layout
      {
         layout_none,
         layout_scan, // intersect in all lines
         layout_no_last_row_intersect, // intersect except last row
         layout_get_intersect_hint,
      };


      bool                    m_bEnablePastePicture;

      //string                  m_strServer;
      //::visual::dib_sp        m_dibAi1;
      //::visual::dib_sp        m_dibAi2;

      //string                  m_strImage;
      //::draw2d::dib_sp        m_dibColor;

      //bool                    m_bOkPending;


      bool                    m_bHelloLayoutOn001Layout;
      bool                    m_b001LayoutIgnoreEmpty;
      double                  m_dAspect;


      sp(data)                m_pdata;

      ::user::e_element       m_eelementDrag;

      index                   m_iTopic;
      rectd                   m_rectTopic;
      rectd                   m_rectTopicDrawing;
      //::userex::font_format_tool       m_fonttool;
      //spa(::user::rich_text::edit)     m_edita;
      //sp(::user::rich_text::edit)     m_peditDrag;
      pointd                   m_ptEditCursorOffset;
      bool                    m_bAutoAdjustPicSize;
      ::size                  m_sizeMaxPicAdjust;
      double                  m_dStartAngle;


      view(::aura::application * papp);
      virtual ~view();

      virtual void load();
      virtual void save();

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

      void on_pic_update();

      virtual void do_edit_paste();

      virtual void _001OnDraw(::draw2d::graphics * pgraphics) override;

      virtual void install_message_routing(::message::sender * psender) override;

      virtual void on_update(::user::impact * pSender, LPARAM lHint, object* pHint) override;

      virtual bool keyboard_focus_is_focusable() override;
      virtual void on_layout() override;

      DECL_GEN_SIGNAL(_001OnLayout);
      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnDestroy);
      DECL_GEN_SIGNAL(_001OnMouseMove);
      DECL_GEN_SIGNAL(_001OnLButtonDown);
      DECL_GEN_SIGNAL(_001OnLButtonUp);
      DECL_GEN_SIGNAL(_001OnKeyDown);
      DECL_GEN_SIGNAL(_001OnEditPaste);
      DECL_GEN_SIGNAL(_001OnUpdateEditPaste);


      virtual pointd pick_random_placement(double dRate);

      virtual void _001OnTimer(::timer * ptimer) override;

      virtual void defer_check_on_draw_layout();

      virtual void on_draw_image_layer(::draw2d::graphics * pgraphics);

      virtual void set_background(::file::path path);
      virtual ::user::pic * place_pic(pointd pt, ::file::path path);
      virtual ::user::pic * place_pic(pointd pt, ::draw2d::dib * pdib);
      virtual void place_pic(pointd pt, ::user::pic * ppic);

      virtual void pica_to_margin();

      virtual void _001OnDrawPic(::draw2d::graphics * pgraphics);


      virtual index hit_test(pointd point, ::user::e_element & eelement);

      virtual void stream_link(string strLink, serializable & serializable);

      virtual ::user::rich_text::edit * create_rich_text_edit(point pt = null_point());

      virtual void on_control_event(::user::control_event * pevent);


   };


} // namespace composite


