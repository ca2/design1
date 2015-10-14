#pragma once


namespace veritile
{

   
   class tileset:
      virtual public object,
      virtual public property_sheet::callback
   {
   public:


//      tileset_view *       m_pview;
      ::visual::dib_sp     m_dib;
      string               m_strFile;
      string               m_strId;

      general_data         m_data;

      point                m_ptBeg;
      point                m_ptEnd;



      point_array          m_ptaSel;


      tileset(::aura::application * papp);
      virtual ~tileset();



      virtual bool load(var varFile);


      virtual int tilex();
      virtual int tiley();
      virtual int xcount();
      virtual int ycount();
      virtual int width();
      virtual int height();
      virtual ::size size();
      virtual bool hit_test(point & ptTile, point pt);

      virtual void on_property_change(property & property);

   };



} // namespace veritile