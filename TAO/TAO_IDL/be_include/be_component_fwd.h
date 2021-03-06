/* -*- c++ -*- */

//=============================================================================
/**
 *  @file    be_component_fwd.h
 *
 *  $Id: be_component_fwd.h 89076 2010-02-18 22:54:36Z parsons $
 *
 *  Extension of class AST_ComponentFwd that provides additional
 *  means for C++ mapping of a forward declared component.
 *
 *
 *  @author Jeff Parsons
 */
//=============================================================================

#ifndef BE_COMPONENT_FWD_H
#define BE_COMPONENT_FWD_H

#include "be_interface_fwd.h"
#include "ast_component_fwd.h"

class be_component_fwd : public virtual AST_ComponentFwd,
                         public virtual be_interface_fwd
{
  // =TITLE
  //   be_component_fwd
  //
  // =DESCRIPTION
  //   Extensions to the AST_ComponentFwd class
public:
  be_component_fwd (AST_Interface *dummy,
                    UTL_ScopedName *n);

  virtual ~be_component_fwd (void);

  // Cleanup function.
  virtual void destroy (void);

  // Visiting.
  virtual int accept (be_visitor* visitor);

  // Narrowing.

  DEF_NARROW_FROM_DECL (be_component_fwd);
};

#endif // if !defined
