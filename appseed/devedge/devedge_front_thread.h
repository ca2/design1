﻿#pragma once


namespace devedge
{


   class CLASS_DECL_DEVEDGE front_thread :
      public ::thread
   {
   public:


      HANDLE                  m_hChildThreadId;
      PROCESS_INFORMATION     m_pi;

      ::event                 m_evInitialized;
      bool                    m_bInitialized;
      front_thread *          m_pnext;


      front_thread(::aura::application * papp);
      virtual ~front_thread();


      void install_message_routing(::message::sender * pinterface);

      virtual bool init_thread() override;


      DECL_GEN_SIGNAL(OnApp);


   };


} // namespace devedge





