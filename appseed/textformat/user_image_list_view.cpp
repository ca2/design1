#include "framework.h"


namespace user
{


   image_list::image_list()
   {

      m_sizeImage.set(0, 0);

      m_iTextHeight = 30;
      m_bMultiSel = true;
      m_size.cx = 128;
      m_size.cy = 128;

      m_bNoName = false;
      m_iPad = 10;
      m_ealign = align_top_left;


      m_iHitLast = -1;
      m_iHover = -1;

      m_scrolldataVert.m_bScrollEnable = true;

   }


   image_list::~image_list()
   {

   }


   bool image_list::update_data(bool bSaveAndValidate)
   {

      if (bSaveAndValidate)
      {

      }
      else
      {

         set_need_layout();

         set_need_redraw();

      }

      return true;

   }


   void image_list::assert_valid() const
   {

      ::user::box::assert_valid();

   }


   void image_list::dump(dump_context & dumpcontext) const
   {

      ::user::box::dump(dumpcontext);

   }

   ::draw2d::dib * image_list::get_current_dib()
   {

      synch_lock sl(m_pmutex);

      if (m_iaSel.get_count() != 1)
      {

         return NULL;

      }

      return m_diba[m_iaSel[0]];

   }

   string image_list::get_current_dib_link()
   {

      if (get_current_dib() == NULL)
      {

         return "";

      }

      return get_current_dib()->oprop("read_only_link");

   }


   void image_list::install_message_routing(::message::sender * psender)
   {

      ::user::box::install_message_routing(psender);

      IGUI_MSG_LINK(WM_CREATE, psender, this, &image_list::_001OnCreate);
      IGUI_MSG_LINK(WM_DESTROY, psender, this, &image_list::_001OnDestroy);
      IGUI_MSG_LINK(WM_LBUTTONDOWN, psender, this, &image_list::_001OnLButtonDown);
      IGUI_MSG_LINK(WM_LBUTTONUP, psender, this, &image_list::_001OnLButtonUp);
      IGUI_MSG_LINK(WM_MOUSEMOVE, psender, this, &image_list::_001OnMouseMove);
      IGUI_MSG_LINK(WM_MOUSELEAVE, psender, this, &image_list::_001OnMouseLeave);

   }


   void image_list::_001OnLButtonDown(::message::message * pobj)
   {

      SCAST_PTR(::message::mouse, pmouse, pobj);

      point pt = pmouse->m_pt;

      ScreenToClient(&pt);

      pt += m_ptScrollPassword1;

      e_element eelement;

      int iHit = hit_test(pt, eelement);

      m_iHitLButtonDown = iHit;

      if (iHit >= 0)
      {

         SetCapture();

         pmouse->m_bRet = true;

      }

   }


   void image_list::_001OnLButtonUp(::message::message * pobj)
   {

      SCAST_PTR(::message::mouse, pmouse, pobj);

      point pt = pmouse->m_pt;

      ScreenToClient(&pt);

      pt += m_ptScrollPassword1;

      ReleaseCapture();

      e_element eelement;

      int iHit = hit_test(pt, eelement);

      index_array iaSel = m_iaSel;

      if (iHit >= 0 && iHit == m_iHitLButtonDown)
      {

         if (!(pmouse->m_nFlags & MK_CONTROL) || !m_bMultiSel)
         {

            iaSel.remove_all();

         }


         if (pmouse->m_nFlags & MK_SHIFT && m_bMultiSel)
         {

            if (m_iHitLast >= 0)
            {

               for (index i = m_iHitLast; i < iHit; i++)
               {

                  iaSel.add_unique(i);

               }

            }

         }
         else
         {

            iaSel.add_unique(iHit);

         }

         _001SetSelection(iaSel, ::action::source_user);

         m_iHitLast = iHit;

      }


   }


   void image_list::_001OnMouseMove(::message::message * pobj)
   {

      SCAST_PTR(::message::mouse, pmouse, pobj);

      point pt = pmouse->m_pt;

      ScreenToClient(&pt);

      pt += m_ptScrollPassword1;

      e_element eelement;

      int iHover = hit_test(pt, eelement);

      if (iHover >= 0 && m_iHover < m_diba.get_count())
      {

         track_mouse_leave();

      }

      if (iHover != m_iHover)
      {

         m_iHover = iHover;

         set_need_redraw();

      }

   }


   void image_list::_001OnMouseLeave(::message::message * pobj)
   {

      ReleaseCapture();

      m_iHover = -1;

      set_need_redraw();

   }


