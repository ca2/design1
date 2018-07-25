#include "framework.h"

bool is_downloadable_url_dup(const char *psz)
{

   string str(psz);

   str.trim();

   return str::begins_ci(str, "http://") || str::begins_ci(str, "https://");


}

double sq(double d)
{

   return d * d;

}

namespace composite
{


   view::view(::aura::application * papp) :
      object(papp),
      ::serialize(papp)
   {

      m_sizeMaxPicAdjust.set(256);

      m_bAutoAdjustPicSize = true;

      m_bEnablePastePicture = false;

      m_eelementDrag = ::user::element_none;


      m_dAspect = 3.0 / 4.0;

      /*
      m_flagNonClient.unsignalize(non_client_background);
      m_flagNonClient.unsignalize(non_client_focus_rect);
      */

      m_bHelloLayoutOn001Layout = false;

      m_b001LayoutIgnoreEmpty = false;

      m_bHelloLayoutOn001Layout = true;

      m_b001LayoutIgnoreEmpty = false;

      m_pdata = canew(data(get_app()));

      m_pdata->m_pictool->m_pview = this;

   }


   view::~view()
   {

   }


   void view::assert_valid() const
   {

      user::box::assert_valid();

   }


   void view::dump(dump_context & dumpcontext) const
   {

      user::box::dump(dumpcontext);

   }


   void view::install_message_routing(::message::sender * psender)
   {

      impact::install_message_routing(psender);

      IGUI_MSG_LINK(message_view_update, psender, this, &view::_001OnLayout);
      IGUI_MSG_LINK(WM_CREATE, psender, this, &view::_001OnCreate);
      IGUI_MSG_LINK(WM_DESTROY, psender, this, &view::_001OnDestroy);
      IGUI_MSG_LINK(WM_MOUSEMOVE, psender, this, &view::_001OnMouseMove);
      IGUI_MSG_LINK(WM_LBUTTONDOWN, psender, this, &view::_001OnLButtonDown);
      IGUI_MSG_LINK(WM_LBUTTONUP, psender, this, &view::_001OnLButtonUp);
      IGUI_MSG_LINK(WM_KEYDOWN, psender, this, &view::_001OnKeyDown);

      connect_command("edit_paste", &view::_001OnEditPaste);
      connect_command_probe("edit_paste", &view::_001OnUpdateEditPaste);


   }


   void view::_001OnCreate(::message::message * pobj)
   {

      SCAST_PTR(::message::create, pcreate, pobj);

      pcreate->previous();

      if (pcreate->m_bRet)
         return;

      string strId = get_document()->m_pimpactsystem->m_strMatter;

      string strText;

      data_get("cur_text", strText);

      if (GetTypedParent<::user::split_view>() != NULL)
      {

         if (GetTypedParent<::user::split_view>()->get_child_by_id("top_edit_view") != NULL)
         {

            sp(::user::edit_text) pedit = GetTypedParent<::user::split_view>()->get_child_by_id("top_edit_view");

            pedit->_001SetText(strText, ::action::source_initialize);

         }

      }

   }


   void view::load()
   {

   }


   void view::save()
   {

   }


   void view::_001OnTimer(::timer * ptimer)
   {

      if (ptimer->m_nIDEvent == timer_drag)
      {

         KillTimer(timer_drag);

         if (m_pdata->m_picCurrent.is_set())
         {

            m_pdata->m_picCurrent->m_ppic->m_bDrag = true;

         }

      }
      else
      {

         ::user::impact::_001OnTimer(ptimer);

      }

   }


   void view::_001OnDestroy(::message::message * pobj)
   {


   }


   void view::_001OnEditPaste(::message::message * pmessage)
   {

      pmessage->m_bRet = true;

      do_edit_paste();


   }

   void view::_001OnUpdateEditPaste(::message::message * pmessage)
   {

      SCAST_PTR(::user::command, pcommand, pmessage);

      pcommand->Enable(m_bEnablePastePicture);

      pmessage->m_bRet = true;


   }


   pointd view::pick_random_placement(double dRate)
   {

      rect rectClient;

      GetClientRect(rectClient);

      return rectClient.random_point(dRate);

   }


   void view::do_edit_paste()
   {

      string strCandidate;

      if (Session.copydesk().has_plain_text())
      {

         Session.copydesk().get_plain_text(strCandidate);

      }

      ::visual::dib_sp dib(allocer());

      point ptPlacement;

      Session.get_cursor_pos(ptPlacement);

      ScreenToClient(ptPlacement);

      if(strCandidate.has_char() && is_downloadable_url_dup(strCandidate))
      {

         ::file::path path = strCandidate;

         place_pic(ptPlacement, path);

      }
      else if (strCandidate.has_char() && file_exists_dup(strCandidate) &&
               dib.load_from_file(strCandidate, false))
      {

         place_pic(ptPlacement, dib);

      }
      else if (Session.copydesk().has_dib())
      {

         Session.copydesk().desk_to_dib(dib);

         place_pic(ptPlacement, dib);

      }

      m_pdata->m_pictool->m_etoolMode = ::composite::tool_none;


   }


