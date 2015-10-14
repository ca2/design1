#include "framework.h"


namespace veritile
{



   tileset::tileset(::aura::application * papp):
      object(papp),
      m_dib(allocer()),
      m_data(papp)
   {

      m_data.m_set["tilex"] = 32;
      m_data.m_map["tilex"].m_validate.m_rules["natural"] = true;
      m_data.m_map["tilex"].m_validate.m_rules["m_iMin"] = 1;


      m_data.m_set["tiley"] = 32;
      m_data.m_map["tiley"].m_validate.m_rules["natural"] = true;
      m_data.m_map["tiley"].m_validate.m_rules["m_iMin"] = 1;


      m_ptBeg = point(-1, -1);
      m_ptEnd = point(-1, -1);

   }


   tileset::~tileset()
   {

   }

   bool tileset::load(var varFile)
   {

      if(!m_dib.load_from_file(varFile))
      {
       
         return false;

      }

      m_strFile = varFile;

      m_data.m_map["tilex"].m_validate.m_rules["m_iMax"] = m_dib->m_size.cx;

      m_data.m_map["tiley"].m_validate.m_rules["m_iMax"] = m_dib->m_size.cy;

      return true;

   }

   
   int tileset::tilex()
   {

      return MAX(1,abs(m_data.m_set["tilex"].int32()));

   }

   int tileset::tiley()
   {

      return MAX(1,abs(m_data.m_set["tiley"].int32()));

   }

   int tileset::xcount()
   {

      return m_dib->size().cx / tilex();

   }

   int tileset::ycount()
   {

      return m_dib->size().cy / tiley();


   }

   int tileset::width()
   {

      return xcount() * tilex();

   }

   int tileset::height()
   {

      return ycount() * tiley();

   }

   ::size tileset::size()
   {
      
      return ::size(width(),height());

   }

   bool tileset::hit_test(point & ptTile, point pt)
   {

      ptTile.x =  pt.x / tilex();

      ptTile.y =  pt.y / tiley();

      if(ptTile.x < 0)
         return false;

      if(ptTile.y < 0)
         return false;

      if(ptTile.x >= xcount())
         return false;

      if(ptTile.y >= ycount())
         return false;

      return true;

   }


   void tileset::on_property_change(property & property)
   {

   }

} // namespace veritile