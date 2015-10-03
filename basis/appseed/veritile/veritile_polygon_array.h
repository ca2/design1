#pragma once


namespace tarsila
{


   class CLASS_DECL_APP_CORE_TARSILA polygon_array:
      public ::xml::smart_pointer_array < drawing_polygon,polygon >
   {
   public:

      polygon_array()
      {

      }

      polygon_array(const polygon_array & xmla)
      {

         copy(xmla);

      }


   };




} // namespace tarsila






