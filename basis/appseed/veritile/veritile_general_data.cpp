#include "framework.h"


namespace veritile
{


   property_sheet_data::property_sheet_data(::aura::application * papp):
      object(papp)
   {

      m_pmutex = canew(mutex(papp));

   }


   property_sheet_data::~property_sheet_data()
   {


   }


} // namespace veritile










