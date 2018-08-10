#pragma once


namespace user
{


   class CLASS_DECL_DESIGN_TEXTFORMAT pic :
      virtual public object
   {
   public:


      class CLASS_DECL_DESIGN_TEXTFORMAT pic_impl :
         virtual public object
      {
      public:

         rectd                   m_rect;
         rectd                   m_rectDrawing;
         rectd                   m_rectCursor;
         bool                    m_bDrag;
         double                  m_dRotate;
         ::draw2d::region_sp     m_region;
         rectd                   m_rectBounding;
         pointd_array            m_pta;
         pointd_array            m_ptaDrawing;
         pointd_array            m_ptaCursor;
         double                  m_dZoom;
         pointd                  m_ptDrag;

         bool                    m_bOutline;
         int                     m_iOutlineWidth;
         ::color::hls            m_hlsOutline;

         bool                    m_bGlowDropShadow;
         int                     m_iGlowDropShadowOffset;
         int                     m_iGlowDropShadowBlur;
         ::color::hls            m_hlsGlowDropShadow;

         int                     m_iBlur;
         bool                    m_bGrayscale;
         bool                    m_bInvert;
         int                     m_iOpacity; // 0 - 100
         int                     m_iSaturation; // 0 - 200


         pic_impl();

         virtual void io(stream & stream) override;

      };


      pic_impl *            m_ppic;


      pic(::aura::application * papp);
      virtual ~pic();

      virtual bool enable_pic(bool bEnable = true);
      virtual bool is_pic_enabled() const;


      virtual int hit_test_cursor(pointd pt);
      virtual int hit_test(pointd pt) const;
      virtual bool intersects_drawing(LPCRECTD lpcrect) const;
      virtual bool intersects(LPCRECTD lpcrect) const;
      virtual ::draw2d::region_sp get_region() const;

      virtual void update_drawing_rect(::sized sizePage, ::sized sizeClient);
      virtual void update_region();
      virtual void update_placement();

      virtual void _transform_point(pointd & pt) const;
      virtual void _transform_point_drawing(pointd & pt) const;
      virtual pointd _transform(const pointd & pt) const;
      virtual pointd _transform_drawing(const pointd & pt) const;
      virtual void _rtransform_point(pointd & pt) const;
      virtual void _rtransform_point_drawing(pointd & pt) const;
      virtual pointd _rtransform(const pointd & pt) const;
      virtual pointd _rtransform_drawing(const pointd & pt) const;

      virtual void drag_transform_point(pointd & pt) const;
      virtual void drag_transform_point_drawing(pointd & pt) const;
      virtual pointd drag_transform(const pointd & pt) const;
      virtual pointd drag_transform_drawing(const pointd & pt) const;
      virtual void drag_rtransform_point(pointd & pt) const;
      virtual void drag_rtransform_point_drawing(pointd & pt) const;
      virtual pointd drag_rtransform(const pointd & pt) const;
      virtual pointd drag_rtransform_drawing(const pointd & pt) const;


      virtual void reset_cursor_rect();
      virtual bool is_dragging();
      virtual bool is_valid();
      virtual ::sized get_size();

      virtual ::draw2d::dib * defer_draw_drop_shadow_phase1(rect & rectDropShadow, ::visual::fastblur & dibDropShadow, ::draw2d::dib * pdib);
      virtual void defer_draw_drop_shadow_phase2(::draw2d::graphics * pgraphics, const rect & rectDropShadow, ::visual::fastblur & dibDropShadow);

      virtual bool set_text_editable(bool bEditable = true);

      virtual bool is_text_editable();

      virtual bool is_text_editor();


      virtual void draw(::draw2d::graphics * pgraphics);
      virtual void draw_impl(::draw2d::graphics * pgraphics, LPCRECT lpcrect);


      virtual void move_to(pointd pt, ::sized sizePage, ::sized sizeClient, LPCRECTD lpcrectMargin);

      virtual void io(stream & stream) override;


   };


} // namespace user



