#pragma once


void CLASS_DECL_DESIGN_NETNODEDS KickDevEdgeFront(::aura::application * papp);


namespace netnode
{


   class bergedge_document;


} // namespace netnode


class netnodeScriptManager;


namespace netnodeds
{


   class pane_view;


   class CLASS_DECL_DESIGN_NETNODEDS application :
      virtual public ::tesseract::application
   {
   public:


      map < int32_t, int32_t, netnode::bergedge_document *, netnode::bergedge_document * > m_mapEdge;
      sp(pane_view)                   m_ppaneview;
      ::netnodeds::netnodeds          * m_pnetnodeds;


      application();
      virtual ~application();


      virtual void construct();


      virtual bool initialize_application();
      virtual int32_t exit_application() override;

      virtual void pre_translate_message(::signal_details * pobj);

      virtual void on_request(::create * pcreate);

      virtual bool _001OnCmdMsg(::user::command * pcommand);

      virtual bool on_install();


      inline ::netnodeds::netnodeds & netnodeds() { return *m_pnetnodeds; }

   };


} // namespace netnodeds



