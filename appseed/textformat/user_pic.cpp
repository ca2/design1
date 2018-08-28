#include "framework.h"
#include <math.h>


property & operator << (property & property, const RECTD & r)
{

   property["left"] = r.left;
   property["top"] = r.top;
   property["right"] = r.right;
   property["bottom"] = r.bottom;

   return property;

}

property & operator >> (property & property, RECTD & r)
{

   r.left = property["left"];
   r.top = property["top"];
   r.right = property["right"];
   r.bottom = property["bottom"];

   return property;

}




//https://rbrundritt.wordpress.com/2008/10/20/approximate-points-of-intersection-of-two-line-segments/
//latlong1 and latlong2 represent two coordinates that make up the bounded box
//latlong3 is a point that we are checking to see is inside the box
inline bool inBoundedBox(pointd pt1, pointd pt2, pointd pt3)
{

   double dSpan = 0.01;

   if (pt1.x < pt2.x)
   {

      if (!(pt1.x <= pt3.x + dSpan && pt2.x + dSpan >= pt3.x))
      {

         return false;

      }

   }
   else
   {

      if (!(pt1.x + dSpan >= pt3.x && pt2.x <= pt3.x + dSpan))
      {

         return false;

      }

   }

   if (pt1.y < pt2.y)
   {

      return pt1.y <= pt3.y + dSpan && pt2.y + dSpan >= pt3.y;

   }
   else
   {

      return pt1.y + dSpan >= pt3.y && pt2.y <=  pt3.y + dSpan;

   }


}

//https://rbrundritt.wordpress.com/2008/10/20/approximate-points-of-intersection-of-two-line-segments/
bool line_intersection(pointd & pt, pointd pt1, pointd pt2, pointd pt3, pointd pt4)
{

   //Line segment 1 (p1, p2)
   double A1 = pt2.x - pt1.x;
   double B1 = pt1.y - pt2.y;
   double C1 = A1 * pt1.y + B1 * pt1.x;

   //Line segment 2 (p3,  p4)
   double A2 = pt4.x - pt3.x;
   double B2 = pt3.y - pt4.y;
   double C2 = A2 * pt3.y + B2 * pt3.x;

   double determinate = A1 * B2 - A2 * B1;

   if (determinate != 0.0)
   {

      pt.y = (B2*C1 - B1 * C2) / determinate;

      pt.x = (A1*C2 - A2 * C1) / determinate;

      return inBoundedBox(pt1, pt2, pt) && inBoundedBox(pt3, pt4, pt);

   }

   // lines are parallel;
   return false;

}

//https://rbrundritt.wordpress.com/2008/10/20/determine-if-two-polygons-overlap/
bool overlaps(const pointd_array & poly1, const pointd_array & poly2)
{

   if (poly1.get_count() >= 3 && poly2.get_count() >= 3)
   {

      ::count c1 = poly1.get_count();

      ::count c2 = poly2.get_count();

      pointd pt;

      for (int i = 0; i < c1; i++)
      {

         for (int k = 0; k < c2; k++)
         {

            if (line_intersection(pt, poly1[i], poly1[(i + 1) % c1], poly2[k], poly2[(k + 1) % c2]))
            {

               return true;

            }

         }

      }

      for (int i = 0; i < c1; i++)
      {

         if (poly2.polygon_contains(poly1[i]))
         {

            return true;

         }

      }

      for (int i = 0; i < c2; i++)
      {

         if (poly1.polygon_contains(poly2[i]))
         {

            return true;

         }

      }

   }

   return false;

}



namespace user
{


   pic::pic(::aura::application * papp) :
      object(papp)
   {

      m_ppic = NULL;

      reset_cursor_rect();

   }


   pic::~pic()
   {

      enable_pic(false);

   }


   bool pic::is_pic_enabled() const
   {

      return m_ppic != NULL;

   }


