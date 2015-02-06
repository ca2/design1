#pragma once


namespace devedge
{


   class CLASS_DECL_DEVEDGE source :
      virtual public folder
   {
   public:


      bool m_bFramework;


      source(::aura::application * papp);


      virtual e_solution_type get_solution_type();


      bool load(project * pproject);


   };


} // namespace devedge


