// $Id: OBV_impl.cpp 84563 2009-02-23 08:13:54Z johnnyw $

#include "OBV_impl.h"
#include "ace/OS_NS_sys_time.h"

// Implementation of the valuetype member functions.

Event_impl::Event_impl ()
{
}

Event_impl::Event_impl (CORBA::Long value)
{
  this->value_ (value);
}

Event_impl::~Event_impl ()
{
}

CORBA::ValueBase*
Event_impl::_copy_value (void)
{
  return new Event_impl (this->value_ ());
}


void
Event_impl::do_print (void)
{
  ACE_DEBUG((LM_DEBUG, "(value %d) \n",
             (CORBA::ULong) this->value_()));
}

Event_factory::~Event_factory ()
{
}

TAO_OBV_CREATE_RETURN_TYPE (Event)
Event_factory::create_for_unmarshal (void)
{
  return new Event_impl;
}

