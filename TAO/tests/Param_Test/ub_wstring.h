
//=============================================================================
/**
 *  @file    ub_wstring.h
 *
 *  $Id: ub_wstring.h 93650 2011-03-28 08:44:53Z johnnyw $
 *
 *   Tests unbounded wide string
 *
 *
 *  @author   Jeff Parsons <parsons@cs.wustl.edu>
 */
//=============================================================================


#ifndef PARAM_TEST_UNBOUNDED_WSTRING_H
#define PARAM_TEST_UNBOUNDED_WSTRING_H

#include "param_testC.h"

// =*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
//                        test unbounded wide strings
// =*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
class Test_Unbounded_WString
{
public:
  /// ctor
  Test_Unbounded_WString (void);

  /// dtor
  ~Test_Unbounded_WString (void);

  /// run the SII test
  int run_sii_test (Param_Test_ptr objref);

  /// return operation name
  const char *opname (void) const;

  /// set values for parameters
  int init_parameters (Param_Test_ptr objref);

  /// reset values for CORBA
  int reset_parameters (void);

  /// check if results are valid
  CORBA::Boolean check_validity (void);

  /// check if results are valid. This is used for DII results
  CORBA::Boolean check_validity (CORBA::Request_ptr req);

  /// print all the values
  void print_values (void);

  /// invoke DII request with appropriate exception handling.
  void dii_req_invoke (CORBA::Request *);

private:
  /// operation name
  char *opname_;

  /// in parameter
  CORBA::WChar *in_;

  /// inout parameter
  CORBA::WChar *inout_;

  /// out parameter
  CORBA::WChar *out_;

  /// return value
  CORBA::WChar *ret_;
};

#endif /* PARAM_TEST_UNBOUNDED_WSTRING_H */
