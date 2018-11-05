#pragma once


namespace veritile
{


   class CLASS_DECL_APP_CORE_VERITILE layer :
      virtual public ::object
   {
   public:


      class CLASS_DECL_APP_CORE_VERITILE tile
      {
      public:


         int      m_iTile;
         point    m_pt;

         tile();

      };

      
      array < array < tile > >    m_tile2a;
      ::size            m_size;


      layer(::aura::application * papp);
      virtual  ~layer();


      bool update(int cx,int cy);

   };


} // namespace veritile










