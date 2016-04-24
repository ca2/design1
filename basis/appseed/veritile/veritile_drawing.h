#pragma once


namespace veritile
{


   class CLASS_DECL_APP_CORE_VERITILE drawing:
      virtual public ::xml::exportable,
      virtual public ::xml::importable
   {
   public:

      enum e_mode
      {

         mode_none,
         mode_place,
         mode_random,

      };


      bool                                            m_bMoving;
      bool                                            m_bMovingPoint;
      e_mode                                          m_emode;
      point                                           m_ptStart;
      point                                           m_ptMove;



      mutex                         m_mutex;
      polygon_array                 m_polygona;

      element_array                               m_elementptra;
      element_array                               m_elementptraSelected;

      ::draw2d::graphics *         m_pgraphics;


      drawing(::aura::application * papp);


      virtual void xml_import(::xml::input_tree & xmlif);
      virtual void xml_export(::xml::output_tree & xmlof);

      ::veritile::element * hit_test(point pt);

      

      DRAWDD();


   };


} // namespace veritile