   pic::pic_impl::pic_impl()
   {
      m_dZoom = 1.0;
      m_ptDrag.x = 0.0;
      m_ptDrag.y = 0.0;


      m_bOutline = false;
      m_iOutlineWidth = 7;
      m_hlsOutline.m_dH = 0.0;
      m_hlsOutline.m_dL = 0.0;
      m_hlsOutline.m_dS = 0.0;

      m_bGlowDropShadow = false;
      m_iGlowDropShadowOffset = 12;
      m_iGlowDropShadowBlur = 4;
      m_hlsGlowDropShadow.m_dH = 0.0;
      m_hlsGlowDropShadow.m_dL = 0.0;
      m_hlsGlowDropShadow.m_dS = 0.0;

      m_iBlur = 0;
      m_bGrayscale = false;
      m_bInvert = false;
      m_iOpacity = 100;
      m_iSaturation = 100;

   }


   bool pic::enable_pic(bool bEnable)
   {

      if (bEnable)
      {

         if (m_ppic == NULL)
         {

            m_ppic = new pic_impl;

         }

      }
      else
      {

         if (m_ppic != NULL)
         {

            delete m_ppic;

         }

      }

      return true;

   }


   int pic::hit_test(pointd pt) const
   {

      ASSERT(is_pic_enabled());

      _rtransform_point(pt);

      if (m_ppic->m_rect.contains(pt))
      {

         return 0;

      }

      return -1;

   }


   pointd pic::_transform(const pointd & p) const
   {

      pointd pt(p);

      _transform_point(pt);

      return pt;

   }


   pointd pic::_transform_drawing(const pointd & p) const
   {

      pointd pt(p);

      _transform_point_drawing(pt);

      return pt;

   }


   void pic::_transform_point(pointd & pt) const
   {

      if (m_ppic == NULL)
      {

         return;

      }

      ::draw2d::matrix m;

      m.translate(-m_ppic->m_rect.center());

      m.rotate(m_ppic->m_dRotate);

      m.translate(m_ppic->m_rect.center());

      m.transform(pt);

   }


   void pic::_transform_point_drawing(pointd & pt) const
   {

      if (m_ppic == NULL)
      {

         return;

      }

      ::draw2d::matrix m;

      m.translate(-m_ppic->m_rectDrawing.center());

      m.rotate(m_ppic->m_dRotate);

      m.translate(m_ppic->m_rectDrawing.center());

      m.transform(pt);

   }

   pointd pic::_rtransform(const pointd & p) const
   {

      pointd pt(p);

      _rtransform_point(pt);

      return pt;

   }


   pointd pic::_rtransform_drawing(const pointd & p) const
   {

      pointd pt(p);

      _rtransform_point_drawing(pt);

      return pt;

   }


   void pic::_rtransform_point(pointd & pt) const
   {

      if (m_ppic == NULL)
      {

         return;

      }

      ::draw2d::matrix m;

      m.translate(-m_ppic->m_rect.center());

      m.rotate(-m_ppic->m_dRotate);

      m.translate(m_ppic->m_rect.center());

      m.transform(pt);

   }


   void pic::_rtransform_point_drawing(pointd & pt) const
   {

      if (m_ppic == NULL)
      {

         return;

      }

      ::draw2d::matrix m;

      m.translate(-m_ppic->m_rectDrawing.center());

      m.rotate(-m_ppic->m_dRotate);

      m.translate(m_ppic->m_rectDrawing.center());

      m.transform(pt);

   }


   pointd pic::drag_transform(const pointd & p) const
   {

      pointd pt(p);

      drag_transform_point(pt);

      return pt;

   }


   pointd pic::drag_transform_drawing(const pointd & p) const
   {

      pointd pt(p);

      drag_transform_point_drawing(pt);

      return pt;

   }


   void pic::drag_transform_point(pointd & pt) const
   {

      if (m_ppic == NULL)
      {

         return;

      }

      ::draw2d::matrix m;

      m.translate(-m_ppic->m_rect.center());

      m.rotate(m_ppic->m_dRotate);

      m.scale(m_ppic->m_dZoom, m_ppic->m_dZoom);

      m.translate(m_ppic->m_rect.center());

      m.transform(pt);

   }


