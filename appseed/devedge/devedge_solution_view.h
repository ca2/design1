#pragma once


namespace devedge
{


   class solution_view :
      virtual public ::user::tree_view
   {
   public:


      solution *  m_psolution;


      solution_view(::aura::application * papp);

      virtual void install_message_handling(::message::dispatch * pinterface);

      bool load();

      void _001OnOpenItem(sp(::data::tree_item) pitem);

      DECL_GEN_SIGNAL(_001OnCreate);

   };


} // namespace devedge










