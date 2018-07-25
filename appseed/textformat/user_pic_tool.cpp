#include "framework.h"


namespace composite
{


   pic_tool::pic_tool(::aura::application * papp)
   {

   }


   pic_tool::~pic_tool()
   {


   }


   bool pic_tool::get_tool_rect(LPRECTD lprect, e_tool etool, bool bDrawing)
   {

      ::user::pic * pic = m_pview->m_pdata->m_picCurrent;

      rectd rPic;

      if (bDrawing)
      {

         rPic = pic->m_ppic->m_rectDrawing;

      }
      else
      {

         rPic = pic->m_ppic->m_rect;

      }


      rectd rectDib;

      if ((int)etool <= 0 || (int)etool >= tool_count)
      {

         return false;

      }
      else
      {

         if (m_pview->is_tool_editing_text())
         {

            if (etool != tool_edit_text)
            {

               return false;

            }

         }
         else if (etool >= tool_zoom_out && etool <= tool_apply)
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

            if (pic->is_text_editor())
            {

               if (etool == tool_crop)
               {

                  return false;

               }

            }
            else
            {

               if (etool == tool_edit_text)
               {

                  return false;

               }

            }


         }

         tool & tool = m_map[etool];

         if (bDrawing)
         {

            rectDib = sized(tool.m_dib->m_size.cx *pic->m_ppic->m_rectDrawing.width() / pic->m_ppic->m_rect.width(),
                            tool.m_dib->m_size.cy *pic->m_ppic->m_rectDrawing.height() / pic->m_ppic->m_rect.height());


         }
         else
         {

            rectDib = sized(tool.m_dib->m_size);


         }

         rectDib._001Align(tool.m_ptAlign.x, tool.m_ptAlign.y, rPic);

         *lprect = rectDib;

         return true;

      }

   }


   bool pic_tool::hit_test(e_tool & etool, pointd pt)
   {

      rectd r;

      ::user::pic * pic = m_pview->m_pdata->m_picCurrent;

      if (pic == NULL)
      {

         return false;

      }

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


   void pic_tool::draw(::draw2d::graphics * pgraphics)
   {

      ::user::pic * pic = m_pview->m_pdata->m_picCurrent;

      rect rPic(pic->m_ppic->m_rectDrawing);

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
      else if (m_pview->is_tool_editing_text())
      {

         draw_tool(pgraphics, tool_edit_text);

      }
      else
      {

         draw_tool(pgraphics, tool_rotate);
         if (pic->is_text_editor())
         {
            draw_tool(pgraphics, tool_edit_text);
         }
         else
         {
            draw_tool(pgraphics, tool_crop);
         }
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


   void pic_tool::draw_tool(::draw2d::graphics * pgraphics, e_tool etool)
   {

      rectd r;

      get_tool_rect(r, etool, true);

      tool & tool = m_map[etool];

      ::user::pic * pic = m_pview->m_pdata->m_picCurrent;

      rectd rPic(pic->m_ppic->m_rectDrawing);

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

      get_tool_rect(r, etool, false);


      if (pic->m_ppic->m_rectCursor.area() < 0)
      {

         pic->m_ppic->m_rectCursor = r;

      }
      else
      {

         pic->m_ppic->m_rectCursor.unite(pic->m_ppic->m_rectCursor, r);

      }

   }



} // namespace composite




