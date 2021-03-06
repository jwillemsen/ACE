// $Id: DataWriter_T.cpp 95899 2012-06-19 13:47:45Z johnnyw $

#include "dds4ccm/impl/ndds/DataWriter.h"
#include "dds4ccm/impl/ndds/StatusCondition.h"
#include "dds4ccm/impl/ndds/Publisher.h"
#include "dds4ccm/impl/ndds/DataWriterListener.h"
#include "dds4ccm/impl/ndds/Topic.h"

#include "dds4ccm/impl/ndds/convertors/Duration_t.h"
#include "dds4ccm/impl/ndds/convertors/InstanceHandle_t.h"
#include "dds4ccm/impl/ndds/convertors/PublicationMatchedStatus.h"
#include "dds4ccm/impl/ndds/convertors/LivelinessLostStatus.h"
#include "dds4ccm/impl/ndds/convertors/OfferedIncompatibleQosStatus.h"
#include "dds4ccm/impl/ndds/convertors/OfferedDeadlineMissedStatus.h"
#include "dds4ccm/impl/ndds/convertors/InstanceHandleSeq.h"
#include "dds4ccm/impl/ndds/convertors/DataWriterQos.h"
#include "dds4ccm/impl/ndds/convertors/SubscriptionBuiltinTopicData.h"

#include "dds4ccm/impl/logger/Log_Macros.h"

namespace CIAO
{
  namespace NDDS
  {
    template <typename TYPED_DDS_WRITER, typename TYPED_WRITER_TYPE, typename VALUE_TYPE>
    DataWriter_T<TYPED_DDS_WRITER, TYPED_WRITER_TYPE, VALUE_TYPE>::DataWriter_T (
      ::DDSDataWriter * dw,
      ::DDS::DomainParticipant_ptr dp,
      ::DDS::Publisher_ptr pub)
      : rti_entity_ (0)
        , dp_ (::DDS::DomainParticipant::_duplicate (dp))
        , pub_ (::DDS::Publisher::_duplicate (pub))
    {
      if (dw)
        {
          this->rti_entity_ = TYPED_DDS_WRITER::narrow (dw);
        }
    }

    template <typename TYPED_DDS_WRITER, typename TYPED_WRITER_TYPE, typename VALUE_TYPE>
    ::DDS::ReturnCode_t
    DataWriter_T<TYPED_DDS_WRITER, TYPED_WRITER_TYPE, VALUE_TYPE>::set_qos (const ::DDS::DataWriterQos & qos)
    {
      DDS4CCM_TRACE ("DataWriter_T<TYPED_DDS_WRITER, TYPED_WRITER_TYPE, VALUE_TYPE>::set_qos");
      ::DDS_DataWriterQos ccm_dds_qos;
      DDS_ReturnCode_t const retcode = this->rti_entity ()->get_qos (ccm_dds_qos);
      if (retcode != DDS_RETCODE_OK)
        {
          DDS4CCM_ERROR (DDS4CCM_LOG_LEVEL_ERROR, (LM_ERROR, DDS4CCM_INFO
                        "DataWriter_T<TYPED_DDS_WRITER, TYPED_WRITER_TYPE, VALUE_TYPE>::set_qos - "
                        "Error: Unable to retrieve qos\n"));
          return retcode;
        }
      ccm_dds_qos <<= qos;
      return this->rti_entity ()->set_qos (ccm_dds_qos);
    }

    template <typename TYPED_DDS_WRITER, typename TYPED_WRITER_TYPE, typename VALUE_TYPE>
    ::DDS::ReturnCode_t
    DataWriter_T<TYPED_DDS_WRITER, TYPED_WRITER_TYPE, VALUE_TYPE>::get_qos (::DDS::DataWriterQos & qos)
    {
      DDS4CCM_TRACE ("DataWriter_T<TYPED_DDS_WRITER, TYPED_WRITER_TYPE, VALUE_TYPE>::get_qos");
      ::DDS_DataWriterQos ccm_dds_qos;
      ccm_dds_qos <<= qos;
      ::DDS::ReturnCode_t const retcode =
        this->rti_entity ()->get_qos (ccm_dds_qos);
      qos <<= ccm_dds_qos;
      return retcode;
    }

