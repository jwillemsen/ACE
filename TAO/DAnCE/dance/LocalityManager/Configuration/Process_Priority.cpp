// $Id: Process_Priority.cpp 93566 2011-03-17 03:20:28Z wotte $

#include "Process_Priority.h"
#include "dance/DAnCE_PropertiesC.h"
#include "dance/Deployment/Deployment_StartErrorC.h"

#include "dance/Logger/Log_Macros.h"

#include <sstream>
#include "ace/Auto_Ptr.h"

namespace DAnCE
{
  Process_Priority::Process_Priority (void)
  {
  }

  // Implementation skeleton destructor
  Process_Priority::~Process_Priority (void)
  {
  }

  char * Process_Priority::type (void)
  {
    return CORBA::string_dup (DAnCE::DANCE_LM_PROCESSPRIORITY);
  }

  void Process_Priority::configure (const ::Deployment::Property & prop)
  {
    CORBA::Long prio;

    if (!(prop.value >>= prio))
      {
        DANCE_ERROR (DANCE_LOG_TERMINAL_ERROR,
                     (LM_ERROR, DLINFO
                      ACE_TEXT ("Process_Priority::configure - ")
                      ACE_TEXT ("Unable to extract priority value from config property\n")));
        throw ::Deployment::PlanError (prop.name.in (),
                                       "Unable to extract priority value from config property.");
      }

    ACE_hthread_t handle;

    ACE_OS::thr_self (handle);

    int retval = ACE_OS::thr_setprio (handle,
                                      static_cast<int> (prio),
                                      -1);

    if (retval != 0)
      {
        std::stringstream str;
        const char * safe_error (ACE_OS::strerror (ACE_OS::last_error ()));

        str << "Unable to set process priority to <" << prio << ">: "
            << safe_error;
        std::string message = str.str ();

        DANCE_ERROR (DANCE_LOG_TERMINAL_ERROR,
                     (LM_ERROR, DLINFO
                      ACE_TEXT ("Process_Priority::configure - %C\n"),
                      message.c_str ()));

        throw ::Deployment::StartError (prop.name.in (),
                                        message.c_str ());

      }

  }
}

extern "C"
{
  DAnCE::LocalityConfiguration_ptr create_Process_Priority (void)
  {
    DAnCE::LocalityConfiguration_ptr retval (0);

    ACE_NEW_RETURN (retval,
                    DAnCE::Process_Priority (),
                    0);

    return retval;
  }
}
