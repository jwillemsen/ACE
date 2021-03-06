// -*- C++ -*-
// $Id: DAnCE_DeploymentInterceptors_Base_Impl.cpp 92190 2010-10-08 11:48:48Z johnnyw $

#include "DAnCE_DeploymentInterceptors_Base_Impl.h"

namespace DAnCE
{
  // Implementation skeleton constructor
  DeploymentInterceptor_Base::DeploymentInterceptor_Base (void)
  {
  }

  // Implementation skeleton destructor
  DeploymentInterceptor_Base::~DeploymentInterceptor_Base (void)
  {
  }

  void
  DeploymentInterceptor_Base::configure (const ::Deployment::Properties &)
  {
    // Add your implementation here
  }

  void
  DeploymentInterceptor_Base::preprocess_plan (::Deployment::DeploymentPlan &)
  {
    // Add your implementation here
  }

  void
  DeploymentInterceptor_Base::pre_install (::Deployment::DeploymentPlan &,
                                                    ::CORBA::ULong)
  {
    // Add your implementation here
  }

  void
  DeploymentInterceptor_Base::post_install (const ::Deployment::DeploymentPlan &,
                                                     ::CORBA::ULong,
                                                     const ::CORBA::Any & ,
                                                     const ::CORBA::Any & )
  {
    // Add your implementation here
  }

  void
  DeploymentInterceptor_Base::post_endpoint_reference (const ::Deployment::DeploymentPlan & ,
                                                               ::CORBA::ULong ,
                                                               const ::CORBA::Any & ,
                                                               const ::CORBA::Any & )
  {
    // Add your implementation here
  }

  void
  DeploymentInterceptor_Base::pre_connect (::Deployment::DeploymentPlan & ,
                                                    ::CORBA::ULong ,
                                                    ::CORBA::Any & )
  {
    // Add your implementation here
  }

  void
  DeploymentInterceptor_Base::post_connect (const ::Deployment::DeploymentPlan & ,
                                                     ::CORBA::ULong ,
                                                     const ::CORBA::Any & )
  {
    // Add your implementation here
  }

  void
  DeploymentInterceptor_Base::pre_disconnect (::Deployment::DeploymentPlan &,
                                       ::CORBA::ULong)
  {
    // Add your implementation here
  }

  void
  DeploymentInterceptor_Base::post_disconnect (const ::Deployment::DeploymentPlan &,
                                             ::CORBA::ULong,
                                             const ::CORBA::Any &)
  {
    // Add your implementation here
  }

  void DeploymentInterceptor_Base::post_configured (const ::Deployment::DeploymentPlan & ,
                                                                ::CORBA::ULong ,
                                                                const ::CORBA::Any &)
  {
    // Add your implementation here
  }

  void DeploymentInterceptor_Base::post_activate (const ::Deployment::DeploymentPlan & ,
                                                              ::CORBA::ULong ,
                                                              const ::CORBA::Any & )
  {
    // Add your implementation here
  }

  void DeploymentInterceptor_Base::post_passivate (const ::Deployment::DeploymentPlan & ,
                                                               ::CORBA::ULong ,
                                                               const ::CORBA::Any &)
  {
    // Add your implementation here
  }

  void DeploymentInterceptor_Base::post_remove (const ::Deployment::DeploymentPlan & ,
                                                            ::CORBA::ULong ,
                                                            const ::CORBA::Any & )
  {
    // Add your implementation here
  }

  void DeploymentInterceptor_Base::unexpected_event (const ::Deployment::DeploymentPlan &,
                                                     ::CORBA::ULong,
                                                     const ::CORBA::Any &,
                                                     const char *)
  {
  }
}

