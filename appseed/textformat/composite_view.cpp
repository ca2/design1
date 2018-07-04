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
      m_sizePagePrev(0, 0)
   {

      m_sizeMaxPicAdjust.set(256);

      m_bAutoAdjustPicSize = true;

      m_bEnablePastePicture = false;

      m_eelementDrag = ::user::element_none;

      m_rectMargin.set(0);
      m_rectMaxMarginDrawing.set(0);
      m_rectMarginDrawing.set(0);

      m_dAspect = 3.0 / 4.0;

      /*
      m_flagNonClient.unsignalize(non_client_background);
      m_flagNonClient.unsignalize(non_client_focus_rect);
      */

      m_bHelloLayoutOn001Layout = false;

      m_b001LayoutIgnoreEmpty = false;

      m_bHelloLayoutOn001Layout = true;

      m_b001LayoutIgnoreEmpty = false;

      m_pictool = canew(pic_tool);

      m_pictool->m_map[pic_tool::tool_rotate].m_dib = Application.get_matter_dib("pictool/rotation24.png");
      m_pictool->m_map[pic_tool::tool_crop].m_dib = Application.get_matter_dib("pictool/crop-icon24.png");
      m_pictool->m_map[pic_tool::tool_close].m_dib = Application.get_matter_dib("pictool/close-button24.png");
      m_pictool->m_map[pic_tool::tool_stack_up].m_dib = Application.get_matter_dib("pictool/stackup24.png");
      m_pictool->m_map[pic_tool::tool_special_effect].m_dib = Application.get_matter_dib("pictool/fx24.png");
      m_pictool->m_map[pic_tool::tool_stack_down].m_dib = Application.get_matter_dib("pictool/stackdown24.png");
      m_pictool->m_map[pic_tool::tool_resize].m_dib = Application.get_matter_dib("pictool/resize20.png");

      m_pictool->m_map[pic_tool::tool_zoom_out].m_dib = Application.get_matter_dib("pictool/zoomout24.png");
      m_pictool->m_map[pic_tool::tool_zoom_in].m_dib = Application.get_matter_dib("pictool/zoomin24.png");
      m_pictool->m_map[pic_tool::tool_move].m_dib = Application.get_matter_dib("pictool/drag24.png");
      m_pictool->m_map[pic_tool::tool_apply].m_dib = Application.get_matter_dib("pictool/apply24.png");

      m_pictool->m_map[pic_tool::tool_resize].m_ecursor = visual::cursor_size_bottom_right;

      m_pictool->m_penBorder.alloc(allocer());
      m_pictool->m_penBorder->create_solid(1.0, ARGB(190, 80, 120, 200));
      m_pictool->m_penBorder->m_etype = ::draw2d::pen::type_dash;

      m_pictool->m_pview = this;

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


   void view::_001OnTimer(::timer * ptimer)
   {

      if (ptimer->m_nIDEvent == timer_drag)
      {

         KillTimer(timer_drag);

         if (m_picCurrent.is_set())
         {

            m_picCurrent->m_ppic->m_bDrag = true;

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

      m_pictool->m_etoolMode = pic_tool::tool_none;


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

      if (m_picCurrent.is_set() && m_picCurrent->is_dragging())
      {

         pmouse->m_bRet = true;

      }
      else if (m_picCurrent.is_set() && (iHit = m_picCurrent->hit_test_cursor(pt)) >= 0)
      {

         m_pictool->hit_test(m_etoolDown, pt);

         if (m_etoolDown == pic_tool::tool_none && iHit == 0)
         {

            m_picCurrent->m_ppic->m_bDrag = true;

            ::rectd r(m_picCurrent->m_ppic->m_rect);

            ClientToScreen(r);

            m_ptEditCursorOffset = pointd(pmouse->m_pt);

            if (m_pictool->m_etoolMode == pic_tool::tool_move)
            {

               ScreenToClient(m_ptEditCursorOffset);

               m_picCurrent->drag_rtransform_point(m_ptEditCursorOffset);

               m_ptEditCursorOffset = m_ptEditCursorOffset - sized(m_picCurrent->m_ppic->m_ptDrag.x * m_picCurrent->m_ppic->m_rect.width(),
                                      m_picCurrent->m_ppic->m_ptDrag.y * m_picCurrent->m_ppic->m_rect.height());

            }
            else
            {

               m_ptEditCursorOffset -= r.top_left();

            }

            pmouse->m_bRet = true;

         }
         else
         {

            m_pictool->m_map[m_etoolDown].m_bDrag = true;

            m_pictool->m_ptCenter = m_picCurrent->m_ppic->m_rect.center();

            pmouse->m_ecursor = m_pictool->m_map[m_etoolDown].m_ecursor;

            pmouse->m_bRet = true;

            if (m_etoolDown == pic_tool::tool_rotate)
            {

               m_dStartAngle = atan2((double)(m_pictool->m_ptCenter.y - pt.y), (double)(m_pictool->m_ptCenter.x - pt.x)) - m_picCurrent->m_ppic->m_dRotate;

            }
            else if (m_etoolDown == pic_tool::tool_resize)
            {

               m_pictool->m_ptResizeOrigin = m_picCurrent->m_ppic->m_rect.top_left();

               m_picCurrent->_transform_point(m_pictool->m_ptResizeOrigin);

            }

         }

      }
      else
      {

         {


            for (auto & pic : m_pica)
            {

               if (pic->hit_test(pt) >= 0)
               {

                  pmouse->m_ecursor = ::visual::cursor_move;

                  m_ptEditCursorOffset = pt - pic->m_ppic->m_rect.top_left();

                  m_picCurrent = pic;

                  on_pic_update();

                  m_picCurrent->m_ppic->m_bDrag = true;

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

               if (m_picCurrent.is_set())
               {

                  m_picCurrent.release();

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

                  sp(::user::rich_text::edit) pedit = canew(::user::rich_text::edit(get_app()));

                  pedit->enable_pic();

                  pedit->create_color(::user::color_background, ARGB(0, 0, 0, 0));
                  pedit->create_color(::user::color_border, ARGB(0, 0, 0, 0));

                  pedit->create_window(rect(pt, ::size(128, 128)), this, string("edit_") + ::str::from(m_pica.get_count()));

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

         m_rectMargin.top = pt.y;

         set_need_layout();

         set_need_redraw();

         pmouse->m_bRet = true;

      }
      else if (m_eelementDrag == ::user::element_margin_left)
      {

         m_rectMargin.left = pt.x;

         set_need_layout();

         set_need_redraw();

         pmouse->m_bRet = true;

      }
      else if (m_eelementDrag == ::user::element_margin_right)
      {

         m_rectMargin.right = pt.x;

         set_need_layout();

         set_need_redraw();

         pmouse->m_bRet = true;

      }
      else if (m_eelementDrag == ::user::element_margin_bottom)
      {

         m_rectMargin.bottom = pt.y;

         set_need_layout();

         set_need_redraw();

         pmouse->m_bRet = true;

      }

      if (m_pictool.is_set() && m_etoolDown != pic_tool::tool_none)
      {

         m_pictool->m_map[m_etoolDown].m_bDrag = false;

      }

      if (m_picCurrent.is_set() && m_picCurrent->is_dragging())
      {

         if (m_pictool->m_etoolMode == pic_tool::tool_move)
         {

            pointd pt = pmouse->m_pt;

            ScreenToClient(&pt);

            m_picCurrent->drag_rtransform_point(pt);

            pt -= m_ptEditCursorOffset;

            m_picCurrent->m_ppic->m_ptDrag = pointd(pt.x / m_picCurrent->m_ppic->m_rect.width(), pt.y / m_picCurrent->m_ppic->m_rect.height());

            m_pictool->m_etoolMode = pic_tool::tool_crop;

         }
         else
         {

            pointd pt = pmouse->m_pt;

            pt -= m_ptEditCursorOffset;

            ScreenToClient(&pt);

            m_picCurrent->move_to(pt, m_sizePage, get_size(), m_rectClient);

         }

         m_picCurrent->m_ppic->m_bDrag = false;

         pmouse->m_bRet = true;

         set_need_layout();

         set_need_redraw();

      }
      else if (m_picCurrent.is_set() && m_picCurrent->hit_test_cursor(pt) >= 0)
      {

         pic_tool::e_tool etool;

         m_pictool->hit_test(etool, pt);

         if (etool == m_etoolDown && etool != pic_tool::tool_none)
         {

            switch (etool)
            {
            case pic_tool::tool_crop:
            {

               m_pictool->m_etoolMode = pic_tool::tool_crop;

            }
            break;
            case pic_tool::tool_move:
            {

               ASSERT(m_pictool->m_etoolMode == pic_tool::tool_crop || m_pictool->m_etoolMode == pic_tool::tool_move);

               m_pictool->m_etoolMode = pic_tool::tool_move;

            }
            break;
            case pic_tool::tool_apply:
            {

               ASSERT(m_pictool->m_etoolMode == pic_tool::tool_crop || m_pictool->m_etoolMode == pic_tool::tool_move);

               if (m_pictool->m_etoolMode == pic_tool::tool_crop
                     || m_pictool->m_etoolMode == pic_tool::tool_move)
               {

                  m_pictool->m_etoolMode = pic_tool::tool_none;

               }

            }
            break;
            case pic_tool::tool_zoom_in:
            {

               ASSERT(m_pictool->m_etoolMode == pic_tool::tool_crop || m_pictool->m_etoolMode == pic_tool::tool_move);

               if (m_pictool->m_etoolMode == pic_tool::tool_move)
               {

                  m_pictool->m_etoolMode = pic_tool::tool_crop;

               }

               m_picCurrent->m_ppic->m_dZoom *= 1.1;

            }
            break;
            case pic_tool::tool_zoom_out:
            {

               if (m_pictool->m_etoolMode == pic_tool::tool_move)
               {

                  m_pictool->m_etoolMode = pic_tool::tool_crop;

               }

               ASSERT(m_pictool->m_etoolMode == pic_tool::tool_crop);

               m_picCurrent->m_ppic->m_dZoom /= 1.1;

            }
            break;
            case pic_tool::tool_close:
            {

               sp(::user::rich_text::edit) pedit = m_picCurrent;

               if (pedit.is_set())
               {

                  pedit->DestroyWindow();

               }

               if (m_pictool->m_etoolMode == pic_tool::tool_crop)
               {

                  m_pictool->m_etoolMode = pic_tool::tool_none;

               }
               else
               {

                  m_pica.remove(m_picCurrent);

                  m_picCurrent.release();

                  set_need_redraw();

               }

            }

            break;

            case pic_tool::tool_stack_up:
            {

               index iFind = m_pica.find_first(m_picCurrent);

               if (iFind >= 0)
               {

                  rectd rIntersect;

                  index iFound = -1;

                  for (index i = iFind + 1; i < m_pica.get_count(); i++)
                  {

                     if (rIntersect.intersect(m_picCurrent->m_ppic->m_rect, m_pica[i]->m_ppic->m_rect))
                     {

                        iFound = i;

                        break;

                     }

                  }

                  if (iFound < 0)
                  {

                     iFound = iFind + 1;

                  }

                  if (iFound < m_pica.get_count())
                  {

                     m_pica.remove_at(iFind);

                     m_pica.insert_at(iFound, m_picCurrent);

                  }

                  on_pic_update();

               }

            }
            break;

            case pic_tool::tool_stack_down:
            {

               index iFind = m_pica.find_first(m_picCurrent);

               if (iFind >= 0)
               {

                  rectd rIntersect;

                  index iFound = -1;

                  for (index i = iFind - 1; i >= 0; i--)
                  {

                     if (rIntersect.intersect(m_picCurrent->m_ppic->m_rect, m_pica[i]->m_ppic->m_rect))
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

                     m_pica.remove_at(iFind);

                     m_pica.insert_at(iFound, m_picCurrent);

                  }

                  on_pic_update();

               }

            }
            break;

            default:;

            }

         }

         set_need_redraw();

         pmouse->m_bRet = true;

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

         m_rectMargin.top = pt.y;

         set_need_layout();

         set_need_redraw();

         pmouse->m_bRet = true;

      }
      else if (m_eelementDrag == ::user::element_margin_left)
      {

         pmouse->m_ecursor = visual::cursor_size_left;

         m_rectMargin.left = pt.x;

         set_need_layout();

         set_need_redraw();

         pmouse->m_bRet = true;

      }
      else if (m_eelementDrag == ::user::element_margin_right)
      {

         pmouse->m_ecursor = visual::cursor_size_right;

         m_rectMargin.right = pt.x;

         set_need_layout();

         set_need_redraw();

         pmouse->m_bRet = true;

      }
      else if (m_eelementDrag == ::user::element_margin_bottom)
      {

         pmouse->m_ecursor = visual::cursor_size_bottom;

         m_rectMargin.bottom = pt.y;

         set_need_layout();

         set_need_redraw();

         pmouse->m_bRet = true;

      }
      else if (m_picCurrent.is_set()
               && m_picCurrent->is_valid()
               && m_pictool.is_set() && m_etoolDown != pic_tool::tool_none
               && m_pictool->m_map[m_etoolDown].m_bDrag)
      {

         pmouse->m_ecursor = m_pictool->m_map[m_etoolDown].m_ecursor;

         if (m_etoolDown == pic_tool::tool_rotate)
         {

            m_picCurrent->m_ppic->m_dRotate = atan2(
                                              (double)(m_pictool->m_ptCenter.y - pt.y),
                                              (double)(m_pictool->m_ptCenter.x - pt.x)) - m_dStartAngle;

            m_picCurrent->update_region();

            set_need_layout();

            set_need_redraw();

         }
         else if (m_etoolDown == pic_tool::tool_resize)
         {

            double a = sin(m_picCurrent->m_ppic->m_dRotate);

            double b = cos(m_picCurrent->m_ppic->m_dRotate);

            double x1 = m_pictool->m_ptResizeOrigin.x;

            double y1 = m_pictool->m_ptResizeOrigin.y;

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

            m_picCurrent->m_ppic->m_rect.left = x - dx;

            m_picCurrent->m_ppic->m_rect.top = y - dy;

            m_picCurrent->m_ppic->m_rect.right = x + dx;

            m_picCurrent->m_ppic->m_rect.bottom = y + dy;


            //sizeNew.cx = MAX(sizeMin.cx, sizeNew.cx);

            //sizeNew.cy = MAX(sizeMin.cy, sizeNew.cy);

            //m_picCurrent->m_ppic->m_rect.set_size(sizeNew);

            m_picCurrent->update_drawing_rect(m_sizePage, get_size());

            m_picCurrent->update_region();

            m_picCurrent->update_placement();

            set_need_layout();

            set_need_redraw();

         }

      }
      else if (m_picCurrent.is_set() && m_picCurrent->is_dragging())
      {

         if (m_pictool->m_etoolMode == pic_tool::tool_move)
         {

            pointd pt = pmouse->m_pt;

            ScreenToClient(&pt);

            m_picCurrent->drag_rtransform_point(pt);

            pt -= m_ptEditCursorOffset;

            m_picCurrent->m_ppic->m_ptDrag = pointd(pt.x / m_picCurrent->m_ppic->m_rect.width(), pt.y / m_picCurrent->m_ppic->m_rect.height());

         }
         else
         {

            pointd pt = pmouse->m_pt;

            pt -= m_ptEditCursorOffset;

            ScreenToClient(&pt);

            m_picCurrent->move_to(pt, m_sizePage, get_size(), m_rectClient);

            pica_to_margin();

         }

         pmouse->m_bRet = true;

         pmouse->m_ecursor = ::visual::cursor_move;

         set_need_layout();

         set_need_redraw();

      }
      else
      {

         for (auto & pic : m_pica)
         {

            if (pic == m_picCurrent)
            {

               int iHit = m_picCurrent->hit_test_cursor(pt);

               if (iHit >= 0)
               {

                  pic_tool::e_tool etool;

                  m_pictool->hit_test(etool, pt);

                  if (etool == pic_tool::tool_none && iHit == 0)
                  {

                     pmouse->m_ecursor = ::visual::cursor_move;

                     pmouse->m_bRet = true;

                     break;

                  }
                  else
                  {

                     pmouse->m_ecursor = m_pictool->m_map[etool].m_ecursor;

                     pmouse->m_bRet = true;

                     break;

                  }

               }


            }
            else if (pic->hit_test(pt) >= 0)
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


   void view::_001OnDrawPic(::draw2d::graphics * pgraphics)
   {

      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

      for (auto & pic : m_pica)
      {

         if (pic.is_set() && pic->is_valid())
         {

            pic->draw(pgraphics);

         }

      }

      if (m_picCurrent.is_set() && m_picCurrent->is_valid())
      {

         {

            ::draw2d::savedc savedc(pgraphics);

            ::draw2d::matrix mRot;

            mRot.append(::draw2d::matrix::rotation(m_picCurrent->m_ppic->m_dRotate));

            pgraphics->prepend(mRot);

            ::draw2d::matrix mTrans;

            mTrans.append(::draw2d::matrix::translation(m_picCurrent->m_ppic->m_rect.center().x, m_picCurrent->m_ppic->m_rect.center().y));

            pgraphics->append(mTrans);

            //pgraphics->draw(m_picCurrent->m_ppic->m_rect, m_picCurrent->m_ppic->m_dib->g(), rect(m_picCurrent->m_ppic->m_dib->m_size));

            m_pictool->draw(pgraphics);

         }

         m_picCurrent->m_ppic->m_rectCursor.offset(m_picCurrent->m_ppic->m_rect.center());

      }

      pgraphics->draw_rect(m_rectMargin, m_pictool->m_penBorder);

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

      double dx = (double)m_sizePage.cx / (double)width();

      double dy = (double)m_sizePage.cy / (double)height();

      m_rectClient = rectClient;

      if (m_sizePagePrev.area() <= 0 || m_rectMargin.is_null())
      {

         m_rectMarginDrawing.set(null_pointd(), pointd(m_sizePage));

      }

      if (m_sizePagePrev != m_sizePage)
      {

         if (m_sizePagePrev.area() > 0)
         {

            double dxRate = (double)m_sizePage.cx / (double)m_sizePagePrev.cx;
            double dyRate = (double)m_sizePage.cy / (double)m_sizePagePrev.cy;

            m_rectMarginDrawing.left *= dxRate;
            m_rectMarginDrawing.top *= dyRate;
            m_rectMarginDrawing.right *= dxRate;
            m_rectMarginDrawing.bottom *= dyRate;

         }

         m_rectMaxMarginDrawing.left = m_sizePage.cx / 70;
         m_rectMaxMarginDrawing.top = m_sizePage.cy / 70;
         m_rectMaxMarginDrawing.right = m_sizePage.cx - m_sizePage.cx / 70;
         m_rectMaxMarginDrawing.bottom = m_sizePage.cy - m_sizePage.cy / 70;

         m_sizePagePrev = m_sizePage;

      }

      if (m_rectMarginPrev != m_rectMargin)
      {

         m_rectMarginDrawing.left = m_rectMargin.left * dx;
         m_rectMarginDrawing.top = m_rectMargin.top * dy;
         m_rectMarginDrawing.right = m_rectMargin.right * dx;
         m_rectMarginDrawing.bottom = m_rectMargin.bottom * dy;

      }

      m_rectMarginDrawing.intersect(m_rectMaxMarginDrawing);

      m_rectMargin.left = m_rectMarginDrawing.left / dx;
      m_rectMargin.top = m_rectMarginDrawing.top / dy;
      m_rectMargin.right = m_rectMarginDrawing.right / dx;
      m_rectMargin.bottom = m_rectMarginDrawing.bottom / dy;

      m_rectMarginPrev = m_rectMargin;

   }


   void view::defer_check_on_draw_layout()
   {

   }


   void view::set_background(::file::path path)
   {

      ::visual::dib_sp dib(allocer());

      if (dib.load_from_file(path, false))
      {

         m_dibBackground = dib;

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

      m_picCurrent = ppic;

      m_pica.add(m_picCurrent);

      on_pic_update();

      m_ptEditCursorOffset = ppic->m_ppic->m_rect.get_size()/2;

#ifdef WINDOWSEX

      point ptCursor(ppic->m_ppic->m_rect.center() + client_to_screen());

      ::SetCursorPos(ptCursor.x, ptCursor.y);

#endif

      m_picCurrent->m_ppic->m_bDrag = true;

   }


   void view::on_draw_image_layer(::draw2d::graphics * pgraphics)
   {


   }




   bool view::pic_tool::get_tool_rect(LPRECTD lprect, e_tool etool)
   {

      ::user::pic * pic = m_pview->m_picCurrent;

      rectd rPic = pic->m_ppic->m_rect;

      rectd rectDib;

      if ((int)etool <= 0 || (int)etool >= tool_count)
      {

         return false;

      }
      else
      {

         if (etool >= tool_zoom_out && etool <= tool_apply)
         {

            if (m_etoolMode != tool_crop && m_etoolMode != tool_move)
            {

               return false;

            }

         }
         else if (etool != tool_close)
         {

            if (m_etoolMode == tool_crop || m_etoolMode == tool_move)
            {

               return false;

            }

         }

         tool & tool = m_map[etool];

         rectDib = sized(tool.m_dib->m_size);

         rectDib._001Align(tool.m_ptAlign.x, tool.m_ptAlign.y, rPic);

         *lprect = rectDib;

         return true;

      }

   }


   bool view::pic_tool::hit_test(e_tool & etool, pointd pt)
   {

      rectd r;

      ::user::pic * pic = m_pview->m_picCurrent;

      pic->_rtransform_point(pt);

      for (etool = (e_tool)1; etool < tool_count; ((int &)etool)++)
      {

         if (get_tool_rect(r, etool))
         {

            if (r.contains(pt))
            {

               return true;

            }

         }

      }

      etool = tool_none;

      return false;

   }


   void view::on_pic_update()
   {

      sp(view::pic) ppic = m_picCurrent;

      if (ppic.is_set())
      {

         m_pictool->m_map[pic_tool::tool_rotate].m_ptAlign.SetPoint(-1.0, -1.0);
         m_pictool->m_map[pic_tool::tool_crop].m_ptAlign.SetPoint(0.0, -1.0);
         m_pictool->m_map[pic_tool::tool_close].m_ptAlign.SetPoint(1.0, -1.0);
         m_pictool->m_map[pic_tool::tool_stack_up].m_ptAlign.SetPoint(-0.75, 1.0);
         m_pictool->m_map[pic_tool::tool_special_effect].m_ptAlign.SetPoint(0.0, 1.0);
         m_pictool->m_map[pic_tool::tool_resize].m_ptAlign.SetPoint(1.0, 1.0);
         m_pictool->m_map[pic_tool::tool_stack_down].m_ptAlign.SetPoint(0.75, 1.0);
         m_pictool->m_map[pic_tool::tool_zoom_out].m_ptAlign.SetPoint(-1.0, -1.0);
         m_pictool->m_map[pic_tool::tool_move].m_ptAlign.SetPoint(-0.33, -1.0);
         m_pictool->m_map[pic_tool::tool_zoom_in].m_ptAlign.SetPoint(0.33, -1.0);
         m_pictool->m_map[pic_tool::tool_apply].m_ptAlign.SetPoint(0.0, -0.5);

      }
      else
      {

         m_pictool->m_map[pic_tool::tool_rotate].m_ptAlign.SetPoint(-1000.0, -1000.0);
         m_pictool->m_map[pic_tool::tool_crop].m_ptAlign.SetPoint(0.0, -1000.0);
         m_pictool->m_map[pic_tool::tool_close].m_ptAlign.SetPoint(1000.0, -1000.0);
         m_pictool->m_map[pic_tool::tool_stack_up].m_ptAlign.SetPoint(-1000.0, 1000.0);
         m_pictool->m_map[pic_tool::tool_special_effect].m_ptAlign.SetPoint(0.0, 1000.0);
         m_pictool->m_map[pic_tool::tool_resize].m_ptAlign.SetPoint(1.0, 1.0);
         m_pictool->m_map[pic_tool::tool_stack_down].m_ptAlign.SetPoint(1000.0, 1000.0);
         m_pictool->m_map[pic_tool::tool_zoom_out].m_ptAlign.SetPoint(-1000.0, -1000.0);
         m_pictool->m_map[pic_tool::tool_move].m_ptAlign.SetPoint(-0.75, -1001.0);
         m_pictool->m_map[pic_tool::tool_zoom_in].m_ptAlign.SetPoint(0.5, -1001.0);
         m_pictool->m_map[pic_tool::tool_apply].m_ptAlign.SetPoint(0.0, -1000.0);

      }

      index i = m_pica.find_first(m_picCurrent);

      if (i >= 0)
      {

         m_pictool->m_map[pic_tool::tool_stack_down].m_bEnable = i > 0;
         m_pictool->m_map[pic_tool::tool_stack_up].m_bEnable = i < m_pica.get_upper_bound();

      }

      pica_to_margin();

      for (auto & pic : m_pica)
      {

         pic->update_region();

      }

   }


   view::pic_tool::tool::tool()
   {

      m_bEnable = true;

      m_bDrag = false;

      m_ecursor = ::visual::cursor_arrow;

   }


   void view::pic_tool::draw(::draw2d::graphics * pgraphics)
   {

      ::user::pic * pic = m_pview->m_picCurrent;

      rect rPic(pic->m_ppic->m_rect);

      rect r;

      pic->reset_cursor_rect();

      if (m_etoolMode == tool_crop || m_etoolMode == tool_move)
      {

         draw_tool(pgraphics, tool_zoom_out);
         draw_tool(pgraphics, tool_move);
         draw_tool(pgraphics, tool_zoom_in);
         draw_tool(pgraphics, tool_apply);
         draw_tool(pgraphics, tool_close);

      }
      else
      {

         draw_tool(pgraphics, tool_rotate);
         draw_tool(pgraphics, tool_crop);
         draw_tool(pgraphics, tool_close);
         draw_tool(pgraphics, tool_stack_up);
         draw_tool(pgraphics, tool_special_effect);
         draw_tool(pgraphics, tool_stack_down);
         draw_tool(pgraphics, tool_resize);

      }

      rect rSel(rPic);

      rSel.inflate(2, 2);

      rSel.offset(-rPic.top_left() - rPic.get_size() / 2);

      pgraphics->draw_rect(rSel, m_penBorder);


   }

   void view::pic_tool::draw_tool(::draw2d::graphics * pgraphics, e_tool etool)
   {

      rectd r;

      get_tool_rect(r, etool);

      tool & tool = m_map[etool];

      ::user::pic * pic = m_pview->m_picCurrent;

      rectd rPic(pic->m_ppic->m_rect);

      r.offset(-rPic.top_left() - rPic.get_size() / 2.0);

      if (!tool.m_bEnable)
      {

         if (tool.m_dibDisable.is_null() || tool.m_dibDisable->area() <= 0)
         {

            tool.m_dibDisable = tool.m_dib->clone();

            tool.m_dibDisable->saturation(0.0);

         }

         pgraphics->draw(rect(r), tool.m_dibDisable->g(), rect(tool.m_dibDisable->m_size));

      }
      else
      {

         pgraphics->draw(rect(r), tool.m_dib->g(), rect(tool.m_dib->m_size));

      }

      if (pic->m_ppic->m_rectCursor.area() < 0)
      {

         pic->m_ppic->m_rectCursor = r;

      }
      else
      {

         pic->m_ppic->m_rectCursor.unite(pic->m_ppic->m_rectCursor, r);

      }

   }


   void view::pica_to_margin()
   {

      for (auto & pic : m_pica)
      {

         if (pic->m_ppic->m_rectBounding.intersects(m_rectClient))
         {

            pic->m_ppic->m_rect._001Constraint(m_rectClient, pic->m_ppic->m_rectBounding);

            pic->update_drawing_rect(m_sizePage, get_size());

            pic->update_region();

            pic->update_placement();

         }

      }

   }

   view::pic::pic(::aura::application * papp) :
      ::object(papp),
      ::user::pic(papp)
   {


   }


   bool view::pic::pic::is_valid()
   {

      return m_dib.is_set() && m_dib->area() > 0;

   }


   ::sized view::pic::pic::get_size()
   {

      return m_dib->m_size;

   }


   void view::pic::pic::draw(::draw2d::graphics * pgraphics)
   {

      ::draw2d::savedc savedc(pgraphics);

      ::draw2d::matrix mRot;

      rectd rClip(m_ppic->m_rect);

      pointd_array pta;

      pta.set_size(4);

      pta[0] = _transform(rClip.top_left());
      pta[1] = _transform(rClip.top_right());
      pta[2] = _transform(rClip.bottom_right());
      pta[3] = _transform(rClip.bottom_left());

      ::draw2d::region_sp rgn(allocer());

      rgn->create_polygon(pta.get_data(), (int) pta.get_count(), ::draw2d::fill_mode_winding);

      pgraphics->SelectClipRgn(rgn, RGN_AND);

      mRot.append(::draw2d::matrix::rotation(m_ppic->m_dRotate));
      
      pgraphics->prepend(mRot);

      pgraphics->prepend(::draw2d::matrix::scaling(m_ppic->m_dZoom, m_ppic->m_dZoom));

      ::draw2d::matrix mTrans;

      mTrans.append(::draw2d::matrix::translation(m_ppic->m_rect.center().x, m_ppic->m_rect.center().y));

      pgraphics->append(mTrans);

      rect r(-point(m_ppic->m_rect.get_size() / 2.0) +
             point(m_ppic->m_ptDrag.x * m_ppic->m_rect.width(),
                   m_ppic->m_ptDrag.y * m_ppic->m_rect.height()), ::size(m_ppic->m_rect.get_size()));

      pgraphics->draw(r, m_dib->g(), rect(m_dib->m_size));

   }




} // namespace composite



