#ifndef _ROS_chase_msgs_Move_h
#define _ROS_chase_msgs_Move_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace chase_msgs
{

  class Move : public ros::Msg
  {
    public:
      typedef float _velocity_forward_type;
      _velocity_forward_type velocity_forward;
      typedef float _radius_turn_type;
      _radius_turn_type radius_turn;

    Move():
      velocity_forward(0),
      radius_turn(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_velocity_forward;
      u_velocity_forward.real = this->velocity_forward;
      *(outbuffer + offset + 0) = (u_velocity_forward.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_velocity_forward.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_velocity_forward.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_velocity_forward.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->velocity_forward);
      union {
        float real;
        uint32_t base;
      } u_radius_turn;
      u_radius_turn.real = this->radius_turn;
      *(outbuffer + offset + 0) = (u_radius_turn.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_radius_turn.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_radius_turn.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_radius_turn.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->radius_turn);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_velocity_forward;
      u_velocity_forward.base = 0;
      u_velocity_forward.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_velocity_forward.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_velocity_forward.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_velocity_forward.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->velocity_forward = u_velocity_forward.real;
      offset += sizeof(this->velocity_forward);
      union {
        float real;
        uint32_t base;
      } u_radius_turn;
      u_radius_turn.base = 0;
      u_radius_turn.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_radius_turn.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_radius_turn.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_radius_turn.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->radius_turn = u_radius_turn.real;
      offset += sizeof(this->radius_turn);
     return offset;
    }

    virtual const char * getType() override { return "chase_msgs/Move"; };
    virtual const char * getMD5() override { return "92bef2ed30570eae158dad47cf5749cf"; };

  };

}
#endif