    template <typename TYPED_DDS_WRITER, typename TYPED_WRITER_TYPE, typename VALUE_TYPE>
    ::DDS::ReturnCode_t
    DataWriter_T<TYPED_DDS_WRITER, TYPED_WRITER_TYPE, VALUE_TYPE>::set_listener (
      ::DDS::DataWriterListener_ptr a_listener,
      ::DDS::StatusMask mask)
    {
      DDS4CCM_TRACE ("DataWriter_T<TYPED_DDS_WRITER, TYPED_WRITER_TYPE, VALUE_TYPE>::set_listener");

      // Retrieve the previously set listener
      DDSDataWriterListener *old_listener = this->rti_entity ()->get_listener ();

      DDSDataWriterListener *listener = 0;
      if (! ::CORBA::is_nil (a_listener))
        {
          ACE_NEW_THROW_EX (listener,
                            DDS_DataWriterListener_i (
                              a_listener,
                              this),
                            ::CORBA::NO_MEMORY ());
        }

      ::DDS::ReturnCode_t const retcode =
        this->rti_entity ()->set_listener (listener, mask);

      if (retcode != ::DDS::RETCODE_OK)
        {
          delete listener;
        }
      else
        {
          delete old_listener;
        }

      return retcode;
    }

    template <typename TYPED_DDS_WRITER, typename TYPED_WRITER_TYPE, typename VALUE_TYPE>
    ::DDS::DataWriterListener_ptr
    DataWriter_T<TYPED_DDS_WRITER, TYPED_WRITER_TYPE, VALUE_TYPE>::get_listener (void)
    {
      DDS4CCM_TRACE ("DataWriter_T<TYPED_DDS_WRITER, TYPED_WRITER_TYPE, VALUE_TYPE>::get_listener");

      DDSDataWriterListener *wr = this->rti_entity ()->get_listener ();
      DDS_DataWriterListener_i * list_proxy =
        dynamic_cast <DDS_DataWriterListener_i *> (wr);
      if (!list_proxy)
        {
          DDS4CCM_DEBUG (DDS4CCM_LOG_LEVEL_ACTION, (LM_DEBUG,
                        "DataWriter_T<TYPED_DDS_WRITER, TYPED_WRITER_TYPE, VALUE_TYPE>::get_listener - "
                        "DDS returned a NIL listener.\n"));
          return ::DDS::DataWriterListener::_nil ();
        }
      return list_proxy->get_datawriterlistener ();
    }

    template <typename TYPED_DDS_WRITER, typename TYPED_WRITER_TYPE, typename VALUE_TYPE>
    ::DDS::Topic_ptr
    DataWriter_T<TYPED_DDS_WRITER, TYPED_WRITER_TYPE, VALUE_TYPE>::get_topic (void)
    {
      DDS4CCM_TRACE ("DataWriter_T<TYPED_DDS_WRITER, TYPED_WRITER_TYPE, VALUE_TYPE>::get_topic");

      ::DDS::Topic_var retval;
      DDSTopic* t = this->rti_entity ()->get_topic ();
      ACE_NEW_THROW_EX (retval,
                        DDS_Topic_i (t, this->dp_.in ()),
                        ::CORBA::NO_MEMORY ());
      return retval._retn ();
    }

    template <typename TYPED_DDS_WRITER, typename TYPED_WRITER_TYPE, typename VALUE_TYPE>
    ::DDS::Publisher_ptr
    DataWriter_T<TYPED_DDS_WRITER, TYPED_WRITER_TYPE, VALUE_TYPE>::get_publisher (void)
    {
      DDS4CCM_TRACE ("DataWriter_T<TYPED_DDS_WRITER, TYPED_WRITER_TYPE, VALUE_TYPE>::get_publisher");

      return ::DDS::Publisher::_duplicate (this->pub_.in ());
    }

