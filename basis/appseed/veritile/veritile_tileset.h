#pragma once


namespace veritile
{

   
   class tileset:
      virtual public object
   {
   public:


      tileset_view *       m_pview;
      ::visual::dib_sp     m_dib;
      string               m_strFile;



      tileset(::aura::application * papp);
      virtual ~tileset();



   };



} // namespace veritile