   void view::_001OnKeyDown(::message::message * pobj)
   {

      SCAST_PTR(::message::key, pkey, pobj);


      if (Session.is_key_pressed(::user::key_control)
            && !Session.is_key_pressed(::user::key_alt)
            && !Session.is_key_pressed(::user::key_shift))
      {

         // only CTRL key is pressed and...

         if (pkey->m_ekey == ::user::key_v)
         {

            do_edit_paste();

            pkey->m_bRet = true;

         }


      }


   }


   void view::_001OnLButtonDown(::message::message * pobj)
   {

      SCAST_PTR(::message::mouse, pmouse, pobj);

      pointd pt = pmouse->m_pt;

      ScreenToClient(&pt);

      int iHit = -1;

      m_pdata->m_etoolDown = tool_none;

      if (m_pdata->m_pictool.is_set())
      {

         m_pdata->m_pictool->hit_test(m_pdata->m_etoolDown, pt);

      }

      if (m_pdata->m_picCurrent.is_set() && m_pdata->m_picCurrent->is_dragging() && !is_tool_editing_text())
      {

         pmouse->m_bRet = true;

      }
      else if (m_pdata->m_picCurrent.is_set()
               && m_pdata->m_picCurrent != m_picName
               && (iHit = m_pdata->m_picCurrent->hit_test_cursor(pt)) >= 0
               || m_pdata->m_etoolDown != tool_none)
      {

         if (m_pdata->m_etoolDown == ::composite::tool_none && iHit == 0 && !is_tool_editing_text())
         {

            m_pdata->m_picCurrent->m_ppic->m_bDrag = true;

            ::rectd r(m_pdata->m_picCurrent->m_ppic->m_rect);

            ClientToScreen(r);

            m_ptEditCursorOffset = pointd(pmouse->m_pt);

            if (m_pdata->m_pictool->m_etoolMode == ::composite::tool_move)
            {

               ScreenToClient(m_ptEditCursorOffset);

               m_pdata->m_picCurrent->drag_rtransform_point(m_ptEditCursorOffset);

               m_ptEditCursorOffset = m_ptEditCursorOffset - sized(m_pdata->m_picCurrent->m_ppic->m_ptDrag.x * m_pdata->m_picCurrent->m_ppic->m_rect.width(),
                                      m_pdata->m_picCurrent->m_ppic->m_ptDrag.y * m_pdata->m_picCurrent->m_ppic->m_rect.height());

            }
            else
            {

               m_ptEditCursorOffset -= r.top_left();

            }

            pmouse->m_bRet = true;

         }
         else
         {

            m_pdata->m_pictool->m_map[m_pdata->m_etoolDown].m_bDrag = true;

            m_pdata->m_pictool->m_ptCenter = m_pdata->m_picCurrent->m_ppic->m_rect.center();

            pmouse->m_ecursor = m_pdata->m_pictool->m_map[m_pdata->m_etoolDown].m_ecursor;

            pmouse->m_bRet = true;

            if (m_pdata->m_etoolDown == ::composite::tool_rotate)
            {

               m_dStartAngle = atan2((double)(m_pdata->m_pictool->m_ptCenter.y - pt.y), (double)(m_pdata->m_pictool->m_ptCenter.x - pt.x)) - m_pdata->m_picCurrent->m_ppic->m_dRotate;

            }
            else if (m_pdata->m_etoolDown == ::composite::tool_resize)
            {

               m_pdata->m_pictool->m_ptResizeOrigin = m_pdata->m_picCurrent->m_ppic->m_rect.top_left();

               m_pdata->m_picCurrent->_transform_point(m_pdata->m_pictool->m_ptResizeOrigin);

            }

         }

      }
      else
      {

         {


            for (auto & pic : m_pdata->m_pica)
            {

               if (pic->hit_test(pt) >= 0)
               {

                  pmouse->m_ecursor = ::visual::cursor_move;

                  m_ptEditCursorOffset = pt - pic->m_ppic->m_rect.top_left();

                  m_pdata->m_picCurrent = pic;

                  on_pic_update();

                  m_pdata->m_picCurrent->m_ppic->m_bDrag = true;

                  goto selected;

               }

            }

            ::user::e_element eelement = ::user::element_none;

            index iHitItem = hit_test(pt, eelement);

            if ((iHitItem >= 0 || eelement != ::user::element_none) && eelement != ::user::element_client)
            {

               m_eelementDrag = eelement;

               pmouse->m_bRet = true;

            }
            else
            {

               bool bNewTextBox = true;

               if (m_pdata->m_picCurrent.is_set())
               {

                  m_pdata->m_picCurrent.release();

                  bNewTextBox = false;

               }

               sp(::user::rich_text::edit) peditFocus = Session.get_keyboard_focus();

               if (peditFocus.is_set())
               {

                  Session.set_keyboard_focus(NULL);

                  bNewTextBox = false;

               }

               if (bNewTextBox)
               {

                  sp(::user::rich_text::edit) pedit = create_rich_text_edit(pt);

                  place_pic(pt, pedit);

               }

            }

         }

selected:;

         set_need_redraw();

         pmouse->m_bRet = true;

      }

   }

