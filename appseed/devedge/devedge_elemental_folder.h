#pragma once

namespace devedge
{

   class project;

   class CLASS_DECL_DEVEDGE folder :
      virtual public ::devedge::elemental,
      virtual public spa(file)
   {
   public:


      project *   m_pproject;
      string      m_strFilter;



      folder(::aura::application * papp);


      virtual e_solution_type get_solution_type();


      bool load(project * pproject, const char * pszFilter);

      index find(const char * pszName);
      bool has(const char * pszName);
      
   };

} // namespace devedge