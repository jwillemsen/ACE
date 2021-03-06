// -*- C++ -*-

//=============================================================================
/**
 *  @file    Completion_Counter_Base.h
 *
 *  $Id: Completion_Counter_Base.h 91745 2010-09-13 18:28:28Z johnnyw $
 *
 *  @author Martin Corino <mcorino@remedy.nl>
 */
//=============================================================================

#ifndef COMPLETION_COUNTER_H
#define COMPLETION_COUNTER_H

#include /**/ "ace/pre.h"

#include /**/ "ace/config-all.h"
#include "ace/Null_Mutex.h"
#include <string>
#include <vector>

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

namespace DAnCE
  {

  template <class ACE_LOCK>
  class Completion_Counter_Base
    {
    public:
      typedef ACE_LOCK lock_type;
      typedef std::vector<std::string> errors_type;

      Completion_Counter_Base (unsigned int exec_count,
                               unsigned int fail_count);
      virtual ~Completion_Counter_Base ();

      void  decrement_exec_count ();
      void  increment_fail_count (const char* error);

      unsigned int exec_count ();
      unsigned int fail_count ();

      bool all_completed ();

      const errors_type& errors () const;

    protected:
      void  increment_exec_count ();

      unsigned int exec_count_i ();
      unsigned int fail_count_i ();

      virtual void on_all_completed () = 0;
      virtual void on_all_completed_with_failure () = 0;

    private:
      mutable ACE_LOCK lock_;
      unsigned int exec_count_;
      unsigned int fail_count_;

      errors_type errors_;
    };

  } /* DAnCE */

#if defined (__ACE_INLINE__)
#include "Completion/Completion_Counter_Base.inl"
#endif /* __ACE_INLINE__ */

#if defined (ACE_TEMPLATES_REQUIRE_SOURCE)
#include "Completion/Completion_Counter_Base.cpp"
#endif /* ACE_TEMPLATES_REQUIRE_SOURCE */

#if defined (ACE_TEMPLATES_REQUIRE_PRAGMA)
#pragma implementation ("Completion_Counter_Base.cpp")
#endif /* ACE_TEMPLATES_REQUIRE_PRAGMA */

#include /**/ "ace/post.h"

#endif /* COMPLETION_HANDLER_T_H */
