#include "framework.h"


namespace composite
{


   data::data(::aura::application * papp) :
      ::object(papp),
      ::data::data(papp),
      m_sizePagePrev(0, 0),
      m_dibBackground(allocer()),
      m_dibAlphaMask(allocer())
   {

      m_dibBackground->oprop("read_only_link") = "";
      m_dibAlphaMask->oprop("read_only_link") = "";

      m_rectMargin.set(0);
      m_rectMaxMarginDrawing.set(0);
      m_rectMarginDrawing.set(0);

      m_pictool = canew(pic_tool(get_app()));

      m_pictool->m_map[::composite::tool_rotate].m_dib = Application.get_matter_dib("pictool/rotation24.png");
      m_pictool->m_map[::composite::tool_crop].m_dib = Application.get_matter_dib("pictool/crop-icon24.png");
      m_pictool->m_map[::composite::tool_edit_text].m_dib = Application.get_matter_dib("pictool/text-icon24.png");
      m_pictool->m_map[::composite::tool_close].m_dib = Application.get_matter_dib("pictool/close-button24.png");
      m_pictool->m_map[::composite::tool_stack_up].m_dib = Application.get_matter_dib("pictool/stackup24.png");
      m_pictool->m_map[::composite::tool_special_effect].m_dib = Application.get_matter_dib("pictool/fx24.png");
      m_pictool->m_map[::composite::tool_stack_down].m_dib = Application.get_matter_dib("pictool/stackdown24.png");
      m_pictool->m_map[::composite::tool_resize].m_dib = Application.get_matter_dib("pictool/resize20.png");

      m_pictool->m_map[::composite::tool_zoom_out].m_dib = Application.get_matter_dib("pictool/zoomout24.png");
      m_pictool->m_map[::composite::tool_zoom_in].m_dib = Application.get_matter_dib("pictool/zoomin24.png");
      m_pictool->m_map[::composite::tool_move].m_dib = Application.get_matter_dib("pictool/drag24.png");
      m_pictool->m_map[::composite::tool_apply].m_dib = Application.get_matter_dib("pictool/apply24.png");

      m_pictool->m_map[::composite::tool_resize].m_ecursor = visual::cursor_size_bottom_right;

      m_pictool->m_penBorder.alloc(allocer());
      m_pictool->m_penBorder->create_solid(1.0, ARGB(190, 80, 120, 200));
      m_pictool->m_penBorder->m_etype = ::draw2d::pen::type_dash;

   }


   data::~data()
   {



   }


   void data::io(stream & serialize)
   {

      try
      {

         serialize(*m_dibBackground);

         serialize(*m_dibAlphaMask);

         serialize(m_sizePage);
         serialize(m_sizePagePrev);
         serialize(m_rectMarginDrawing);
         serialize(m_rectMaxMarginDrawing);
         serialize(m_rectMargin);
         serialize(m_rectMarginPrev);

         serialize.stream_array(m_pica);

      }
      catch (...)
      {
      }

   }


   pic::pic(::aura::application * papp) :
      ::object(papp),
      ::user::pic(papp)
   {

//      m_pview = Application.m_pcompositeviewCurrent;

   }


   bool pic::pic::is_valid()
   {

      return m_dib.is_set() && m_dib->area() > 0;

   }


   ::sized pic::pic::get_size()
   {

      return m_dib->m_size;

   }


   void pic::io(stream & stream)
   {

      if (stream.is_storing())
      {

         string strLink = m_dib->oprop("read_only_link");

         stream(strLink);

      }
      else
      {

         string strLink;

         stream(strLink);

         if (strLink.is_empty())
         {

            return;

         }

         m_dib.alloc(allocer());

         if (System.imaging().load_from_file(m_dib, stream.get_link_path(strLink)))
         {

            m_dib->oprop("read_only_link") = strLink;

         }

      }

      ::user::pic::io(stream);

   }


   void pic::pic::draw_impl(::draw2d::graphics * pgraphics, LPCRECT lpcrect)
   {

      rect r(lpcrect);

      ::draw2d::dib * pdib = m_dib;

      ::visual::fastblur blur;

      pdib->m_bColorMatrix = false;

      pdib->m_colormatrix = ::draw2d::color_matrix();

      if (m_ppic->m_iBlur > 0)
      {

         double dBlur = (double) m_ppic->m_iBlur * (double)pdib->m_size.cx / (double)r.width();

         int iBlur = ceil(dBlur);

         blur.alloc(allocer());

         rect rDib(pdib->m_size);

         int iShift = iBlur * 2;

         rDib.inflate(iShift, iShift);

         r.inflate(m_ppic->m_iBlur, m_ppic->m_iBlur);

         blur.initialize(rDib.width(), rDib.height(), iBlur);

         blur->Fill(0);

         blur->g()->draw(rect(point(iShift, iShift), pdib->m_size), pdib->g());

         blur.blur();

         pdib = blur;

      }

      pdib->m_bColorMatrix = false;

      pdib->m_colormatrix = ::draw2d::color_matrix();

      if (m_ppic->m_bGrayscale)
      {

         pdib->m_bColorMatrix = true;

         pdib->m_colormatrix.grayscale();

      }
      else if(m_ppic->m_iSaturation != 100)
      {

         pdib->m_bColorMatrix = true;

         pdib->m_colormatrix.saturation(0.3333, 0.3333, 0.3333, m_ppic->m_iSaturation / 100.0);

      }

      if (m_ppic->m_bInvert)
      {

         pdib->m_bColorMatrix = true;

         pdib->m_colormatrix.invert();

      }

      if (m_ppic->m_iOpacity != 100)
      {

         pgraphics->alpha_blend(r, pdib->g(), rect(pdib->m_size), m_ppic->m_iOpacity / 100.0);

      }
      else
      {

         pgraphics->draw(r, pdib->g(), rect(pdib->m_size));

      }

      if (m_ppic->m_bBorder)
      {

         color c(m_ppic->m_hlsBorder);

         pgraphics->draw_border(r, c, m_ppic->m_iBorderWidth);

      }

   }




} // namespace composite