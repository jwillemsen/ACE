// -*- C++ -*-
//
// $Id: ECG_UDP_EH.inl 73791 2006-07-27 20:54:56Z wotte $

TAO_BEGIN_VERSIONED_NAMESPACE_DECL

ACE_INLINE ACE_SOCK_Dgram&
TAO_ECG_UDP_EH::dgram (void)
{
  return this->dgram_;
}

TAO_END_VERSIONED_NAMESPACE_DECL
