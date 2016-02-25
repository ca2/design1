#include "framework.h"

namespace tarsila
{


   drawing::drawing(::aura::application * papp) :
      ::object(papp)
   {

      m_bMoving = false;
      m_bMovingPoint = false;
      m_polygona.set_app(papp);

   }


   void drawing::_001OnDraw(::draw2d::dib * pdib)
   {

      synch_lock sl(&m_mutex);

      m_pdib = pdib;

      for(index i = 0; i < m_elementptra.get_size(); i++)
      {

         m_elementptra[i]->draw_this(this);

      }

   }


   void drawing::xml_import(::xml::input_tree & xmlif)
   {
      m_elementptra.remove_all();
      xmlif.import_node("polygon_array",m_polygona);
      for(index i = 0; i < m_polygona.get_size(); i++)
      {
         m_elementptra.add(&m_polygona(i));
      }

   }

   void drawing::xml_export(::xml::output_tree & xmlof)
   {

      xmlof.export_node("polygon_array",m_polygona);

   }

   element * drawing::hit_test(point pt)
   {
      for(index i = m_elementptra.get_upper_bound(); i >= 0; i--)
      {
         if(m_elementptra[i]->contains(pt))
            return m_elementptra[i];

         if(m_elementptra[i]->sel_point_hit_test(pt) >= 0)
            return m_elementptra[i];
      }
      return NULL;
   }


} // namespace tarsila







