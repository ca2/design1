#pragma once


void CLASS_DECL_DEVEDGE KickDevEdgeFront(::aura::application * papp);


namespace netnode
{


   class bergedge_document;


} // namespace netnode


class netnodeScriptManager;


namespace devedge
{


   class pane_view;


   class CLASS_DECL_DEVEDGE application :
      virtual public ::tesseract::application
   {
   public:


      map < int32_t, int32_t, netnode::bergedge_document *, netnode::bergedge_document * > m_mapEdge;
      sp(pane_view)                   m_ppaneview;
      ::devedge::devedge          * m_pdevedge;


      application();
      virtual ~application();


      //virtual void construct();


      virtual bool initialize_application();
      virtual int32_t exit_application() override;

      virtual void pre_translate_message(::message::message * pobj);

      virtual void on_request(::create * pcreate);

      virtual bool _001OnCmdMsg(::user::command * pcommand);

      virtual bool on_install();


      inline ::devedge::devedge & devedge() { return *m_pdevedge; }

   };


} // namespace devedge



