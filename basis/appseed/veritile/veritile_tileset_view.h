#pragma once


namespace veritile
{


   class CLASS_DECL_APP_CORE_VERITILE tileset_view:
      virtual public ::user::show < ::user::scroll < ::user::control > >
   {
   public:


      typedef ::user::show < ::user::scroll < ::user::control > > BASE_VIEW;

      sp(tileset)                      m_ptileset;
         
//      point_array                      m_pta;

      bool                             m_bMouseDown;


      tileset_view(::aura::application * papp);
      virtual ~tileset_view();


      virtual bool initialize(tileset * ptileset);


#ifdef DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
#endif

      virtual void install_message_handling(::message::dispatch * pinterface);

      virtual void _001OnDraw(::draw2d::graphics * pdc);
      virtual void _001OnDrawSel(::draw2d::graphics * pdc, const point_array & ptaSel);

      virtual bool pre_create_window(::user::create_struct& cs);
      virtual void on_update(::user::impact * pSender,LPARAM lHint,::object* pHint);

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


      virtual bool hit_test(point & ptTile,point pt);

      virtual ::size get_total_size();


   };


} // namespace veritile





