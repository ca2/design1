#pragma once


namespace netnodeds
{


   class CLASS_DECL_DESIGN_NETNODEDS headers :
      virtual public folder
   {
   public:
      
      // precompiled header
      bool m_bFramework;

      
      headers(::aura::application * papp);

      virtual e_solution_type get_solution_type();

      bool load(project * pproject);


   };


} // namespace netnodeds





