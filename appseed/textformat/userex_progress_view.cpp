#include "framework.h"

#pragma once

progress::progress(::aura::application * papp, const char * pszTitle) :
   object(papp)
{

   defer_create_mutex();
   m_strTitle = pszTitle;
   m_iStep = 0;
   m_iStepCount = 0;

}


progress::~progress()
{

}


void progress::on_set_scalar(e_scalar escalar, double d, int iFlags)
{

}


void progress::get_scalar_minimum(e_scalar escalar, double & d)
{

   d = 0.0;

}


void progress::get_scalar(e_scalar escalar, double & d)
{

   d = (double)m_iStep / (double)m_iStepCount;

}


void progress::get_scalar_maximum(e_scalar escalar, double & d)
{

   d = 1.0;

}


void progress::redraw()
{


}

void progress::format_status(const char *pszFormat)
{

   string strStatus(pszFormat);

   strStatus.replace("%1", ::str::from(m_iStep));
   strStatus.replace("%2", ::str::from(m_iStepCount));

   m_strStatus = strStatus;

   redraw();

}

void progress::step()
{

   ASSERT(m_iStep + 1 <= m_iStepCount);

   if (m_iStep + 1 > m_iStepCount)
   {

      return;

   }

   m_iStep++;

   redraw();

}

namespace userex
{


   progress::progress(::aura::application * papp, const char * pszTitle, int iStepCount) :
      object(papp),
      ::progress(papp, pszTitle)
   {

      m_iStepCount = iStepCount;
      m_pdoc = NULL;
      m_pview = NULL;

   }


   progress::~progress()
   {

   }


   void progress::set_progress_title(const char * pszTitle)
   {

      m_pview->GetParentFrame()->set_window_text(pszTitle);

   }


   i64 progress::dec_ref()
   {

      i64 i = ::progress::dec_ref();

      if (i == 1 && m_pthread.is_set())
      {

         m_pthread->post_quit();

      }

      return i;

   }


   void progress::create_progress(::user::interaction * puiParent)
   {

      if (m_pdoc == NULL)
      {

         Application.m_ptemplateProgress2->m_bQueueDocumentOpening = false;

         m_pdoc = Application.m_ptemplateProgress2->open_document_file(get_app(), var::type_null, false, puiParent);

         m_pview = m_pdoc->get_typed_view<::userex::progress_view>();

      }

      m_pview->m_progress.m_pscalar = new double_scalar(this, scalar_progress);

      m_pview->m_pprogress = this;

   }


   void progress::close_progress()
   {

      synch_lock sl(m_pmutex);

      auto pdoc = m_pdoc;

      m_pdoc = NULL;

      pdoc->close_document();

   }


   void progress::redraw()
   {

      if (m_pview == NULL)
      {

         return;

      }

      m_pview->set_need_redraw();


   }


   void progress::defer_show(::user::interaction * puiParent)
   {

      manual_reset_event ev(get_app());

      ev.ResetEvent();

      m_pthread = fork([this, &ev, puiParent]()
      {

         add_ref();

         create_progress(puiParent);

         ev.SetEvent();

         Sleep(150);

         if (m_pdoc != NULL)
         {

            try
            {

               rect r;

               System.get_main_monitor(r);

               r.deflate(r.width() / 6, r.height() / 3, r.width() / 6, r.height() / 2);

               m_pview->GetParentFrame()->SetWindowPos(ZORDER_TOP, r, SWP_SHOWWINDOW | SWP_NOACTIVATE);


            }
            catch (...)
            {


            }

            m_pthread->m_bSimpleMessageLoop = false;

            m_pthread->::thread::run();

         }

         m_pthread->m_objectptraDependent.remove(this);

         close_progress();

         release();

         output_debug_string("finished");

      });

      ev.wait(seconds(10));

   }


   progress_view::progress_view(::aura::application * papp) :
      object(papp),
      m_progress(papp)
   {

   }


   progress_view::~progress_view()
   {

   }


   void progress_view::assert_valid() const
   {

      ::user::impact::assert_valid();

   }


   void  progress_view::dump(dump_context & dumpcontext) const
   {

      ::user::impact::dump(dumpcontext);

   }


   void  progress_view::install_message_routing(::message::sender * psender)
   {

      ::user::impact::install_message_routing(psender);

      IGUI_MSG_LINK(WM_CREATE, psender, this, &progress_view::_001OnCreate);


   }


   void progress_view::on_update(::user::impact * pSender, LPARAM lHint, object* pHint)
   {

   }


   void progress_view::_001OnCreate(::message::message * pmessage)
   {

      SCAST_PTR(::message::create, pcreate, pmessage);
      pmessage->previous();

      if (!m_progress.create_window(::null_rect(), this, "progress"))
      {


         pcreate->set_lresult(-1);

         pcreate->m_bRet = true;

         return;

      }


   }


   void progress_view::_001OnDestroy(::message::message * pmessage)
   {

      pmessage->previous();

   }


   void progress_view::_001OnDraw(::draw2d::graphics * pgraphics)
   {

      if (m_pprogress == NULL)
      {

         return;

      }

      pgraphics->set_text_color(ARGB(255, 80, 80, 80));

      pgraphics->draw_text(m_pprogress->m_strStatus, m_rectStatus, DT_CENTER | DT_VCENTER);

   }


   void progress_view::on_layout()
   {

      rect rectClient;

      GetClientRect(rectClient);

      if(rectClient.area() <= 0)
      {

         return;

      }

      int cxBorder = rectClient.width() / 16;
      int h = rectClient.height() / 4;

      rect rectIndicator(rectClient);

      rectIndicator.deflate(cxBorder, h, cxBorder, h * 2);

      m_rectStatus = rectClient;

      m_rectStatus.deflate(cxBorder, h * 2, cxBorder, h);

      m_progress.SetWindowPos(ZORDER_TOP, rectIndicator, SWP_SHOWWINDOW);

   }


} // namespace tranquillum


