#pragma once


namespace syllomatter
{


   class CLASS_DECL_CA2_SYLLOMATTER frame : 
      public form_child_frame
   {
   public:

      
      
      image_list                 m_imagelist;
      bool                       m_bTimerOn;
      bool                       m_bHoverMouse;
      uint32_t                      m_dwLastHover;

      frame(::aura::application * papp);
      virtual ~frame();

      virtual bool pre_create_window(::user::create_struct& cs);
      void ShowControlBars(bool bShow);
    
#ifdef DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
#endif




      void OnHoverAction();


      //   simple_menu_bar     m_menubar;
      //   SimpleDialogBar   m_dialogbar;
      //xxx   SimpleReBar       m_wndReBar;
      //   simple_status_bar   m_statusbar;
      //   simple_toolbar     m_toolbar;
      //   simple_toolbar     m_toolbarView;


      DECL_GEN_SIGNAL(_001OnCreate);
      void OnShowWindow(bool bShow, uint32_t nStatus) ;
   };


} // namespace syllomatter