    template <typename TYPED_DDS_WRITER, typename TYPED_WRITER_TYPE, typename VALUE_TYPE>
    ::DDS::ReturnCode_t
    DataWriter_T<TYPED_DDS_WRITER, TYPED_WRITER_TYPE, VALUE_TYPE>::wait_for_acknowledgments (const ::DDS::Duration_t & max_wait)
    {
      DDS4CCM_TRACE ("DataWriter_T<TYPED_DDS_WRITER, TYPED_WRITER_TYPE, VALUE_TYPE>::wait_for_acknowledgments");

      ::DDS_Duration_t rtiduration;
     rtiduration <<= max_wait;
     return this->rti_entity ()->wait_for_acknowledgments (rtiduration);
    }

    template <typename TYPED_DDS_WRITER, typename TYPED_WRITER_TYPE, typename VALUE_TYPE>
    ::DDS::ReturnCode_t
    DataWriter_T<TYPED_DDS_WRITER, TYPED_WRITER_TYPE, VALUE_TYPE>::get_liveliness_lost_status (::DDS::LivelinessLostStatus & status)
    {
      DDS4CCM_TRACE ("DataWriter_T<TYPED_DDS_WRITER, TYPED_WRITER_TYPE, VALUE_TYPE>::get_liveliness_lost_status");

      ::DDS_LivelinessLostStatus ddsstatus;
      ddsstatus <<= status;
      ::DDS::ReturnCode_t const retval =
        this->rti_entity ()->get_liveliness_lost_status (ddsstatus);
      status <<= ddsstatus;
      return retval;
    }

    template <typename TYPED_DDS_WRITER, typename TYPED_WRITER_TYPE, typename VALUE_TYPE>
    ::DDS::ReturnCode_t
    DataWriter_T<TYPED_DDS_WRITER, TYPED_WRITER_TYPE, VALUE_TYPE>::get_offered_deadline_missed_status (
      ::DDS::OfferedDeadlineMissedStatus & status)
    {
      DDS4CCM_TRACE ("DataWriter_T<TYPED_DDS_WRITER, TYPED_WRITER_TYPE, VALUE_TYPE>::get_offered_deadline_missed_status");

      ::DDS_OfferedDeadlineMissedStatus ddsstatus;
      ddsstatus <<= status;
      ::DDS::ReturnCode_t const retval =
        this->rti_entity ()->get_offered_deadline_missed_status (ddsstatus);
      status <<= ddsstatus;
      return retval;
    }

    template <typename TYPED_DDS_WRITER, typename TYPED_WRITER_TYPE, typename VALUE_TYPE>
    ::DDS::ReturnCode_t
    DataWriter_T<TYPED_DDS_WRITER, TYPED_WRITER_TYPE, VALUE_TYPE>::get_offered_incompatible_qos_status (
      ::DDS::OfferedIncompatibleQosStatus & status)
    {
      DDS4CCM_TRACE ("DataWriter_T<TYPED_DDS_WRITER, TYPED_WRITER_TYPE, VALUE_TYPE>::get_offered_incompatible_qos_status");

      ::DDS_OfferedIncompatibleQosStatus ddsstatus;
      ddsstatus <<= status;
      ::DDS::ReturnCode_t const retval =
        this->rti_entity ()->get_offered_incompatible_qos_status (ddsstatus);
      status <<= ddsstatus;
      return retval;
    }

    template <typename TYPED_DDS_WRITER, typename TYPED_WRITER_TYPE, typename VALUE_TYPE>
    ::DDS::ReturnCode_t
    DataWriter_T<TYPED_DDS_WRITER, TYPED_WRITER_TYPE, VALUE_TYPE>::get_publication_matched_status (
      ::DDS::PublicationMatchedStatus & status)
    {
      DDS4CCM_TRACE ("DataWriter_T<TYPED_DDS_WRITER, TYPED_WRITER_TYPE, VALUE_TYPE>::get_publication_matched_status");

      ::DDS_PublicationMatchedStatus ddsstatus;
      ddsstatus <<= status;
      ::DDS::ReturnCode_t const retval =
        this->rti_entity ()->get_publication_matched_status (ddsstatus);
      status <<= ddsstatus;
      return retval;
    }

