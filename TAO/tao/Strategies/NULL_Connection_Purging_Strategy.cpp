// $Id: NULL_Connection_Purging_Strategy.cpp 92240 2010-10-17 12:26:24Z johnnyw $

#include "tao/Strategies/NULL_Connection_Purging_Strategy.h"
#include "tao/Transport.h"

TAO_BEGIN_VERSIONED_NAMESPACE_DECL

TAO_NULL_Connection_Purging_Strategy::TAO_NULL_Connection_Purging_Strategy (
                                                           int cache_maximum)
 : TAO_Connection_Purging_Strategy (cache_maximum)
{
}

void
TAO_NULL_Connection_Purging_Strategy::update_item (TAO_Transport&)
{
}

int
TAO_NULL_Connection_Purging_Strategy::cache_maximum (void) const
{
  return -1;
}

TAO_END_VERSIONED_NAMESPACE_DECL