   void view::_001OnLButtonUp(::message::message * pobj)
   {

      SCAST_PTR(::message::mouse, pmouse, pobj);

      point pt = pmouse->m_pt;

      ScreenToClient(&pt);

      KillTimer(timer_drag);

      if (m_eelementDrag == ::user::element_margin_top)
      {

         m_pdata->m_rectMargin.top = pt.y;

         set_need_layout();

         set_need_redraw();

         pmouse->m_bRet = true;

         save();

      }
      else if (m_eelementDrag == ::user::element_margin_left)
      {

         m_pdata->m_rectMargin.left = pt.x;

         set_need_layout();

         set_need_redraw();

         pmouse->m_bRet = true;

         save();

      }
      else if (m_eelementDrag == ::user::element_margin_right)
      {

         m_pdata->m_rectMargin.right = pt.x;

         set_need_layout();

         set_need_redraw();

         pmouse->m_bRet = true;

         save();

      }
      else if (m_eelementDrag == ::user::element_margin_bottom)
      {

         m_pdata->m_rectMargin.bottom = pt.y;

         set_need_layout();

         set_need_redraw();

         pmouse->m_bRet = true;

         save();

      }

      ::composite::e_tool etool = tool_none;

      if (m_pdata->m_pictool != NULL)
      {

         m_pdata->m_pictool->hit_test(etool, pt);

      }


      if (m_pdata->m_pictool.is_set() && m_pdata->m_etoolDown != ::composite::tool_none)
      {
         if (m_pdata->m_etoolDown == ::composite::tool_rotate)
         {

            save();

         }
         m_pdata->m_pictool->m_map[m_pdata->m_etoolDown].m_bDrag = false;

      }

      if (m_pdata->m_picCurrent.is_set() && m_pdata->m_picCurrent->is_dragging() && !is_tool_editing_text())
      {

         if (m_pdata->m_pictool->m_etoolMode == ::composite::tool_move)
         {

            pointd pt = pmouse->m_pt;

            ScreenToClient(&pt);

            m_pdata->m_picCurrent->drag_rtransform_point(pt);

            pt -= m_ptEditCursorOffset;

            m_pdata->m_picCurrent->m_ppic->m_ptDrag = pointd(pt.x / m_pdata->m_picCurrent->m_ppic->m_rect.width(), pt.y / m_pdata->m_picCurrent->m_ppic->m_rect.height());

            m_pdata->m_pictool->m_etoolMode = ::composite::tool_crop;

         }
         else
         {

            pointd pt = pmouse->m_pt;

            pt -= m_ptEditCursorOffset;

            ScreenToClient(&pt);

            m_pdata->m_picCurrent->move_to(pt, m_pdata->m_sizePage, get_size(), m_pdata->m_rectClient);

         }

         m_pdata->m_picCurrent->m_ppic->m_bDrag = false;

         pmouse->m_bRet = true;

         set_need_layout();

         set_need_redraw();

         save();

         sp(::user::rich_text::edit) pedit = m_pdata->m_picCurrent;


         if (pedit.is_set())
         {

            pedit->SetFocus();

         }



      }
      else if (m_pdata->m_picCurrent.is_set() && etool != tool_none)
      {


         if (etool == m_pdata->m_etoolDown && etool != ::composite::tool_none)
         {

            switch (etool)
            {
            case ::composite::tool_crop:
            {

               m_pdata->m_pictool->m_etoolMode = ::composite::tool_crop;

            }
            break;
            case ::composite::tool_edit_text:
            {

               sp(::user::rich_text::edit) pedit = m_pdata->m_picCurrent;

               if (is_tool_editing_text())
               {

                  if (pedit.is_set())
                  {

                     pedit->set_text_editable(false);

                  }

                  m_pdata->m_pictool->m_etoolMode = ::composite::tool_none;

               }
               else
               {

                  m_pdata->m_pictool->m_etoolMode = ::composite::tool_edit_text;

                  if (pedit.is_set())
                  {

                     pedit->set_text_editable(true);

                     pedit->keyboard_set_focus();

                  }

               }

            }
            break;
            case ::composite::tool_move:
            {

               ASSERT(m_pdata->m_pictool->m_etoolMode == ::composite::tool_crop || m_pdata->m_pictool->m_etoolMode == ::composite::tool_move);

               m_pdata->m_pictool->m_etoolMode = ::composite::tool_move;

            }
            break;
            case ::composite::tool_apply:
            {

               ASSERT(m_pdata->m_pictool->m_etoolMode == ::composite::tool_crop || m_pdata->m_pictool->m_etoolMode == ::composite::tool_move);

               if (m_pdata->m_pictool->m_etoolMode == ::composite::tool_crop
                     || m_pdata->m_pictool->m_etoolMode == ::composite::tool_move)
               {

                  m_pdata->m_pictool->m_etoolMode = ::composite::tool_none;

               }

            }
            break;
            case ::composite::tool_zoom_in:
            {

               ASSERT(m_pdata->m_pictool->m_etoolMode == ::composite::tool_crop || m_pdata->m_pictool->m_etoolMode == ::composite::tool_move);

               if (m_pdata->m_pictool->m_etoolMode == ::composite::tool_move)
               {

                  m_pdata->m_pictool->m_etoolMode = ::composite::tool_crop;

               }

               m_pdata->m_picCurrent->m_ppic->m_dZoom *= 1.1;

               save();



            }
            break;
            case ::composite::tool_zoom_out:
            {

               if (m_pdata->m_pictool->m_etoolMode == ::composite::tool_move)
               {

                  m_pdata->m_pictool->m_etoolMode = ::composite::tool_crop;

               }

               ASSERT(m_pdata->m_pictool->m_etoolMode == ::composite::tool_crop);

               m_pdata->m_picCurrent->m_ppic->m_dZoom /= 1.1;

               save();



            }
            break;
            case ::composite::tool_close:
            {

               sp(::user::rich_text::edit) pedit = m_pdata->m_picCurrent;

               if (pedit.is_set())
               {

                  pedit->DestroyWindow();

               }

               if (m_pdata->m_pictool->m_etoolMode == ::composite::tool_crop)
               {

                  m_pdata->m_pictool->m_etoolMode = ::composite::tool_none;

               }
               else
               {

                  m_pdata->m_pica.remove(m_pdata->m_picCurrent);

                  m_pdata->m_picCurrent.release();

                  set_need_redraw();

                  save();



               }

            }

            break;

            case ::composite::tool_stack_up:
            {

               index iFind = m_pdata->m_pica.find_first(m_pdata->m_picCurrent);

               if (iFind >= 0)
               {

                  rectd rIntersect;

                  index iFound = -1;

                  for (index i = iFind + 1; i < m_pdata->m_pica.get_count(); i++)
                  {

                     if (rIntersect.intersect(m_pdata->m_picCurrent->m_ppic->m_rect, m_pdata->m_pica[i]->m_ppic->m_rect))
                     {

                        iFound = i;

                        break;

                     }

                  }

                  if (iFound < 0)
                  {

                     iFound = iFind + 1;

                  }

                  if (iFound < m_pdata->m_pica.get_count())
                  {

                     m_pdata->m_pica.remove_at(iFind);

                     m_pdata->m_pica.insert_at(iFound, m_pdata->m_picCurrent);

                  }

                  on_pic_update();

                  save();



               }

            }
            break;

            case ::composite::tool_stack_down:
            {

               index iFind = m_pdata->m_pica.find_first(m_pdata->m_picCurrent);

               if (iFind >= 0)
               {

                  rectd rIntersect;

                  index iFound = -1;

                  for (index i = iFind - 1; i >= 0; i--)
                  {

                     if (rIntersect.intersect(m_pdata->m_picCurrent->m_ppic->m_rect, m_pdata->m_pica[i]->m_ppic->m_rect))
                     {

                        iFound = i;

                        break;

                     }

                  }

                  if (iFound < 0)
                  {

                     iFound = iFind - 1;

                  }

                  if (iFound >= 0)
                  {

                     m_pdata->m_pica.remove_at(iFind);

                     m_pdata->m_pica.insert_at(iFound, m_pdata->m_picCurrent);

                  }

                  on_pic_update();

                  save();



               }

            }
            break;

            default:;

            }

         }

         if (!is_tool_editing_text())
         {

            set_need_redraw();

            pmouse->m_bRet = true;

         }

      }

      m_eelementDrag = ::user::element_none;

   }


