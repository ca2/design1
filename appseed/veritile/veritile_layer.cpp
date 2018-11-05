#include "framework.h"


namespace veritile
{


   layer::tile::tile()
   {

      m_iTile = -1;

      m_pt.x = -1;

      m_pt.y = -1;

   }

   layer::layer(::aura::application * papp) :
      object(papp)
   {

   }


   layer::~layer()
   {


   }


   bool layer::update(int cx,int cy)
   {
      
      m_size.cx = cx;

      m_size.cy = cy;

      m_tile2a.set_size(m_size.cy);

      for(auto & a : m_tile2a)
      {

         a.set_size(m_size.cx);

      }

      return true;

   }

} // namespace veritile










