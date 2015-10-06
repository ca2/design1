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

   
   string tileset::get_id()
   {

      return m_strFile + "." + ::str::from(m_iIndex);

   }


   int tileset::tilex()
   {

      return MAX(1,abs(m_data["tilex"].int32()));

   }

   int tileset::tiley()
   {

      return MAX(1,abs(m_data["tilex"].int32()));

   }

   int tileset::xcount()
   {

      return m_dib->height() / tiley();

   }

   bool tileset::ycount()
   {

      return m_dib->width() / tilex();


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

   bool tileset::hit_test(int & iTileX,int & iTileY, point pt)
   {

      iTileX =  pt.x / tilex();

      iTileY =  pt.y / tiley();

      if(iTileX < 0)
         return false;

      if(iTileY < 0)
         return false;

      if(iTileX >= xcount())
         return false;

      if(iTileY >= ycount())
         return false;

      return true;

   }


} // namespace veritile