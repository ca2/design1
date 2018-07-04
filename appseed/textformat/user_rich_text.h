#pragma once


namespace user
{


   namespace rich_text
   {


      enum e_script
      {

         script_normal,
         script_subscript,
         script_superscript,

      };

      enum e_line_height
      {

         line_height_single,
         line_height_one_and_a_half,
         line_height_double

      };

      enum e_attribute
      {

         attribute_bold,
         attribute_italic,
         attribute_underline,
         attribute_family,
         attribute_size,
         attribute_foreground,
         attribute_background,
         attribute_script,
         attribute_line_height,
         attribute_align

      };


      enum e_align
      {

         align_left,
         align_center,
         align_right,

      };

      enum e_bias
      {

         bias_none,
         bias_left,
         bias_right,

      };

      using attribute_flags = comparable_array < e_attribute >;


   } // namespace rich_text


} // namespace user


#include "user_rich_text_format.h"
#include "user_rich_text_box.h"
#include "user_rich_text_layout.h"
#include "user_rich_text_data.h"