   void pic::drag_transform_point_drawing(pointd & pt) const
   {

      if (m_ppic == NULL)
      {

         return;

      }

      ::draw2d::matrix m;

      m.translate(-m_ppic->m_rectDrawing.center());

      m.rotate(m_ppic->m_dRotate);

      m.scale(m_ppic->m_dZoom, m_ppic->m_dZoom);

      m.translate(m_ppic->m_rectDrawing.center());

      m.transform(pt);

   }

   pointd pic::drag_rtransform(const pointd & p) const
   {

      pointd pt(p);

      drag_rtransform_point(pt);

      return pt;

   }


   pointd pic::drag_rtransform_drawing(const pointd & p) const
   {

      pointd pt(p);

      drag_rtransform_point_drawing(pt);

      return pt;

   }


   void pic::drag_rtransform_point(pointd & pt) const
   {

      if (m_ppic == NULL)
      {

         return;

      }

      ::draw2d::matrix m;

      m.translate(-m_ppic->m_rect.center());

      m.rotate(-m_ppic->m_dRotate);

      m.scale(1.0 / m_ppic->m_dZoom, 1.0 / m_ppic->m_dZoom);

      //m.translate(m_ppic->m_rect.center());

      m.transform(pt);

   }


   void pic::drag_rtransform_point_drawing(pointd & pt) const
   {

      if (m_ppic == NULL)
      {

         return;

      }

      ::draw2d::matrix m;

      m.translate(-m_ppic->m_rectDrawing.center());

      m.rotate(-m_ppic->m_dRotate);

      m.scale(1.0 / m_ppic->m_dZoom, 1.0 / m_ppic->m_dZoom);

      //m.translate(m_ppic->m_rectDrawing.center());

      m.transform(pt);

   }


   void pic::update_placement()
   {

   }


   void pic::update_drawing_rect(::sized sizePage, ::sized sizeClient)
   {

      ASSERT(is_pic_enabled());

      if (sizeClient.area() <= 0)
      {

         m_ppic->m_rectDrawing = m_ppic->m_rect;

      }
      else
      {

         m_ppic->m_rectDrawing.left = m_ppic->m_rect.left * sizePage.cx / sizeClient.cx;
         m_ppic->m_rectDrawing.right = m_ppic->m_rect.right * sizePage.cx / sizeClient.cx;
         m_ppic->m_rectDrawing.top = m_ppic->m_rect.top * sizePage.cy / sizeClient.cy;
         m_ppic->m_rectDrawing.bottom = m_ppic->m_rect.bottom * sizePage.cy / sizeClient.cy;

      }

   }


   void pic::update_region()
   {

      ASSERT(is_pic_enabled());

      m_ppic->m_ptaDrawing.set_size(4);

      m_ppic->m_ptaDrawing[0] = _transform_drawing(m_ppic->m_rectDrawing.top_left());
      m_ppic->m_ptaDrawing[1] = _transform_drawing(m_ppic->m_rectDrawing.top_right());
      m_ppic->m_ptaDrawing[2] = _transform_drawing(m_ppic->m_rectDrawing.bottom_right());
      m_ppic->m_ptaDrawing[3] = _transform_drawing(m_ppic->m_rectDrawing.bottom_left());

      m_ppic->m_pta.set_size(4);

      m_ppic->m_pta[0] = _transform(m_ppic->m_rect.top_left());
      m_ppic->m_pta[1] = _transform(m_ppic->m_rect.top_right());
      m_ppic->m_pta[2] = _transform(m_ppic->m_rect.bottom_right());
      m_ppic->m_pta[3] = _transform(m_ppic->m_rect.bottom_left());

      m_ppic->m_rectBounding.left = m_ppic->m_pta[0].x;
      m_ppic->m_rectBounding.top = m_ppic->m_pta[0].y;
      m_ppic->m_rectBounding.right = m_ppic->m_pta[0].x;
      m_ppic->m_rectBounding.bottom = m_ppic->m_pta[0].y;

      for (index i = 1; i < 4; i++)
      {

         m_ppic->m_rectBounding.left = MIN(m_ppic->m_rectBounding.left, m_ppic->m_pta[i].x);
         m_ppic->m_rectBounding.right = MAX(m_ppic->m_rectBounding.right, m_ppic->m_pta[i].x);
         m_ppic->m_rectBounding.top = MIN(m_ppic->m_rectBounding.top, m_ppic->m_pta[i].y);
         m_ppic->m_rectBounding.bottom = MAX(m_ppic->m_rectBounding.bottom, m_ppic->m_pta[i].y);

      }

   }