    template <typename TYPED_DDS_WRITER, typename TYPED_WRITER_TYPE, typename VALUE_TYPE>
    ::DDS::ReturnCode_t
    DataWriter_T<TYPED_DDS_WRITER, TYPED_WRITER_TYPE, VALUE_TYPE>::assert_liveliness (void)
    {
      DDS4CCM_TRACE ("DataWriter_T<TYPED_DDS_WRITER, TYPED_WRITER_TYPE, VALUE_TYPE>::assert_liveliness");

      return this->rti_entity ()->assert_liveliness ();
    }

    template <typename TYPED_DDS_WRITER, typename TYPED_WRITER_TYPE, typename VALUE_TYPE>
    ::DDS::ReturnCode_t
    DataWriter_T<TYPED_DDS_WRITER, TYPED_WRITER_TYPE, VALUE_TYPE>::get_matched_subscriptions (
      ::DDS::InstanceHandleSeq & subscription_handles)
    {
      DDS4CCM_TRACE ("DataWriter_T<TYPED_DDS_WRITER, TYPED_WRITER_TYPE, VALUE_TYPE>::get_matched_subscription");

      ::DDS_InstanceHandleSeq rtiseq;
      rtiseq <<= subscription_handles;
      ::DDS::ReturnCode_t const retval =
        this->rti_entity ()->get_matched_subscriptions (rtiseq);
      subscription_handles <<= rtiseq;
      return retval;
    }

    template <typename TYPED_DDS_WRITER, typename TYPED_WRITER_TYPE, typename VALUE_TYPE>
    ::DDS::ReturnCode_t
    DataWriter_T<TYPED_DDS_WRITER, TYPED_WRITER_TYPE, VALUE_TYPE>::get_matched_subscription_data (
      ::DDS::SubscriptionBuiltinTopicData & subscription_data,
      DDS_INSTANCE_HANDLE_T_IN subscription_handle)
    {
      DDS4CCM_TRACE ("DataWriter_T<TYPED_DDS_WRITER, TYPED_WRITER_TYPE, VALUE_TYPE>::get_matched_subscription_data");

      ::DDS_SubscriptionBuiltinTopicData ccm_dds_sub_data;
      ::DDS_InstanceHandle_t ccm_dds_sub_handle;
      ccm_dds_sub_handle <<= subscription_handle;
      ::DDS::ReturnCode_t const retval =
        this->rti_entity ()->get_matched_subscription_data (ccm_dds_sub_data,
                                                            ccm_dds_sub_handle);
      subscription_data <<= ccm_dds_sub_data;
      return retval;
    }

    template <typename TYPED_DDS_WRITER, typename TYPED_WRITER_TYPE, typename VALUE_TYPE>
    ::DDS::ReturnCode_t
    DataWriter_T<TYPED_DDS_WRITER, TYPED_WRITER_TYPE, VALUE_TYPE>::enable (void)
    {
      DDS4CCM_TRACE ("DataWriter_T<TYPED_DDS_WRITER, TYPED_WRITER_TYPE, VALUE_TYPE>::enable");

      return this->rti_entity ()->enable ();
    }

    template <typename TYPED_DDS_WRITER, typename TYPED_WRITER_TYPE, typename VALUE_TYPE>
    ::DDS::StatusCondition_ptr
    DataWriter_T<TYPED_DDS_WRITER, TYPED_WRITER_TYPE, VALUE_TYPE>::get_statuscondition (void)
    {
      DDS4CCM_TRACE ("DataWriter_T<TYPED_DDS_WRITER, TYPED_WRITER_TYPE, VALUE_TYPE>::get_statuscondition");

      ::DDS::StatusCondition_var retval;
      DDSStatusCondition* sc = this->rti_entity ()->get_statuscondition ();
      ACE_NEW_THROW_EX (retval,
                        DDS_StatusCondition_i (sc, this->dp_.in ()),
                        ::CORBA::NO_MEMORY ());
      return retval._retn ();
    }

