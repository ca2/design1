#pragma once


namespace veritile
{


   class CLASS_DECL_APP_CORE_VERITILE view :
      virtual public ::user::impact
   {
   public:



      enum e_state
      {

         state_initial,
         state_polygon_tool_initial,
         state_polygon_tool_dots,

      };


      e_state                                         m_estate;
      //visual::dib_sp                                  m_spdib;
      string                                          m_strServer;
      bool                                            m_bMouseDown;

      general_data                             m_


      view(::aura::application * papp);
      virtual ~view();


#ifdef DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
#endif

      virtual void install_message_handling(::message::dispatch * pinterface);

      virtual void _001OnDraw(::draw2d::graphics * pdc);

      virtual bool pre_create_window(::user::create_struct& cs);
      virtual void on_update(::user::impact * pSender, LPARAM lHint, ::object* pHint);

      virtual void _001OnTabClick(int32_t iTab);


      virtual bool keyboard_focus_is_focusable();
      virtual bool keyboard_focus_OnSetFocus();

      virtual void layout();

      virtual void _001OnInitialUpdate();
      DECL_GEN_SIGNAL(_001OnDestroy);
      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnContextMenu);
      DECL_GEN_SIGNAL(_001OnSetCursor);
      DECL_GEN_SIGNAL(_001OnEraseBkgnd);
      void _001OnTimer(::timer * ptimer);;
      DECL_GEN_SIGNAL(_001OnMouseMove);
      DECL_GEN_SIGNAL(_001OnLButtonDown);
      DECL_GEN_SIGNAL(_001OnLButtonUp);
      DECL_GEN_SIGNAL(_001OnLButtonDblClk);

      DECL_GEN_SIGNAL(_001OnSelectionTool);
      DECL_GEN_SIGNAL(_001OnUpdateSelectionTool);
      DECL_GEN_SIGNAL(_001OnPolygonTool);
      DECL_GEN_SIGNAL(_001OnUpdatePolygonTool);



   };


} // namespace veritile





