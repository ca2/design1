﻿#pragma once

namespace netnodeds
{

   class CLASS_DECL_DESIGN_NETNODEDS main_frame : public simple_frame_window
   {
   public:




      sp(image_list)                m_pimagelist;


      main_frame(::aura::application * papp);
      virtual ~main_frame();

      virtual void install_message_routing(::message::sender * pinterface);

      virtual bool pre_create_window(::user::create_struct& cs);
      void ShowControlBars(bool bShow);

      virtual bool is_application_main_window();


      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;


      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnClose);
      void _001OnTimer(::timer * ptimer);
   };

} // namespace netnodeds