   void view::_001OnMouseMove(::message::message * pobj)
   {

      SCAST_PTR(::message::mouse, pmouse, pobj);

      pointd pt = pmouse->m_pt;

      ScreenToClient(&pt);

      if (m_eelementDrag == ::user::element_margin_top)
      {

         pmouse->m_ecursor = visual::cursor_size_top;

         m_pdata->m_rectMargin.top = pt.y;

         set_need_layout();

         set_need_redraw();

         pmouse->m_bRet = true;

      }
      else if (m_eelementDrag == ::user::element_margin_left)
      {

         pmouse->m_ecursor = visual::cursor_size_left;

         m_pdata->m_rectMargin.left = pt.x;

         set_need_layout();

         set_need_redraw();

         pmouse->m_bRet = true;

      }
      else if (m_eelementDrag == ::user::element_margin_right)
      {

         pmouse->m_ecursor = visual::cursor_size_right;

         m_pdata->m_rectMargin.right = pt.x;

         set_need_layout();

         set_need_redraw();

         pmouse->m_bRet = true;

      }
      else if (m_eelementDrag == ::user::element_margin_bottom)
      {

         pmouse->m_ecursor = visual::cursor_size_bottom;

         m_pdata->m_rectMargin.bottom = pt.y;

         set_need_layout();

         set_need_redraw();

         pmouse->m_bRet = true;

      }
      else if (m_pdata->m_picCurrent.is_set()
               && m_pdata->m_picCurrent->is_valid()
               && m_pdata->m_pictool.is_set() && m_pdata->m_etoolDown != ::composite::tool_none
               && m_pdata->m_pictool->m_map[m_pdata->m_etoolDown].m_bDrag
               && !is_tool_editing_text())
      {

         pmouse->m_ecursor = m_pdata->m_pictool->m_map[m_pdata->m_etoolDown].m_ecursor;

         if (m_pdata->m_etoolDown == ::composite::tool_rotate)
         {

            m_pdata->m_picCurrent->m_ppic->m_dRotate = atan2(
                  (double)(m_pdata->m_pictool->m_ptCenter.y - pt.y),
                  (double)(m_pdata->m_pictool->m_ptCenter.x - pt.x)) - m_dStartAngle;

            m_pdata->m_picCurrent->update_region();

            set_need_layout();

            set_need_redraw();

         }
         else if (m_pdata->m_etoolDown == ::composite::tool_resize)
         {

            double a = sin(m_pdata->m_picCurrent->m_ppic->m_dRotate);

            double b = cos(m_pdata->m_picCurrent->m_ppic->m_dRotate);

            double x1 = m_pdata->m_pictool->m_ptResizeOrigin.x;

            double y1 = m_pdata->m_pictool->m_ptResizeOrigin.y;

            double x2 = pt.x;

            double y2 = pt.y;

            double x = (x1 + x2) / 2.0;

            double y = (y1 + y2) / 2.0;

            double h = -(a*(x2-x1)-b *(y2-y1)) ;

            double w = b*(x2 - x1) + a * (y2 - y1);

            bool bChanged = false;

            if (h < 64)
            {

               h = 64;

               bChanged = true;

            }

            if (w < 64)
            {

               w = 64;

               bChanged = true;

            }

            if (bChanged)
            {

               //double f = sqrt(sq(a) + sq(b));

               //double f = 1.0;

               x2 = - a*h + sq(a)*x1 + b*w + sq(b)*x1;

               y2 = a*w + sq(a)*y1 + b*h + sq(b)*y1;

               x = (x1 + x2) / 2.0;

               y = (y1 + y2) / 2.0;

            }


            double dy = h / 2.0;

            double dx = w / 2.0;

            m_pdata->m_picCurrent->m_ppic->m_rect.left = x - dx;

            m_pdata->m_picCurrent->m_ppic->m_rect.top = y - dy;

            m_pdata->m_picCurrent->m_ppic->m_rect.right = x + dx;

            m_pdata->m_picCurrent->m_ppic->m_rect.bottom = y + dy;


            //sizeNew.cx = MAX(sizeMin.cx, sizeNew.cx);

            //sizeNew.cy = MAX(sizeMin.cy, sizeNew.cy);

            //m_pdata->m_picCurrent->m_ppic->m_rect.set_size(sizeNew);

            m_pdata->m_picCurrent->update_drawing_rect(m_pdata->m_sizePage, get_size());

            m_pdata->m_picCurrent->update_region();

            m_pdata->m_picCurrent->update_placement();

            set_need_layout();

            set_need_redraw();

         }

      }
      else if (m_pdata->m_picCurrent.is_set() && m_pdata->m_picCurrent->is_dragging() && !is_tool_editing_text())
      {

         if (m_pdata->m_pictool->m_etoolMode == ::composite::tool_move)
         {

            pointd pt = pmouse->m_pt;

            ScreenToClient(&pt);

            m_pdata->m_picCurrent->drag_rtransform_point(pt);

            pt -= m_ptEditCursorOffset;

            m_pdata->m_picCurrent->m_ppic->m_ptDrag = pointd(pt.x / m_pdata->m_picCurrent->m_ppic->m_rect.width(), pt.y / m_pdata->m_picCurrent->m_ppic->m_rect.height());

         }
         else
         {

            pointd pt = pmouse->m_pt;

            pt -= m_ptEditCursorOffset;

            ScreenToClient(&pt);

            m_pdata->m_picCurrent->move_to(pt, m_pdata->m_sizePage, get_size(), m_pdata->m_rectClient);

            pica_to_margin();

         }

         pmouse->m_bRet = true;

         pmouse->m_ecursor = ::visual::cursor_move;

         set_need_layout();

         set_need_redraw();

      }
      else
      {

         for (auto & pic : m_pdata->m_pica)
         {

            if (pic == m_pdata->m_picCurrent)
            {

               int iHit = m_pdata->m_picCurrent->hit_test_cursor(pt);

               if (iHit >= 0)
               {

                  ::composite::e_tool etool;

                  m_pdata->m_pictool->hit_test(etool, pt);

                  if (etool == ::composite::tool_none && iHit == 0)
                  {

                     pmouse->m_ecursor = ::visual::cursor_move;

                     pmouse->m_bRet = true;

                     break;

                  }
                  else
                  {

                     pmouse->m_ecursor = m_pdata->m_pictool->m_map[etool].m_ecursor;

                     pmouse->m_bRet = true;

                     break;

                  }

               }


            }
            else if (pic != NULL && pic->hit_test(pt) >= 0)
            {

               pmouse->m_ecursor = ::visual::cursor_move;

               pmouse->m_bRet = true;

               break;

            }

         }

         if (!pmouse->m_bRet)
         {

            ::user::e_element eelement;

            int iHit = (int) hit_test(pt, eelement);

            if (iHit < 0)
            {

               if (eelement == ::user::element_margin_top)
               {

                  pmouse->m_ecursor = ::visual::cursor_size_top;

                  pmouse->m_bRet = true;

               }
               else if (eelement == ::user::element_margin_left)
               {

                  pmouse->m_ecursor = ::visual::cursor_size_left;

                  pmouse->m_bRet = true;

               }
               else if (eelement == ::user::element_margin_right)
               {

                  pmouse->m_ecursor = ::visual::cursor_size_right;

                  pmouse->m_bRet = true;

               }
               else if (eelement == ::user::element_margin_bottom)
               {

                  pmouse->m_ecursor = ::visual::cursor_size_bottom;

                  pmouse->m_bRet = true;

               }

            }

         }

      }


   }


