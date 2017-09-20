#pragma once


namespace tarsila
{


   class CLASS_DECL_APP_CORE_TARSILA element:
      virtual public ::xml::exportable,
      virtual public ::xml::importable
   {
      public:

         class draw
         {
            public:

               drawing *               m_pdrawing;
               ::draw2d::graphics *    m_pgraphics;
               bool                    m_bSelected;

         };

         index_array            m_iaSelectedPoint;



         element(::aura::application * papp);


         virtual bool contains(point pt);


         virtual void xml_import(::xml::input_tree & xmlif);
         virtual void xml_export(::xml::output_tree & xmlof);


         virtual void draw_this(drawing * pdrawing);

         virtual void on_draw(draw * pdraw);

         virtual bool is_selected(drawing * pdrawing);

         virtual void translate(size sz);

         virtual ::count sel_get_point_count();
         virtual bool sel_get_point(LPPOINT ppt, index iIndex);
         virtual bool sel_set_point(LPPOINT ppt, index iIndex);

         virtual bool call_sel_get_point(drawing * pdrawing, LPPOINT ppt, index iIndex, bool * ppSelected = NULL);
         virtual bool sel_get_rect(drawing * pdrawing, LPRECT lrpect, index iIndex, bool * ppSelected = NULL);
         virtual bool sel_point_selected(index iIndex);
         virtual void sel_point_select(index iIndex);
         virtual void sel_point_clear();
         virtual index sel_point_hit_test(point pt);
         virtual void move_to_sel_points(drawing * pdrawing);

   };




} // namespace tarsila





