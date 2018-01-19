﻿#pragma once


namespace tarsila
{


   class CLASS_DECL_APP_CORE_TARSILA element_array:
      public pointer_array < element * >
   {
   public:


      element_array();


      virtual void translate(::size sz);

      void sel_point_clear();

      void move_to_sel_points(drawing * pdrawing);

   };




} // namespace tarsila






