#ifndef _ROS_chase_msgs_ChaseArduino_h
#define _ROS_chase_msgs_ChaseArduino_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace chase_msgs
{

  class ChaseArduino : public ros::Msg
  {
    public:
      typedef int32_t _mode_type;
      _mode_type mode;
      float params[5];

    ChaseArduino():
      mode(0),
      params()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_mode;
      u_mode.real = this->mode;
      *(outbuffer + offset + 0) = (u_mode.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_mode.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_mode.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_mode.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->mode);
      for( uint32_t i = 0; i < 5; i++){
      union {
        float real;
        uint32_t base;
      } u_paramsi;
      u_paramsi.real = this->params[i];
      *(outbuffer + offset + 0) = (u_paramsi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_paramsi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_paramsi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_paramsi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->params[i]);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_mode;
      u_mode.base = 0;
      u_mode.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_mode.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_mode.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_mode.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->mode = u_mode.real;
      offset += sizeof(this->mode);
      for( uint32_t i = 0; i < 5; i++){
      union {
        float real;
        uint32_t base;
      } u_paramsi;
      u_paramsi.base = 0;
      u_paramsi.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_paramsi.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_paramsi.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_paramsi.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->params[i] = u_paramsi.real;
      offset += sizeof(this->params[i]);
      }
     return offset;
    }

    virtual const char * getType() override { return "chase_msgs/ChaseArduino"; };
    virtual const char * getMD5() override { return "48d445e4ce578543c3d93225ff9938a0"; };

  };

}
#endif