   ::draw2d::region_sp pic::get_region() const
   {

      if (m_ppic->m_region.is_null())
      {

         ((pic*)this)->update_region();

      }

      return m_ppic->m_region;

   }


   bool pic::intersects(LPCRECTD lpcrect) const
   {

      rectd r(lpcrect);

      pointd_array pta;

      pta.set_size(4);

      pta[0] = r.top_left();
      pta[1] = r.top_right();
      pta[2] = r.bottom_right();
      pta[3] = r.bottom_left();

      if (m_ppic->m_pta.get_size() <= 0)
      {

         ((pic*)this)->update_region();

      }

      return overlaps(pta, m_ppic->m_pta);

   }


   bool pic::intersects_drawing(LPCRECTD lpcrect) const
   {

      ASSERT(is_pic_enabled());

      rectd r(lpcrect);

      pointd_array pta;

      pta.set_size(4);

      pta[0] = r.top_left();
      pta[1] = r.top_right();
      pta[2] = r.bottom_right();
      pta[3] = r.bottom_left();

      if (m_ppic->m_ptaDrawing.get_size() <= 0)
      {

         ((pic*)this)->update_region();

      }

      return overlaps(pta, m_ppic->m_ptaDrawing);

   }


   bool pic::is_valid()
   {

      return true;

   }


   ::sized pic::get_size()
   {

      return ::sized(128, 128);

   }


   bool pic::set_text_editable(bool bEditable)
   {

      return false;

   }


   bool pic::is_text_editable()
   {

      return false;

   }


   bool pic::is_text_editor()
   {

      return false;

   }


   void pic::reset_cursor_rect()
   {

      if (m_ppic == NULL)
      {

         return;

      }

      m_ppic->m_rectCursor.set(0, 0, -1, -1);

   }


   bool pic::is_dragging()
   {

      if (!is_valid())
      {

         return false;

      }

      if (!m_ppic->m_bDrag)
      {

         return false;

      }

      return true;

   }


   int pic::hit_test_cursor(pointd pt)
   {

      if (!is_valid())
      {

         return -1;

      }

      _rtransform_point(pt);

      if(m_ppic->m_rect.contains(pt))
      {

         return 0;

      }

      return -1;

   }


   ::draw2d::dib * pic::defer_draw_drop_shadow_phase1(rect & rDropShadow, ::visual::fastblur & dibDropShadow, ::draw2d::dib * pdib)
   {

      if (m_ppic->m_bGlowDropShadow)
      {

         double dBlur = (double)m_ppic->m_iGlowDropShadowBlur * (double)pdib->m_size.cx / (double)rDropShadow.width();

         int iBlur = ceil(dBlur);

         dibDropShadow.alloc(allocer());

         rect rDib(pdib->m_size);

         int iShift = iBlur * 2;

         rDib.inflate(iShift, iShift);

         rDropShadow.inflate(m_ppic->m_iGlowDropShadowBlur, m_ppic->m_iGlowDropShadowBlur);

         dibDropShadow.initialize(rDib.width(), rDib.height(), iBlur);

         dibDropShadow->Fill(0);

         dibDropShadow->g()->draw(rect(point(iShift, iShift), pdib->m_size), pdib->g());

         dibDropShadow->paint_rgb(m_ppic->m_hlsGlowDropShadow);

         dibDropShadow.blur();

      }

      return pdib;

   }

