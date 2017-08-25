#include "framework.h"


namespace netnodeds
{


   front_thread::front_thread(::aura::application * papp) :
      ::object(papp),
      thread(papp),
      m_evInitialized(papp)
   {

      m_evInitialized.ResetEvent();

      m_bInitialized = false;

      //m_plistensocket = NULL;

   }


   front_thread::~front_thread()
   {

   }


   void front_thread::install_message_routing(::message::sender * pinterface)
   {
      IGUI_MSG_LINK(WM_APP, pinterface, this, &front_thread::OnApp);
   }


   bool front_thread::initialize_thread()
   {

      int32_t iCount = 2;
      int32_t i;
      for(int32_t i = 0; i < iCount; i++)
      {
         //   netnodedsSocketThread * pthread = __begin_thread < netnodedsSocketThread >(get_app());
         //      m_ptrathread.add(pthread);
      }
      int32_t iCount2 = iCount - 1;
      for(i = 0; i < iCount2; i++)
      {
         //   m_ptrathread[i]->m_pnext = m_ptrathread[i + 1];
      }
      //   m_ptrathread[i]->m_pnext = m_ptrathread[0];

      //   m_pthreadCurrent = m_ptrathread[0];

      post_message(WM_APP);


      /*   STARTUPINFO startupinfo;
      memset(&startupinfo, 0, sizeof(startupinfo));
      if(!::CreateProcess(NULL, "netnoderewrite.exe", 
      NULL,
      NULL,
      TRUE,
      0, 
      NULL,
      ".",
      &startupinfo,
      &m_pi))
      {
      return FALSE;
      }


      WaitForInputIdle(m_pi.hProcess, INFINITE);


      //   m_hChildThreadId = ::OpenThread(THREAD_ALL_ACCESS, TRUE, m_pi.dwThreadId);

      ::post_thread_message(m_pi.dwThreadId, WM_APP, 0, m_nThreadID);

      post_thread_message(WM_APP, 0, 0);*/


      //post_thread_message(WM_APP, 0, 0);


      /*   m_plistensocket = new netnodedsListenSocket(this);
      //Sleep(15000);
      if(!m_plistensocket->create(80, SOCK_STREAM))
      {
      uint32_t dw = ::GetLastError();
      TRACE("error %u", dw);
      return FALSE;
      }
      if(!m_plistensocket->Listen())
      {
      uint32_t dw = ::GetLastError();
      TRACE("error %u", dw);
      return FALSE;
      }*/
      return true;
   }


   void front_thread::OnApp(::message::message * pobj)
   {
      SCAST_PTR(::message::base, pbase, pobj);
      if(pbase->m_wparam == 0)
      {
         /*   m_plistensocket = new netnodedsListenSocket(this);
         //Sleep(15000);
         if(!m_plistensocket->create(10011, SOCK_STREAM))
         {
         uint32_t dw = ::GetLastError();
         TRACE("error %u", dw);
         System.post_thread_message(WM_APP, 3, 0);
         return;
         }
         if(!m_plistensocket->Listen())
         {
         uint32_t dw = ::GetLastError();
         TRACE("error %u", dw);
         System.post_thread_message(WM_APP, 3, 1);
         return;
         }*/
      }
      else if(pbase->m_wparam == 1)
      {
         //   netnodedsListenSocket * plistensocket = (netnodedsListenSocket *) pbase->m_lparam;
         //      netnodedsSocket * psocket = new netnodedsSocket(plistensocket);
         //single_lock sl(&m_csNetNodeSocket);
         //   plistensocket->Accept(*psocket);
      }
      if(pbase->m_wparam == 0)
      {
         m_bInitialized = true;
         m_evInitialized.SetEvent();
      }
      else if(pbase->m_wparam == 1)
      {

         throw not_implemented(get_app());

      }
      else if(pbase->m_wparam == 2)
      {
         m_pnext->post_message(WM_APP, 1);
      }
   }



} // namespace netnodeds





void CLASS_DECL_DESIGN_NETNODEDS KickDevEdgeFront(::aura::application * papp)
{
   __begin_thread < ::netnodeds::front_thread > (papp);   
}