   void view::_001OnDraw(::draw2d::graphics * pgraphics)
   {

      if (!GetTopLevelFrame()->frame_is_transparent())
      {

         rect rClient;

         GetClientRect(rClient);

         rectd rectClient(rClient);

         pgraphics->fill_solid_rect(rectClient, ARGB(40, 255, 255, 255));

      }

      _001OnDrawPic(pgraphics);


   }

   index view::hit_test(pointd point, ::user::e_element & eelement)
   {

      return -1;

   }


   void view::stream_link(string strLink, object & object)
   {

      ::object * pserializable = &object;

      ::draw2d::dib_sp pdib = pserializable;

      if (strLink.has_char())
      {

         ::file::path path = get_link_path(strLink);

         if (path.has_char())
         {

            if (pdib.is_set())
            {

               ::visual::dib_sp dib(allocer());

               if (dib.load_from_file(path))
               {

                  pdib->from(dib);

               }
               else
               {

                  pdib->create(16, 16);

                  pdib->FillByte(ARGB(255, 255, 0, 0));

               }

            }

         }

      }
      else
      {

         ::serialize::stream_link(strLink, object);

      }

   }



   void view::_001OnDrawPic(::draw2d::graphics * pgraphics)
   {

      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

      for (auto & pic : m_pdata->m_pica)
      {

         if (pic.is_set() && pic->is_valid())
         {

            pic->draw(pgraphics);

         }

      }

      if (m_pdata->m_picCurrent.is_set() && m_pdata->m_picCurrent->is_valid())
      {

         {

            ::draw2d::savedc savedc(pgraphics);

            ::draw2d::matrix mRot;

            mRot.append(::draw2d::matrix::rotation(m_pdata->m_picCurrent->m_ppic->m_dRotate));

            pgraphics->prepend(mRot);

            ::draw2d::matrix mTrans;

            mTrans.append(::draw2d::matrix::translation(m_pdata->m_picCurrent->m_ppic->m_rect.center().x, m_pdata->m_picCurrent->m_ppic->m_rect.center().y));

            pgraphics->append(mTrans);

            //pgraphics->draw(m_pdata->m_picCurrent->m_ppic->m_rect, m_pdata->m_picCurrent->m_ppic->m_dib->g(), rect(m_pdata->m_picCurrent->m_ppic->m_dib->m_size));

            m_pdata->m_pictool->draw(pgraphics);

         }

         m_pdata->m_picCurrent->m_ppic->m_rectCursor.offset(m_pdata->m_picCurrent->m_ppic->m_rect.center());

      }

      pgraphics->draw_rect(m_pdata->m_rectMargin, m_pdata->m_pictool->m_penBorder);

   }