   void pic::defer_draw_drop_shadow_phase2(::draw2d::graphics * pgraphics, const rect & r, ::visual::fastblur & dibDropShadow)
   {

      if (m_ppic->m_bGlowDropShadow)
      {

         rect rDropShadow(r);

         rDropShadow.offset(m_ppic->m_iGlowDropShadowOffset, m_ppic->m_iGlowDropShadowOffset);

         pgraphics->draw(rDropShadow, dibDropShadow->g(), rect(dibDropShadow->m_size));

      }

   }


   void pic::draw_impl(::draw2d::graphics * pgraphics, LPCRECT lpcrect)
   {


   }


   void pic::draw(::draw2d::graphics * pgraphics)
   {

      ::draw2d::savedc savedc(pgraphics);

      ::draw2d::matrix mRot;

      rectd rClip(m_ppic->m_rectDrawing);

      pointd_array pta;

      pta.set_size(4);

      pta[0] = _transform_drawing(rClip.top_left());
      pta[1] = _transform_drawing(rClip.top_right());
      pta[2] = _transform_drawing(rClip.bottom_right());
      pta[3] = _transform_drawing(rClip.bottom_left());

      ::draw2d::region_sp rgn(allocer());

      rgn->create_polygon(pta.get_data(), (int)pta.get_count(), ::draw2d::fill_mode_winding);

      pgraphics->SelectClipRgn(rgn, RGN_AND);

      mRot.append(::draw2d::matrix::rotation(m_ppic->m_dRotate));

      ::draw2d::matrix mG;

      pgraphics->get_viewport_scale(mG);

      pgraphics->prepend(mRot);

      pgraphics->prepend(::draw2d::matrix::scaling(m_ppic->m_dZoom, m_ppic->m_dZoom));

      ::draw2d::matrix mTrans;

      point ptD = m_ppic->m_rectDrawing.center();

      mG.transform(ptD);

      mTrans.append(::draw2d::matrix::translation(ptD));

      pgraphics->append(mTrans);

      rect r(-point(m_ppic->m_rectDrawing.get_size() / 2.0) +
             point(m_ppic->m_ptDrag.x * m_ppic->m_rectDrawing.width(),
                   m_ppic->m_ptDrag.y * m_ppic->m_rectDrawing.height()), ::size(m_ppic->m_rectDrawing.get_size()));

      draw_impl(pgraphics, r);


   }




   void pic::move_to(pointd pt, ::sized sizePage, ::sized sizeClient, LPCRECTD lpcrectMargin)
   {

      m_ppic->m_rect.move_to(pt);

      update_region();

      m_ppic->m_rect._001Constraint(lpcrectMargin, m_ppic->m_rectBounding);

      update_drawing_rect(sizePage, sizeClient);

      update_region();

      update_placement();

   }


   void pic::pic_impl::io(stream & serialize)
   {

      if (serialize.is_version(FIRST_VERSION))
      {

         serialize(m_rect);
         serialize(m_rectDrawing);
         serialize(m_rectCursor);
         serialize(m_bDrag);
         serialize(m_dRotate);
         serialize(m_rectBounding);
         serialize.stream_array(m_pta);
         serialize.stream_array(m_ptaDrawing);
         serialize.stream_array(m_ptaCursor);
         serialize(m_dZoom);
         serialize(m_ptDrag);


         serialize(m_bOutline);
         serialize(m_iOutlineWidth);
         serialize(m_hlsOutline);

         serialize(m_bGlowDropShadow);
         serialize(m_iGlowDropShadowOffset);
         serialize(m_iGlowDropShadowBlur);
         serialize(m_hlsGlowDropShadow);

         serialize(m_iBlur);
         serialize(m_bGrayscale);
         serialize(m_bInvert);
         serialize(m_iOpacity);
         serialize(m_iSaturation);

      }

   }


   void pic::io(stream & serialize)
   {

      if (serialize.is_version(FIRST_VERSION))
      {

         bool bEnable;

         if (serialize.is_storing())
         {

            bEnable = m_ppic != NULL;

         }

         serialize(bEnable);

         if (!serialize.is_storing())
         {

            enable_pic(bEnable);

         }

         if (bEnable)
         {

            serialize.stream_object(*m_ppic);

         }

      }

   }


} // namespace user



