#pragma once


namespace tarsila
{


   class CLASS_DECL_APP_CORE_TARSILA drawing:
      virtual public ::xml::exportable,
      virtual public ::xml::importable
   {
   public:

      enum e_mode
      {

         mode_none,
         mode_selection,
         mode_polygon_tool,
         mode_show_alarm,

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

      ::tarsila::element * hit_test(point pt);


      DRAWDD();


   };


} // namespace tarsila





