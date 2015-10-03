#include "framework.h"


namespace tarsila
{


   polygon::polygon(::aura::application * papp) :
      ::object(papp),
      element(papp)
   {

   }


   void polygon::on_draw(draw * pdraw)
   {

      if(!pdraw->m_bSelected)
      {

         pdraw->m_pgraphics->Polygon(m_pointa);

      }
      else
      {

         point_array pointa = m_pointa;

         

         for(index i = 0; i < m_pointa.get_upper_bound(); i++)
         {

            call_sel_get_point(pdraw->m_pdrawing,pointa[i],i);
            

         }

         pdraw->m_pgraphics->Polygon(pointa);


      }

   }



   void polygon::xml_import(::xml::input_tree & xmlif)
   {

      xmlif.import_node("point_array",m_pointa);

   }

   void polygon::xml_export(::xml::output_tree & xmlof)
   {

      xmlof.export_node("point_array",m_pointa);

   }


   bool polygon::contains(point pt)
   {

      return m_pointa.polygon_contains(pt);

   }


   void polygon::translate(size sz)
   {

      m_pointa.offset(sz);
      
   }


   int polygon::sel_get_point_count()
   {
      return m_pointa.get_count();
   }

   bool polygon::sel_get_point(LPPOINT ppt,int iIndex)
   {
      if(iIndex < 0)
         return false;
      if(iIndex >= m_pointa.get_size())
         return false;
      *ppt =m_pointa[iIndex];
      return true;
   }

   bool polygon::sel_set_point(LPPOINT ppt,int iIndex)
   {
      if(iIndex < 0)
         return false;
      if(iIndex >= m_pointa.get_size())
         return false;
      m_pointa[iIndex] = *ppt;
      return true;
   }

} // namespace tarsila