    template <typename TYPED_DDS_WRITER, typename TYPED_WRITER_TYPE, typename VALUE_TYPE>
    ::DDS::StatusMask
    DataWriter_T<TYPED_DDS_WRITER, TYPED_WRITER_TYPE, VALUE_TYPE>::get_status_changes (void)
    {
      DDS4CCM_TRACE ("DataWriter_T<TYPED_DDS_WRITER, TYPED_WRITER_TYPE, VALUE_TYPE>::get_status_changes");

      return this->rti_entity ()->get_status_changes ();
    }

    template <typename TYPED_DDS_WRITER, typename TYPED_WRITER_TYPE, typename VALUE_TYPE>
    DDS_INSTANCE_HANDLE_T_RETN
    DataWriter_T<TYPED_DDS_WRITER, TYPED_WRITER_TYPE, VALUE_TYPE>::get_instance_handle (void)
    {
      DDS4CCM_TRACE ("DataWriter_T<TYPED_DDS_WRITER, TYPED_WRITER_TYPE, VALUE_TYPE>::get_instance_handle");

      ::DDS_InstanceHandle_t const rtihandle =
        this->rti_entity ()->get_instance_handle ();
      ::DDS::InstanceHandle_t handle;
      handle <<= rtihandle;
      return handle;
    }

    template <typename TYPED_DDS_WRITER, typename TYPED_WRITER_TYPE, typename VALUE_TYPE>
    ::DDS::InstanceHandle_t
    DataWriter_T<TYPED_DDS_WRITER, TYPED_WRITER_TYPE, VALUE_TYPE>::register_instance (
        const VALUE_TYPE & instance_data)
    {
      DDS4CCM_TRACE ("DataWriter_T<TYPED_DDS_WRITER, TYPED_WRITER_TYPE, VALUE_TYPE>::register_instance");

      ::DDS::InstanceHandle_t dds_handle;
      ::DDS_InstanceHandle_t const handle = this->rti_entity ()->register_instance (instance_data);
      dds_handle <<= handle;
      return dds_handle;
    }

    template <typename TYPED_DDS_WRITER, typename TYPED_WRITER_TYPE, typename VALUE_TYPE>
    ::DDS::InstanceHandle_t
    DataWriter_T<TYPED_DDS_WRITER, TYPED_WRITER_TYPE, VALUE_TYPE>::register_instance_w_timestamp (
        const VALUE_TYPE & instance_data,
        const ::DDS::Time_t & source_timestamp)
    {
      DDS4CCM_TRACE ("DataWriter_T<TYPED_DDS_WRITER, TYPED_WRITER_TYPE, VALUE_TYPE>::register_instance_w_timestamp");

      ::DDS_Time_t time;
      time <<= source_timestamp;
      ::DDS_InstanceHandle_t const rtihandle =
        this->rti_entity ()->register_instance_w_timestamp (instance_data, time);
      ::DDS::InstanceHandle_t handle;
      handle <<= rtihandle;
      return handle;
    }

    template <typename TYPED_DDS_WRITER, typename TYPED_WRITER_TYPE, typename VALUE_TYPE>
    ::DDS::ReturnCode_t
    DataWriter_T<TYPED_DDS_WRITER, TYPED_WRITER_TYPE, VALUE_TYPE>::unregister_instance (
        const VALUE_TYPE & instance_data,
        const ::DDS::InstanceHandle_t & handle)
    {
      DDS4CCM_TRACE ("DataWriter_T<TYPED_DDS_WRITER, TYPED_WRITER_TYPE, VALUE_TYPE>::unregister_instance");

      ::DDS_InstanceHandle_t instance_handle = ::DDS_HANDLE_NIL;
      instance_handle <<= handle;
      return this->rti_entity ()->unregister_instance (instance_data, instance_handle);
    }

