#pragma once


namespace netnodeds
{


   class CLASS_DECL_DESIGN_NETNODEDS source :
      virtual public folder
   {
   public:


      bool m_bFramework;


      source(::aura::application * papp);


      virtual e_solution_type get_solution_type();


      bool load(project * pproject);


   };


} // namespace netnodeds


