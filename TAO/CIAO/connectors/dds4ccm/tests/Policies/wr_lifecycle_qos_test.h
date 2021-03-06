//$Id: wr_lifecycle_qos_test.h 92430 2010-10-30 07:02:24Z msmit $

#ifndef WRITER_DATA_LIFECYCLE_QOS_TEST_H_
#define WRITER_DATA_LIFECYCLE_QOS_TEST_H_

#include "dds4ccm/idl/dds_rtf2_dcpsC.h"
#include "ndds/ndds_cpp.h"
#include "dds4ccm/impl/ndds/convertors/WriterDataLifecycleQosPolicy.h"

class WriterDataLifecyclePolicyTest
{
public:
  WriterDataLifecyclePolicyTest ();

  static bool check (const ::DDS_WriterDataLifecycleQosPolicy & dds_qos,
                     const ::DDS::WriterDataLifecycleQosPolicy & qos);
};

#endif /* WRITER_DATA_LIFECYCLE_QOS_TEST_H_ */