    template <typename TYPED_DDS_WRITER, typename TYPED_WRITER_TYPE, typename VALUE_TYPE>
    ::DDS::ReturnCode_t
    DataWriter_T<TYPED_DDS_WRITER, TYPED_WRITER_TYPE, VALUE_TYPE>::unregister_instance_w_timestamp (
        const VALUE_TYPE & instance_data,
        const ::DDS::InstanceHandle_t & handle,
        const ::DDS::Time_t & source_timestamp)
    {
      DDS4CCM_TRACE ("DataWriter_T<TYPED_DDS_WRITER, TYPED_WRITER_TYPE, VALUE_TYPE>::unregister_instance_w_timestamp");

      ::DDS_InstanceHandle_t instance_handle = ::DDS_HANDLE_NIL;
      instance_handle <<= handle;
      ::DDS_Time_t time;
      time <<= source_timestamp;
      return this->rti_entity ()->unregister_instance_w_timestamp (instance_data,
                                                                   instance_handle,
                                                                   time);
    }

    template <typename TYPED_DDS_WRITER, typename TYPED_WRITER_TYPE, typename VALUE_TYPE>
    ::DDS::ReturnCode_t
    DataWriter_T<TYPED_DDS_WRITER, TYPED_WRITER_TYPE, VALUE_TYPE>::write (
        const VALUE_TYPE & instance_data,
        const ::DDS::InstanceHandle_t & handle)
    {
      DDS4CCM_TRACE ("DataWriter_T<TYPED_DDS_WRITER, TYPED_WRITER_TYPE, VALUE_TYPE>::write");

      ::DDS_InstanceHandle_t instance_handle = ::DDS_HANDLE_NIL;
      instance_handle <<= handle;
      return this->rti_entity ()->write (instance_data, instance_handle);
    }

    template <typename TYPED_DDS_WRITER, typename TYPED_WRITER_TYPE, typename VALUE_TYPE>
    ::DDS::ReturnCode_t
    DataWriter_T<TYPED_DDS_WRITER, TYPED_WRITER_TYPE, VALUE_TYPE>::write_w_timestamp (
        const VALUE_TYPE & instance_data,
        const ::DDS::InstanceHandle_t & handle,
        const ::DDS::Time_t & source_timestamp)
    {
      DDS4CCM_TRACE ("DataWriter_T<TYPED_DDS_WRITER, TYPED_WRITER_TYPE, VALUE_TYPE>::write_w_timestamp");

      ::DDS_InstanceHandle_t instance_handle = ::DDS_HANDLE_NIL;
      instance_handle <<= handle;
      ::DDS_Time_t time;
      time <<= source_timestamp;
      return this->rti_entity ()->write_w_timestamp (instance_data,
                                                     instance_handle,
                                                     time);
    }

    template <typename TYPED_DDS_WRITER, typename TYPED_WRITER_TYPE, typename VALUE_TYPE>
     ::DDS::ReturnCode_t
     DataWriter_T<TYPED_DDS_WRITER, TYPED_WRITER_TYPE, VALUE_TYPE>::dispose (
        const VALUE_TYPE & instance_data,
        const ::DDS::InstanceHandle_t & handle)
    {
      DDS4CCM_TRACE ("DataWriter_T<TYPED_DDS_WRITER, TYPED_WRITER_TYPE, VALUE_TYPE>::dispose");

      ::DDS_InstanceHandle_t instance_handle = ::DDS_HANDLE_NIL;
      instance_handle <<= handle;
      return this->rti_entity ()->dispose (instance_data, instance_handle);
    }

