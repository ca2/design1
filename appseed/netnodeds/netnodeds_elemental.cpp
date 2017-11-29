#include "framework.h"


namespace netnodeds
{


   /*#define ROUND(x,y) (((x)+(y-1))&~(y-1))
   #define ROUND4(x) ROUND(x, 4)
   __STATIC fixed_alloc_no_sync _alloc001SimpleTreeItem(ROUND4(sizeof(::ca::elemental)));*/


   elemental::elemental()
   {
      m_iImage          = -1;
      m_iImageSelected  = -1;

   /*#undef new
      new(&m_str) string;
   #define new AURA_NEW*/
   }

   elemental::~elemental()
   {
   }

   string elemental::get_text(::data::tree * ptree)
   {
      UNREFERENCED_PARAMETER(ptree);
      return m_strName;
   }
   
   index elemental::get_image(::data::tree * ptree)
   {
      if(ptree->is_selected(this))
      {
         return m_iImageSelected;
      }
      else
      {
         return m_iImage;
      }
   }


/*#undef new
   void * elemental::operator new(size_t, const char *, int32_t)
   {
      return _alloc001SimpleTreeItem.Alloc();
   }

   void * elemental::operator new(size_t)
   {
      return _alloc001SimpleTreeItem.Alloc();
   }
#define new AURA_NEW*/

/*   void elemental::operator delete(void * p)
   {
      return _alloc001SimpleTreeItem.Free(p);
   }

   void elemental::operator delete(void * p, const char *, int32_t)
   {
      return _alloc001SimpleTreeItem.Free(p);
   }*/

   elemental::e_solution_type elemental::get_solution_type()
   {
      throw new interface_only_exception(get_app());
   }
   

} // namespace netnodeds


