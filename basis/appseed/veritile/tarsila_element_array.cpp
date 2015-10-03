#include "framework.h"


namespace tarsila
{


   element_array::element_array()
   {

   }


   void element_array::translate(::size sz)
   {

      for(index i = 0; i < get_size(); i++)
      {

         element_at(i)->translate(sz);

      }


   }

   void element_array::sel_point_clear()
   {
      
      for(index i = 0; i < get_size(); i++)
      {

         element_at(i)->sel_point_clear();

      }

   }

   void element_array::move_to_sel_points(drawing * pdrawing)
   {

      for(index i = 0; i < get_size(); i++)
      {

         element_at(i)->move_to_sel_points(pdrawing);

      }

   }

} // namespace tarsila