   void image_list::_001OnCreate(::message::message * pobj)
   {

      SCAST_PTR(::message::create, pcreate, pobj);

      pcreate->previous();

      if (pcreate->m_bRet)
         return;


   }


   void image_list::_001OnDestroy(::message::message * pobj)
   {

   }

   bool image_list::get_element_rect(LPRECT lprect, index i, e_element eelement)
   {

      if (eelement == ::user::element_icon)
      {

         if (!get_item_rect(lprect, i))
         {

            return false;

         }

         if (!m_bNoName)
         {

            lprect->bottom -= m_iTextHeight;

         }

         return true;

      }
      else if (eelement == ::user::element_text)
      {

         if (m_bNoName)
         {

            return false;

         }

         if (!get_item_rect(lprect, i))
         {

            return false;

         }

         lprect->top += m_size.cy;

         return true;


      }

      return false;

   }

   bool image_list::get_item_rect(LPRECT lprect, index i)
   {

      if (i < 0 || i >= m_diba.get_count())
      {

         return false;

      }

      int pad = m_iPad;

      int text_height = m_bNoName ? 0 : m_iTextHeight;

      int xpad = m_iPad;

      rect rClient;

      GetClientRect(rClient);

      int cx = rClient.width();

      int w = m_size.cx;

      int h = m_size.cy;

      int iColCount = (cx - xpad) / (w + xpad);

      int cxInternal = iColCount * (w + xpad) - xpad;

      int xLeft;

      if (m_ealign & align_horizontal_center)
      {

         xLeft = (cx - cxInternal) / 2;

      }
      else
      {

         xLeft = xpad;

      }

      int x = xLeft;

      int y = pad;

      for (index pos = 0; pos < i; pos++)
      {

         if (x + w + pad + w + pad>= cx)
         {

            x = xLeft;

            y += h + pad + text_height;

         }
         else
         {

            x += w + pad;

         }

      }

      lprect->left = x;
      lprect->right = x + w;
      lprect->top = y;
      lprect->bottom = y + h + text_height;

      return true;

   }


   index image_list::hit_test(point pt, ::user::e_element & eelement)
   {

      ::count c = m_diba.get_count();

      rect r;

      for (index i = 0; i < c; i++)
      {

         if (get_item_rect(r, i))
         {

            if (r.contains(pt))
            {

               return i;

            }

         }

      }

      return -1;

   }



   void image_list::_001OnDraw(::draw2d::graphics * pgraphics)
   {

      rect r;

      rect rectClient;

      GetClientRect(rectClient);

      select_font(::user::font_default);

      rectClient.offset(m_ptScrollPassword1);

      pgraphics->fill_solid_rect(rectClient, _001GetColor(::user::color_background));

      pgraphics->draw3d_rect(rectClient, ARGB(255, 192, 192, 192));

      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

      for (index i = 0; i < m_diba.get_count(); i++)
      {

         rect rText;

         rect rSel;

         bool bRectText = get_element_rect(rText, i, element_text);

         if (get_element_rect(r, i, element_icon))
         {

            ::draw2d::dib * pdibSrc = m_diba[i];

            if (pdibSrc->area() > 0)
            {

               if (m_dibaThumb.get_size() < m_diba.get_size())
               {

                  m_dibaThumb.set_size(m_diba.get_size());

               }

               if (m_dibaThumb[i].is_null())
               {

                  m_dibaThumb[i].alloc(allocer());

               }

               ::draw2d::dib * pdib = m_dibaThumb[i];

               if (pdib->area() <= 0)
               {

                  rect rImage;

                  double dW = (double)r.width() / (double)pdibSrc->m_size.cx;

                  double dH = (double)r.height() / (double)pdibSrc->m_size.cy;

                  double dMin = MIN(dW, dH);

                  size szNew = pdibSrc->m_size * dMin;

                  pdib->create(szNew);

                  pdib->get_graphics()->SetStretchBltMode(HALFTONE);

                  pdib->get_graphics()->StretchBlt(rect(szNew), pdibSrc->get_graphics(), rect(pdibSrc->m_size));

               }

               rect rImage;

               rImage.left = r.left + (r.width() - pdib->m_size.cx) / 2;

               rImage.top = r.top + (r.height() - pdib->m_size.cy) / 2;

               rImage.right = rImage.left + pdib->m_size.cx;

               rImage.bottom = rImage.top + pdib->m_size.cy;

               rSel = rImage;

               if (!m_bNoName)
               {

                  rSel.bottom = rText.bottom;

               }

               rSel.inflate(5, 5);

               COLORREF crBorder = 0;

               COLORREF crSel = 0;

               bool bSel;

               bool bHover;

               if (m_iaSel.contains(i))
               {

                  bSel = true;

                  if (m_iHover == i)
                  {

                     crBorder = ARGB(255, 100, 180, 240);

                     crSel = ARGB(108, 100, 180, 240);

                     bHover = true;

                  }
                  else
                  {

                     crBorder = ARGB(255, 80, 140, 200);

                     crSel = ARGB(108, 80, 140, 200);

                     bHover = false;

                  }

               }
               else
               {

                  bSel = false;

                  if (m_iHover == i)
                  {

                     crBorder = ARGB(255, 80, 130, 180);

                     crSel = ARGB(108, 80, 130, 180);

                     bHover = true;

                  }
                  else
                  {

                     crBorder = ARGB(255, 100, 100, 100);

                     bHover = false;

                  }

               }

               if (bSel || bHover)
               {

                  pgraphics->fill_solid_rect(rSel, crSel);

               }

               pgraphics->draw(rImage, pdib->get_graphics());

               if (bSel)
               {


                  rImage.inflate(1, 1);

                  pgraphics->draw3d_rect(rSel, crBorder);

                  rImage.inflate(1, 1);

                  pgraphics->draw3d_rect(rSel, crBorder);

               }

            }

         }

         if (bRectText)
         {

            string str;

            if (_001GetItemText(str, i))
            {

               pgraphics->set_text_color(_001GetColor(::user::color_list_item_text));

               pgraphics->draw_text(str, rText, DT_CENTER | DT_VCENTER);

            }

         }

      }

   }