   void view::_001OnLayout(::message::message * pobj)
   {

      synch_lock sl(m_pmutex);

      {

         on_layout();

      }

   }

   bool view::keyboard_focus_is_focusable()
   {

      return true;

   }

   void view::on_update(::user::impact * pSender, LPARAM lHint, object* phint)
   {

      ::user::impact::on_update(pSender, lHint, phint);

      ::user::view_update_hint * puh = dynamic_cast <::user::view_update_hint *> (phint);

      if (lHint == 123)
      {

         set_need_layout();

      }

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


   void view::on_layout()
   {

      rect rectClient;

      GetClientRect(rectClient);

      if (rectClient.area() <= 0)
      {

         return;

      }

      double dx = (double)m_pdata->m_sizePage.cx / (double)::user::interaction::width();

      double dy = (double)m_pdata->m_sizePage.cy / (double)height();

      m_pdata->m_rectClient = rectClient;

      if (m_pdata->m_sizePagePrev.area() <= 0 || m_pdata->m_rectMargin.is_null())
      {

         m_pdata->m_rectMarginDrawing.set(null_pointd(), pointd(m_pdata->m_sizePage));

      }

      if (m_pdata->m_sizePagePrev != m_pdata->m_sizePage)
      {

         if (m_pdata->m_sizePagePrev.area() > 0)
         {

            double dxRate = (double)m_pdata->m_sizePage.cx / (double)m_pdata->m_sizePagePrev.cx;
            double dyRate = (double)m_pdata->m_sizePage.cy / (double)m_pdata->m_sizePagePrev.cy;

            m_pdata->m_rectMarginDrawing.left *= dxRate;
            m_pdata->m_rectMarginDrawing.top *= dyRate;
            m_pdata->m_rectMarginDrawing.right *= dxRate;
            m_pdata->m_rectMarginDrawing.bottom *= dyRate;

         }

         m_pdata->m_rectMaxMarginDrawing.left = m_pdata->m_sizePage.cx / 70;
         m_pdata->m_rectMaxMarginDrawing.top = m_pdata->m_sizePage.cy / 70;
         m_pdata->m_rectMaxMarginDrawing.right = m_pdata->m_sizePage.cx - m_pdata->m_sizePage.cx / 70;
         m_pdata->m_rectMaxMarginDrawing.bottom = m_pdata->m_sizePage.cy - m_pdata->m_sizePage.cy / 70;

         m_pdata->m_sizePagePrev = m_pdata->m_sizePage;

      }

      if (m_pdata->m_rectMarginPrev != m_pdata->m_rectMargin)
      {

         m_pdata->m_rectMarginDrawing.left = m_pdata->m_rectMargin.left * dx;
         m_pdata->m_rectMarginDrawing.top = m_pdata->m_rectMargin.top * dy;
         m_pdata->m_rectMarginDrawing.right = m_pdata->m_rectMargin.right * dx;
         m_pdata->m_rectMarginDrawing.bottom = m_pdata->m_rectMargin.bottom * dy;

      }

      m_pdata->m_rectMarginDrawing.intersect(m_pdata->m_rectMaxMarginDrawing);

      m_pdata->m_rectMargin.left = m_pdata->m_rectMarginDrawing.left / dx;
      m_pdata->m_rectMargin.top = m_pdata->m_rectMarginDrawing.top / dy;
      m_pdata->m_rectMargin.right = m_pdata->m_rectMarginDrawing.right / dx;
      m_pdata->m_rectMargin.bottom = m_pdata->m_rectMarginDrawing.bottom / dy;

      m_pdata->m_rectMarginPrev = m_pdata->m_rectMargin;

   }


   void view::defer_check_on_draw_layout()
   {

   }


   void view::set_background(::file::path path)
   {

      ::visual::dib_sp dib(allocer());

      if (dib.load_from_file(path, false))
      {

         m_pdata->m_dibBackground = dib;

         set_need_redraw();

      }

   }


   ::user::pic * view::place_pic(pointd pt, ::file::path path)
   {

      ::visual::dib_sp dib(allocer());


      var varFile;
      varFile["url"] = path;
      varFile["http_set"]["disable_common_name_cert_check"] = true;

      if (dib.load_from_file(varFile, false))
      {

         ::draw2d::dib_sp dib2(allocer());

         dib2->create(128, 128 * dib->m_size.cy / dib->m_size.cx);

         dib2->g()->draw(rect(dib2->m_size), dib->g(), rect(dib->m_size));

      }

      return place_pic(pt, dib);

   }


   ::user::pic * view::place_pic(pointd pt, ::draw2d::dib * pdib)
   {

      sp(pic) ppic = canew(pic(get_app()));

      ppic->enable_pic();

      ppic->m_dib = pdib;

      place_pic(pt, ppic);

      return ppic;

   }


   void view::place_pic(pointd pt, ::user::pic * ppic)
   {

      m_ptEditCursorOffset = ppic->get_size() / 2;

      if (m_bAutoAdjustPicSize && ppic->get_size().area() > 0)
      {

         double d1 = (double)m_sizeMaxPicAdjust.cx / (double)ppic->get_size().cx;

         double d2 = (double)m_sizeMaxPicAdjust.cy / (double)ppic->get_size().cy;

         double d = MIN(d1, d2);

         ppic->m_ppic->m_rect = rectd(pt, ::sized(ppic->get_size().cx * d, ppic->get_size().cy * d));

         //ppic->m_dib.alloc(allocer());

         //ppic->m_dib->create(pdib->m_size.cx * d, pdib->m_size.cy * d);

         //ppic->m_dib->g()->StretchBlt(0, 0, ppic->m_dib->m_size.cx, ppic->m_dib->m_size.cy, pdib->g(), 0, 0,
         //                             pdib->m_size.cx, pdib->m_size.cy);

      }
      else
      {

         ppic->m_ppic->m_rect = rectd(pt, ppic->get_size());

      }

      m_pdata->m_picCurrent = ppic;

      m_pdata->m_pica.add(m_pdata->m_picCurrent);

      on_pic_update();

      m_ptEditCursorOffset = ppic->m_ppic->m_rect.get_size()/2;

#ifdef WINDOWSEX

      point ptCursor(ppic->m_ppic->m_rect.center() + client_to_screen());

      ::SetCursorPos(ptCursor.x, ptCursor.y);

#endif

      m_pdata->m_picCurrent->m_ppic->m_bDrag = true;

   }


   void view::on_draw_image_layer(::draw2d::graphics * pgraphics)
   {


   }



   void view::on_pic_update()
   {

      sp(pic) ppic = m_pdata->m_picCurrent;

      if (ppic.is_set())
      {

         m_pdata->m_pictool->m_map[::composite::tool_rotate].m_ptAlign.SetPoint(-1.0, -1.0);
         m_pdata->m_pictool->m_map[::composite::tool_crop].m_ptAlign.SetPoint(0.0, -1.0);
         m_pdata->m_pictool->m_map[::composite::tool_edit_text].m_ptAlign.SetPoint(0.0, -1.0);
         m_pdata->m_pictool->m_map[::composite::tool_close].m_ptAlign.SetPoint(1.0, -1.0);
         m_pdata->m_pictool->m_map[::composite::tool_stack_up].m_ptAlign.SetPoint(-0.75, 1.0);
         m_pdata->m_pictool->m_map[::composite::tool_special_effect].m_ptAlign.SetPoint(0.0, 1.0);
         m_pdata->m_pictool->m_map[::composite::tool_resize].m_ptAlign.SetPoint(1.0, 1.0);
         m_pdata->m_pictool->m_map[::composite::tool_stack_down].m_ptAlign.SetPoint(0.75, 1.0);
         m_pdata->m_pictool->m_map[::composite::tool_zoom_out].m_ptAlign.SetPoint(-1.0, -1.0);
         m_pdata->m_pictool->m_map[::composite::tool_move].m_ptAlign.SetPoint(-0.33, -1.0);
         m_pdata->m_pictool->m_map[::composite::tool_zoom_in].m_ptAlign.SetPoint(0.33, -1.0);
         m_pdata->m_pictool->m_map[::composite::tool_apply].m_ptAlign.SetPoint(0.0, -0.5);

      }
      else
      {

         m_pdata->m_pictool->m_map[::composite::tool_rotate].m_ptAlign.SetPoint(-1000.0, -1000.0);
         m_pdata->m_pictool->m_map[::composite::tool_crop].m_ptAlign.SetPoint(0.0, -1000.0);
         m_pdata->m_pictool->m_map[::composite::tool_edit_text].m_ptAlign.SetPoint(0.0, -1000.0);
         m_pdata->m_pictool->m_map[::composite::tool_close].m_ptAlign.SetPoint(1000.0, -1000.0);
         m_pdata->m_pictool->m_map[::composite::tool_stack_up].m_ptAlign.SetPoint(-1000.0, 1000.0);
         m_pdata->m_pictool->m_map[::composite::tool_special_effect].m_ptAlign.SetPoint(0.0, 1000.0);
         m_pdata->m_pictool->m_map[::composite::tool_resize].m_ptAlign.SetPoint(1.0, 1.0);
         m_pdata->m_pictool->m_map[::composite::tool_stack_down].m_ptAlign.SetPoint(1000.0, 1000.0);
         m_pdata->m_pictool->m_map[::composite::tool_zoom_out].m_ptAlign.SetPoint(-1000.0, -1000.0);
         m_pdata->m_pictool->m_map[::composite::tool_move].m_ptAlign.SetPoint(-0.75, -1001.0);
         m_pdata->m_pictool->m_map[::composite::tool_zoom_in].m_ptAlign.SetPoint(0.5, -1001.0);
         m_pdata->m_pictool->m_map[::composite::tool_apply].m_ptAlign.SetPoint(0.0, -1000.0);

      }

      index i = m_pdata->m_pica.find_first(m_pdata->m_picCurrent);

      if (i >= 0)
      {

         m_pdata->m_pictool->m_map[::composite::tool_stack_down].m_bEnable = i > 0;
         m_pdata->m_pictool->m_map[::composite::tool_stack_up].m_bEnable = i < m_pdata->m_pica.get_upper_bound();

      }

      pica_to_margin();

      for (auto & pic : m_pdata->m_pica)
      {

         pic->update_region();

      }

   }


   pic_tool::tool::tool()
   {

      m_bEnable = true;

      m_bDrag = false;

      m_ecursor = ::visual::cursor_arrow;

   }



   void view::pica_to_margin()
   {

      for (auto & pic : m_pdata->m_pica)
      {

         if (pic->m_ppic->m_rectBounding.intersects(m_pdata->m_rectClient))
         {

            pic->m_ppic->m_rect._001Constraint(m_pdata->m_rectClient, pic->m_ppic->m_rectBounding);

            pic->update_drawing_rect(m_pdata->m_sizePage, get_size());

            pic->update_region();

            pic->update_placement();

         }

      }

   }


   ::user::rich_text::edit * view::create_rich_text_edit(point pt)
   {

      ::user::rich_text::edit * pedit  = new ::user::rich_text::edit(get_app());

      pedit->enable_pic();

      pedit->create_color(::user::color_background, ARGB(0, 0, 0, 0));
      pedit->create_color(::user::color_border, ARGB(0, 0, 0, 0));

      pedit->create_window(rect(pt, ::size(128, 128)), this, string("edit_") + ::str::from(m_pdata->m_pica.get_count()));
      dereference_no_delete(pedit);

      return pedit;

   }


   void view::on_control_event(::user::control_event * pevent)
   {

      if (pevent->m_eevent == ::user::event_after_change_text
            || pevent->m_eevent == ::user::event_after_change_text_format)
      {

         if (::str::begins_ci(pevent->m_id, "edit_"))
         {

            save();

            pevent->m_bRet = true;

            return;

         }

      }

      ::user::impact::on_control_event(pevent);

   }


   void view::_001HideEditingControls()
   {

      if (m_picName.is_set())
      {

         m_picName->ShowWindow(SW_HIDE);

      }

   }


   bool view::is_tool_editing_text()
   {

      if (m_picName == m_pdata->m_picCurrent)
      {

         return false;

      }

      if (m_pdata->m_picCurrent.is_set() && !m_pdata->m_picCurrent->is_text_editor())
      {

         if (m_pdata->m_pictool->m_etoolMode == ::composite::tool_edit_text)
         {

            m_pdata->m_pictool->m_etoolMode = ::composite::tool_none;

         }

      }

      bool bEditable = m_pdata->m_pictool->m_etoolMode == ::composite::tool_edit_text;

      if (m_pdata->m_picCurrent.is_set()
            && is_different(bEditable, m_pdata->m_picCurrent->is_text_editable()))
      {

         sp(user::rich_text::edit) pedit = m_pdata->m_picCurrent;

         if (pedit.is_set())
         {

            pedit->set_text_editable(bEditable);

            if (bEditable)
            {

               SetFocus();

            }

         }

      }

      return bEditable;

   }


} // namespace composite



