#pragma once


namespace composite
{


   class view;

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


   class CLASS_DECL_DESIGN_TEXTFORMAT pic :
      virtual public ::user::pic
   {
   public:


      view * m_pview;
      ::draw2d::dib_sp     m_dib;
      pic(::aura::application * papp);


      virtual bool is_valid() override;
      virtual ::sized get_size() override;

      virtual void draw_impl(::draw2d::graphics * pgraphics, LPCRECT lpcrect) override;

      virtual void io(stream & stream) override;

   };

   class CLASS_DECL_DESIGN_TEXTFORMAT pic_tool :
      virtual public object
   {
   public:

      class CLASS_DECL_DESIGN_TEXTFORMAT tool
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


      pic_tool(::aura::application * papp);
      virtual ~pic_tool();


      bool get_tool_rect(LPRECTD lprect, e_tool etool);
      bool hit_test(e_tool & etool, pointd pt);

      void draw(::draw2d::graphics * pgraphics);
      void draw_tool(::draw2d::graphics * pgraphics, e_tool etool);

   };


   class CLASS_DECL_DESIGN_TEXTFORMAT data :
      public ::data::data
   {
   public:


      data(::aura::application * papp);
      virtual ~data();



      e_tool        m_etoolDown;


      spa(::user::pic)        m_pica;
      sp(::user::pic)         m_picCurrent;
      sp(pic_tool)            m_pictool;
      ::draw2d::dib_sp        m_dibBackground;
      ::draw2d::dib_sp        m_dibAlphaMask;
      ::draw2d::dib_sp        m_dibAlphaMaskFit;
      sized                   m_sizePage;
      sized                   m_sizePagePrev;
      rectd                   m_rectMarginDrawing;
      rectd                   m_rectMaxMarginDrawing;
      rectd                   m_rectMargin;
      rectd                   m_rectMarginPrev;
      rectd                   m_rectClient;

      virtual void io(stream & serialize) override;


   };


} // namepsace composite