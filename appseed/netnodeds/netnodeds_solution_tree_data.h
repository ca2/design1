#pragma once


namespace netnodeds
{


   class CLASS_DECL_DESIGN_NETNODEDS solution_tree_data :
      virtual public ::data::tree
   {
   public:


      solution_tree_data(::aura::application * papp);


      virtual sp(::data::tree_item) on_allocate_item();


   };



} // namespace ca



