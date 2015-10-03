#pragma once


namespace veritile
{


   class CLASS_DECL_APP_CORE_VERITILE element_array:
      public ptr_array < element >
   {
   public:


      element_array();


      virtual void translate(::size sz);

      void sel_point_clear();

      void move_to_sel_points(drawing * pdrawing);

   };




} // namespace veritile






