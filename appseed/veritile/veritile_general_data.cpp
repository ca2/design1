#include "framework.h"


namespace veritile
{


   general_data::general_data(::aura::application * papp):
      object(papp),
      ::data::data(papp)
   {

      m_pmutex = canew(mutex(papp));

   }


   general_data::~general_data()
   {


   }


} // namespace veritile