   bool image_list::_001GetItemText(string & str, index iItem)
   {

      return false;

   }


   void image_list::on_layout()
   {


      rect rClient;

      rect rTotal(0, 0, 0, 0);

      ::size sizeImage;

      for (index i = 0; i < m_diba.get_count(); i++)
      {

         rect r;

         if (get_item_rect(r, i))
         {

            if (i == 0)
            {

               sizeImage = r.get_size();

            }

            rTotal.unite(rTotal, r);

         }

      }

      if (m_sizeImage != sizeImage)
      {

         m_sizeImage = sizeImage;

         m_dibaThumb.remove_all();

      }

      rTotal.left = 0;

      rTotal.top = 0;

      rTotal.bottom += m_iPad;

      m_sizeTotal = rTotal.get_size();

      m_scrolldataVert.m_iPage = rClient.height();

      ::user::box::on_layout();


   }


   image_list_view::image_list_view(::aura::application * papp) :
      ::object(papp)
   {

   }


   image_list_view::~image_list_view()
   {
   }

   void image_list_view::assert_valid() const
   {

      ::user::image_list::assert_valid();

   }


   void image_list_view::dump(dump_context & dumpcontext) const
   {

      ::user::image_list::dump(dumpcontext);

   }


   void image_list_view::install_message_routing(::message::sender * psender)
   {

      ::user::impact::install_message_routing(psender);
      ::user::image_list::install_message_routing(psender);

      IGUI_MSG_LINK(WM_CREATE, psender, this, &image_list_view::_001OnCreate);
      IGUI_MSG_LINK(WM_DESTROY, psender, this, &image_list_view::_001OnDestroy);

   }


   void image_list_view::_001OnCreate(::message::message * pobj)
   {

      SCAST_PTR(::message::create, pcreate, pobj);

      pcreate->previous();

      if (pcreate->m_bRet)
         return;

   }


   void image_list_view::_001OnDestroy(::message::message * pobj)
   {

   }


   void image_list_view::on_update(::user::impact * pSender, LPARAM lHint, object* phint)
   {

      ::user::impact::on_update(pSender, lHint, phint);

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


   index image_list::_001GetCurSel()
   {

      synch_lock sl(m_pmutex);

      if (m_iaSel.get_count() == 1)
      {

         return m_iaSel[0];

      }

      return -1;

   }


   index_array image_list::_001GetSelection()
   {

      synch_lock sl(m_pmutex);

      return m_iaSel;

   }


   void image_list::_001SetCurSel(index iFind, ::action::context actioncontext)
   {

      synch_lock sl(m_pmutex);

      m_iaSel.remove_all();

      m_iaSel.add(iFind);

   }

   void image_list::_001SetSelection(const index_array & ia, ::action::context actioncontext)
   {

      synch_lock sl(m_pmutex);

      if (!::lemon::array::equals_non_unique_unordered(ia, m_iaSel))
      {

         m_iaSel = ia;

         ::user::control_event ev;

         ev.m_puie = this;

         ev.m_id = m_id;

         ev.m_eevent = ::user::event_after_change_cur_sel;

         on_control_event(&ev);

      }

   }


} // namespace user



