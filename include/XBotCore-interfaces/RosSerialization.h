#ifndef __SONO_LA_GUARDIA_DI_ROS_SERIALIZATION_H__
#define __SONO_LA_GUARDIA_DI_ROS_SERIALIZATION_H__

#include <ros/ros.h>
#include <sensor_msgs/JointState.h>
#include <array>

namespace XBot {

    template <typename RosMessageType, int MaxSizeBytes = 1024>
    class RosMessageWrapper {

    public:

        RosMessageWrapper():_is_valid(false), _serialization_length(0) {}

        bool wrap(const RosMessageType& ros_msg)
        {
            /* Get message length in bytes */
            _serialization_length = ros::serialization::serializationLength(ros_msg);

            /* If message exceeds buffer size, return */
            if( _serialization_length > MaxSizeBytes ){
                _serialization_length = 0;
                _is_valid = false;
                return false;
            }

            ros::serialization::OStream stream(_bytes, _serialization_length);
            ros::serialization::serialize(stream, ros_msg);
            _is_valid = true;

            return true;
        }

        bool getMessage(RosMessageType& msg)
        {
            if( !_is_valid ) return false;

            // Fill buffer with a serialized UInt32
            ros::serialization::IStream stream(_bytes, _serialization_length);
            ros::serialization::Serializer<RosMessageType>::read(stream, msg);

            return true;

        }



    private:

        bool _is_valid;
        uint8_t _bytes[MaxSizeBytes];
        uint32_t _serialization_length;

    };

}

#endif