    template <typename TYPED_DDS_WRITER, typename TYPED_WRITER_TYPE, typename VALUE_TYPE>
    ::DDS::ReturnCode_t
    DataWriter_T<TYPED_DDS_WRITER, TYPED_WRITER_TYPE, VALUE_TYPE>::dispose_w_timestamp (
        const VALUE_TYPE & instance_data,
        const ::DDS::InstanceHandle_t & handle,
        const ::DDS::Time_t & source_timestamp)
    {
      DDS4CCM_TRACE ("DataWriter_T<TYPED_DDS_WRITER, TYPED_WRITER_TYPE, VALUE_TYPE>::dispose_w_timestamp");

      ::DDS_InstanceHandle_t instance_handle = ::DDS_HANDLE_NIL;
      instance_handle <<= handle;
      ::DDS_Time_t time;
      time <<= source_timestamp;
      return this->rti_entity ()->dispose_w_timestamp (instance_data,
                                                       instance_handle,
                                                       time);
    }

    template <typename TYPED_DDS_WRITER, typename TYPED_WRITER_TYPE, typename VALUE_TYPE>
    ::DDS::ReturnCode_t
    DataWriter_T<TYPED_DDS_WRITER, TYPED_WRITER_TYPE, VALUE_TYPE>::get_key_value (
        VALUE_TYPE & key_holder,
        const ::DDS::InstanceHandle_t & handle)
    {
      DDS4CCM_TRACE ("DataWriter_T<TYPED_DDS_WRITER, TYPED_WRITER_TYPE, VALUE_TYPE>::get_key_value");

      ::DDS_InstanceHandle_t instance_handle = ::DDS_HANDLE_NIL;
      instance_handle <<= handle;
      return this->rti_entity ()->get_key_value (key_holder, instance_handle);
    }

    template <typename TYPED_DDS_WRITER, typename TYPED_WRITER_TYPE, typename VALUE_TYPE>
    ::DDS::InstanceHandle_t
    DataWriter_T<TYPED_DDS_WRITER, TYPED_WRITER_TYPE, VALUE_TYPE>::lookup_instance (
        const VALUE_TYPE & instance_data)
    {
      DDS4CCM_TRACE ("DataWriter_T<TYPED_DDS_WRITER, TYPED_WRITER_TYPE, VALUE_TYPE>::lookup_instance");

      ::DDS_InstanceHandle_t const rtihandle =
        this->rti_entity ()->lookup_instance (instance_data);
      ::DDS::InstanceHandle_t handle = DDS::HANDLE_NIL;
      handle <<= rtihandle;
      return handle;
    }

    template <typename TYPED_DDS_WRITER, typename TYPED_WRITER_TYPE, typename VALUE_TYPE>
    void
    DataWriter_T<TYPED_DDS_WRITER, TYPED_WRITER_TYPE, VALUE_TYPE>::set_rti_entity (DDSDataWriter * dw)
    {
      if (dw)
        {
          this->rti_entity_ = TYPED_DDS_WRITER::narrow (dw);
        }
      else
        {
          this->rti_entity_ = 0;
        }
    }

    template <typename TYPED_DDS_WRITER, typename TYPED_WRITER_TYPE, typename VALUE_TYPE>
    DDSDataWriter *
    DataWriter_T<TYPED_DDS_WRITER, TYPED_WRITER_TYPE, VALUE_TYPE>::get_rti_entity (void)
    {
      return this->rti_entity_;
    }

    template <typename TYPED_DDS_WRITER, typename TYPED_WRITER_TYPE, typename VALUE_TYPE>
    TYPED_DDS_WRITER*
    DataWriter_T<TYPED_DDS_WRITER, TYPED_WRITER_TYPE, VALUE_TYPE>::rti_entity (void)
    {
      if (!this->rti_entity_)
        {
          DDS4CCM_DEBUG (DDS4CCM_LOG_LEVEL_ACTION, (LM_DEBUG,
                        "DataWriter_T<TYPED_DDS_WRITER, TYPED_WRITER_TYPE, VALUE_TYPE>::rti_entity - "
                        "Throwing BAD_INV_ORDER.\n"));
          throw ::CORBA::BAD_INV_ORDER ();
        }
      return this->rti_entity_;
    }

  }
}
