#ifndef _ROS_chase_msgs_ControlMode_h
#define _ROS_chase_msgs_ControlMode_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace chase_msgs
{

  class ControlMode : public ros::Msg
  {
    public:
      typedef const char* _control_mode_type;
      _control_mode_type control_mode;
      enum { MANUAL_MOVE_MODE =  "MANUAL_MOVE_MODE" };
      enum { FIND_OBJECT_MODE =  "FIND_OBJECT_MODE" };
      enum { SLEEP_MODE =  "SLEEP_MODE" };

    ControlMode():
      control_mode("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      uint32_t length_control_mode = strlen(this->control_mode);
      varToArr(outbuffer + offset, length_control_mode);
      offset += 4;
      memcpy(outbuffer + offset, this->control_mode, length_control_mode);
      offset += length_control_mode;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      uint32_t length_control_mode;
      arrToVar(length_control_mode, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_control_mode; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_control_mode-1]=0;
      this->control_mode = (char *)(inbuffer + offset-1);
      offset += length_control_mode;
     return offset;
    }

    virtual const char * getType() override { return "chase_msgs/ControlMode"; };
    virtual const char * getMD5() override { return "0ff0099baab72b3e9b1f252fdcc57470"; };

  };

}
#endif
