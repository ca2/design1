#pragma once


namespace biteditor
{


   class CLASS_DECL_CA2_BITEDITOR frame : public simple_frame_window
   {
   public:


      
      
      image_list                 m_imagelist;


      frame(::aura::application * papp);
      virtual ~frame();

      virtual void install_message_routing(::message::sender * pinterface);
      virtual bool pre_create_window(::user::create_struct& cs);
      void ShowControlBars(bool bShow);
 

      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;


      //   simple_menu_bar     m_menubar;
      //   SimpleDialogBar   m_dialogbar;
      //xxx   SimpleReBar       m_wndReBar;
      //   simple_status_bar   m_statusbar;
      //   simple_toolbar     m_toolbar;
      //   simple_toolbar     m_toolbarView;

      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnClose);
      void OnTimer(uint32_t nIDEvent);


   };



} // namespace biteditor



