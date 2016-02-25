#include "framework.h"


namespace tarsila
{


   element::element(::aura::application * papp)
   {

   }


   void element::on_draw(draw * pdraw)
   {

   }


   bool element::is_selected(drawing * pdrawing)
   {

      return pdrawing->m_elementptraSelected.contains(this);

   }

   void element::xml_import(::xml::input_tree & xmlif)
   {

      //xmlif.import_node("point_array",m_pointa);

   }

   void element::xml_export(::xml::output_tree & xmlof)
   {

      //xmlof.export_node("point_array",m_pointa);

   }


   bool element::contains(point pt)
   {

      return false;

   }


   void element::draw_this(drawing * pdrawing)
   {

      ::tarsila::element::draw draw;


      draw.m_pdrawing = pdrawing;
      draw.m_pdib = pdrawing->m_pdib;
      draw.m_bSelected = is_selected(pdrawing);

      bool bMoving = pdrawing->m_bMoving;

      point ptViewport;

      if(bMoving && draw.m_bSelected)
      {

         ptViewport = draw.m_pdib->get_graphics()->GetViewportOrg();

         point ptOffset = pdrawing->m_ptMove - pdrawing->m_ptStart;

         draw.m_pdrawing->m_pdib->get_graphics()->OffsetViewportOrg(ptOffset.x,ptOffset.y);

      }

      try
      {
         on_draw(&draw);
      }
      catch(...)
      {
      }

      try
      {

         if(draw.m_bSelected)
         {

            ::count cPoint = sel_get_point_count();

            ::rect rect;

            bool bSelected;

            for(index i = 0; i < cPoint; i++)
            {


               if(sel_get_rect(pdrawing,rect,i,&bSelected))
               {

                  if(bSelected)
                  {

                     draw.m_pdib->get_graphics()->FillSolidRect(rect,ARGB(255,0,0,0));

                  }
                  else
                  {

                     draw.m_pdib->get_graphics()->Draw3dRect(rect,ARGB(255,0,0,0),ARGB(255,0,0,0));

                  }

               }

            }

         }

      }
      catch(...)
      {
      }

      if(bMoving && draw.m_bSelected)
      {

         draw.m_pdib->get_graphics()->SetViewportOrg(ptViewport);

      }

   }


   void element::translate(::size sz)
   {
   }

   int element::sel_get_point_count()
   {

      return 0;

   }

   bool element::sel_get_point(LPPOINT lppt,int iIndex)
   {

      return false;

   }

   
   bool element::sel_set_point(LPPOINT ppt,int iIndex)
   {

      return false;
   }


   bool element::call_sel_get_point(drawing * pdrawing,LPPOINT lppt,int iIndex,bool * pbSelected)
   {

      if(iIndex < 0)
         return false;

      if(iIndex > sel_get_point_count())
         return false;

      if(!sel_get_point(lppt,iIndex))
         return false;

      bool bSel = false;

      if(pdrawing != NULL)
      {

         bSel =  sel_point_selected(iIndex);

         if(pdrawing->m_elementptraSelected.contains(this) && pdrawing->m_bMovingPoint)
         {

            

            if(bSel)
            {

               point ptOffset = pdrawing->m_ptMove - pdrawing->m_ptStart;

               ::offset(*lppt,ptOffset.x, ptOffset.y);

               

            }

         }

      }

      if(pbSelected != NULL)
      {
         
         *pbSelected = bSel;

      }

      return true;

   }

   bool element::sel_get_rect(drawing * pdrawing, LPRECT lrpect,int iIndex, bool * pbSelected)
   {

      point pt;

      if(!call_sel_get_point(pdrawing,&pt,iIndex,pbSelected))
      {
         
         return false;

      }

      int iSize = 3;
      lrpect->left = pt.x - iSize;
      lrpect->top = pt.y - iSize;
      lrpect->right = pt.x + iSize;
      lrpect->bottom = pt.y + iSize;

      return true;

   }

   bool element::sel_point_selected(int iIndex)
   {

      return m_iaSelectedPoint.contains(iIndex);

   }

   void element::sel_point_select(int iIndex)
   {

      m_iaSelectedPoint.add_unique(iIndex);

   }

   void element::sel_point_clear()
   {

      m_iaSelectedPoint.remove_all();

   }

   int element::sel_point_hit_test(point pt)
   {

      ::rect r;
      
      for(index i = 0; i < sel_get_point_count(); i++)
      {



         if(sel_get_rect(NULL,r,i))
         {
            if(r.contains(pt))
            {
               return i;
            }
         }



      }

      return -1;

   }


   void element::move_to_sel_points(drawing * pdrawing)
   {

      if(!is_selected(pdrawing))
         return;

      ::point pt;

//      bool bSel;

      for(index i = 0; i < sel_get_point_count(); i++)
      {

         if(sel_point_selected(i))
         {

            if(sel_get_point(pt,i))
            {
               
               pt += pdrawing->m_ptMove - pdrawing->m_ptStart;

               sel_set_point(pt,i);

            }

         }

      }

      
   }



} // namespace tarsila





