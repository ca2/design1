#pragma once


namespace veritile
{

   
   class tileset:
      virtual public object
   {
   public:


//      tileset_view *       m_pview;
      ::visual::dib_sp     m_dib;
      string               m_strFile;
      index                m_iIndex;

      general_data         m_data;






      tileset(::aura::application * papp);
      virtual ~tileset();


      string get_id();


      virtual bool load(var varFile);


      virtual int tilex();
      virtual int tiley();
      virtual int xcount();
      virtual int ycount();
      virtual int width();
      virtual int height();
      virtual ::size size();
      virtual bool hit_test(point & ptTile, point pt);

      

   };



} // namespace veritile