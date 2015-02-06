#pragma once


namespace devedge
{


   class CLASS_DECL_DEVEDGE solution_tree_data :
      virtual public ::data::tree
   {
   public:


      solution_tree_data(::aura::application * papp);


      virtual sp(::data::tree_item) on_allocate_item();


   };



} // namespace ca



