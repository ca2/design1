#pragma once


namespace tarsila
{


   class CLASS_DECL_APP_CORE_TARSILA view :
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


      view(::aura::application * papp);
      virtual ~view();



      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;


      virtual void install_message_routing(::message::sender * pinterface);

      virtual void _001OnDraw(::draw2d::graphics * pgraphics);

      virtual bool pre_create_window(::user::create_struct& cs);
      virtual void on_update(::user::impact * pSender, LPARAM lHint, ::object* pHint);

      virtual void _001OnTabClick(int32_t iTab);



      virtual void on_layout();

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


} // namespace tarsila





