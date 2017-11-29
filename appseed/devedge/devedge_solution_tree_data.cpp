#include "framework.h"


namespace devedge
{


   solution_tree_data::solution_tree_data(::aura::application * papp) :
      ::object(papp),
      ::data::data(papp),
      ::data::tree(papp)
   {
   }

   sp(::data::tree_item) solution_tree_data::on_allocate_item()
   {
      // please use insert item with proper allocated data type
      throw new interface_only_exception(get_app());
      return NULL;
   }


} // namespace ca


