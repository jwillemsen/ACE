// $Id: Locality_Manager_Task.h 94556 2011-10-04 19:43:28Z wotte $
/**
 * @file Locality_Manager_Task.h
 * @author William R. Otte
 *
 * Defines interface for the bootstrap element of the Locality Manager.
 */

#ifndef DAnCE_LOCALITY_TASK_H_
#define DAnCE_LOCALITY_TASK_H_

#include "ace/String_Base.h"
#include "ace/Task.h"
#include "tao/ORB.h"
#include "dance/Deployment/Deployment_BaseC.h"

#include <list>
#include <string>

namespace DAnCE
{
  class LocalityManager_Task : ACE_Task_Base
  {
  public:
    LocalityManager_Task (int argc, ACE_TCHAR **argv);

    int svc (void);

    struct Error
    {
      Error (const ACE_CString &err);
      ACE_CString err_;
    };

    void run (void);

  private:
    void parse_args (int argc, ACE_TCHAR **argv);

    void usage (void);

    CORBA::ORB_var orb_;
    ::Deployment::Properties_var config_;

    ACE_TString uuid_;
    ACE_TString callback_ior_str_;
    ACE_TString output_file_;

    std::list < std::string > plugin_config_;
  };
}

#endif
