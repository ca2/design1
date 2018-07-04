#include "framework.h"


namespace userex
{


   image_list_view::image_list_view(::aura::application * papp) :
      object(papp),
      ::user::image_list_view(papp),
      m_listing(papp)
   {


   }


   image_list_view::~image_list_view()
   {
   }


   stringa image_list_view::get_ls_pattern_stra() const
   {

      stringa stra;

      for (auto & strPattern : m_straPattern)
      {

         stringa straPattern;

         straPattern.explode(";", strPattern);

         straPattern.trim();

         stra.add_unique(straPattern);

      }

      return stra;

   }


   bool image_list_view::update_data(bool bSaveAndValidate)
   {

      if (bSaveAndValidate)
      {

         return true;

      }
      else
      {

         synch_lock sl(m_pmutex);

         m_dibaThumb.remove_all();

         m_diba.remove_all();

         if (m_pathFolder.has_char())
         {

            m_listing.remove_all();

            m_listing.ls_pattern_file(m_pathFolder, get_ls_pattern_stra());

         }

         fork([this]()
         {

            synch_lock sl(m_pmutex);

            for (index i = 0; i < m_listing.get_count();)
            {

               sl.unlock();

               ::visual::dib_sp dib(allocer());

               if (dib.load_from_file(m_listing[i], false))
               {

                  i++;

                  sl.lock();

                  if (dib->m_size.cx > 256)
                  {

                     ::draw2d::dib_sp dibSmall(allocer());

                     dibSmall->create(256, 256 * dib->m_size.cy / dib->m_size.cx);

                     dibSmall->g()->draw(::rect(dibSmall->m_size), dib->g(), ::rect(dib->m_size));

                     dib = dibSmall;

                  }

                  m_diba.add(dib);

                  set_need_layout();

               }
               else
               {

                  sl.lock();

                  TRACE("Could not dib.load_from_file.file=" + m_listing[i]);

                  m_listing.remove_at(i);

               }

            }

         });

         return ::user::image_list::update_data(false);

      }

   }

   void image_list_view::assert_valid() const
   {
      ::user::image_list_view::assert_valid();
   }

   void image_list_view::dump(dump_context & dumpcontext) const
   {
      ::user::image_list_view::dump(dumpcontext);
   }

   void image_list_view::install_message_routing(::message::sender * psender)
   {

      ::user::image_list_view::install_message_routing(psender);

      IGUI_MSG_LINK(WM_CREATE, psender, this, &image_list_view::_001OnCreate);
      IGUI_MSG_LINK(WM_DESTROY, psender, this, &image_list_view::_001OnDestroy);
//      IGUI_MSG_LINK(WM_LBUTTONDOWN, psender, this, &image_list_view::_001OnLButtonDown);
      //    IGUI_MSG_LINK(WM_MOUSEMOVE, psender, this, &image_list_view::_001OnMouseMove);
      //  IGUI_MSG_LINK(WM_MOUSELEAVE, psender, this, &image_list_view::_001OnMouseLeave);

   }


   //void image_list_view::_001OnLButtonDown(::message::message * pobj)
   //{

   //   SCAST_PTR(::message::mouse, pmouse, pobj);

   //   point pt = pmouse->m_pt;

   //   ScreenToClient(&pt);

   //   int iMenuSel;

   //   int iCommandSel;

   //   int iHover = hit_test(pt, iMenuSel, iCommandSel);

   //   if (iCommandSel >= 0)
   //   {

   //      m_iMenuSel = iMenuSel;

   //      m_iCommandSel = iCommandSel;

   //   }

   //}


   //void image_list_view::_001OnMouseMove(::message::message * pobj)
   //{

   //   SCAST_PTR(::message::mouse, pmouse, pobj);

   //   point pt = pmouse->m_pt;

   //   ScreenToClient(&pt);

   //   int iMenuHover;

   //   int iCommandHover;

   //   int iHover = hit_test(pt, iMenuHover, iCommandHover);

   //   if (iHover >= 0 && m_iHover < 0)
   //   {

   //      SetCapture();

   //   }

   //   m_iMenuHover = iMenuHover;

   //   m_iCommandHover = iCommandHover;

   //   m_iHover = iHover;

   //}


   //void image_list_view::_001OnMouseLeave(::message::message * pobj)
   //{

   //   ReleaseCapture();

   //   m_iMenuHover = -1;

   //   m_iCommandHover = -1;

   //}


   void image_list_view::_001OnCreate(::message::message * pobj)
   {

      SCAST_PTR(::message::create, pcreate, pobj);

      pcreate->previous();

      if (pcreate->m_bRet)
         return;

      string strId = get_document()->m_pimpactsystem->m_strMatter;

      string strText;

      data_get("cur_text", strText);

   }


   void image_list_view::_001OnDestroy(::message::message * pobj)
   {

   }


   void image_list_view::on_update(::user::impact * pSender, LPARAM lHint, object* phint)
   {

      ::user::image_list_view::on_update(pSender, lHint, phint);

      ::user::view_update_hint * puh = dynamic_cast < ::user::view_update_hint *> (phint);

      if (puh != NULL)
      {

         if (puh->m_ehint == ::user::view_update_hint::hint_after_change_text)
         {

            auto * peditview = _001TypedWindow < ::userex::top_edit_view >();

            if (peditview != NULL && puh->m_pui == peditview)
            {

               string strText;

               peditview->_001GetText(strText);

            }

         }

      }

   }





   void image_list_view::on_layout()
   {


      ::user::image_list_view::on_layout();

   }


   bool image_list_view::_001GetItemText(string & str, index iItem)
   {

      str = m_listing[iItem].name();

      string strMap;

      string strLower = str;

      strLower.make_lower();

      if (m_mapName.Lookup(strLower, strMap))
      {

         str = strMap;

      }

      return true;

   }



} // namespace userex


