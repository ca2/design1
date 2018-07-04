#pragma once


namespace composite
{


   class CLASS_DECL_APP_CORE_TEXTFORMAT view :
      virtual public ::user::impact
   {
   public:


      enum e_timer
      {

         timer_drag = 1000,

      };

      class CLASS_DECL_APP_CORE_TEXTFORMAT pic :
         virtual public ::user::pic
      {
      public:


         ::draw2d::dib_sp     m_dib;
         pic(::aura::application * papp);


         virtual bool is_valid() override;
         virtual ::sized get_size() override;

         virtual void draw(::draw2d::graphics * pgraphics) override;

      };

      class CLASS_DECL_APP_CORE_TEXTFORMAT pic_tool :
         virtual public object
      {
      public:

         enum e_tool
         {
            tool_none,
            tool_rotate,
            tool_crop,
            tool_close,
            tool_stack_up,
            tool_stack_down,
            tool_special_effect,
            tool_resize,
            tool_zoom_out,
            tool_move,
            tool_zoom_in,
            tool_apply,
            tool_count,

         };

         class CLASS_DECL_APP_CORE_TEXTFORMAT tool
         {
         public:

            e_tool               m_etool;
            ::draw2d::dib_sp     m_dibDisable;
            ::draw2d::dib_sp     m_dib;
            bool                 m_bEnable;
            pointd               m_ptAlign;
            bool                 m_bDrag;
            ::visual::e_cursor   m_ecursor;

            tool();

         };

         e_tool               m_etoolMode;
         view *               m_pview;
         ::draw2d::pen_sp     m_penBorder;
         // Steady/Stable Center for rotation
         // because rotation can make it loose precision
         point                m_ptCenter;
         pointd               m_ptResizeOrigin;

         map < e_tool, e_tool, tool > m_map;

         bool get_tool_rect(LPRECTD lprect, e_tool etool);
         bool hit_test(e_tool & etool, pointd pt);

         void draw(::draw2d::graphics * pgraphics);
         void draw_tool(::draw2d::graphics * pgraphics, e_tool etool);

      };

      enum e_layout
      {
         layout_none,
         layout_scan, // intersect in all lines
         layout_no_last_row_intersect, // intersect except last row
         layout_get_intersect_hint,
      };


      bool                    m_bEnablePastePicture;

      pic_tool::e_tool        m_etoolDown;


      spa(::user::pic)        m_pica;
      sp(::user::pic)         m_picCurrent;
      sp(pic_tool)            m_pictool;
      ::draw2d::dib_sp        m_dibBackground;
      ::draw2d::dib_sp        m_dibAlphaMask;
      ::draw2d::dib_sp        m_dibAlphaMaskFit;
      //string                  m_strServer;
      //::visual::dib_sp        m_dibAi1;
      //::visual::dib_sp        m_dibAi2;

      //string                  m_strImage;
      //::draw2d::dib_sp        m_dibColor;

      //bool                    m_bOkPending;


      bool                    m_bHelloLayoutOn001Layout;
      bool                    m_b001LayoutIgnoreEmpty;
      double                  m_dAspect;


      sized                   m_sizePage;
      sized                   m_sizePagePrev;
      rectd                   m_rectMarginDrawing;
      rectd                   m_rectMaxMarginDrawing;
      rectd                   m_rectMargin;
      rectd                   m_rectMarginPrev;
      rectd                   m_rectClient;

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

   };


} // namespace composite


