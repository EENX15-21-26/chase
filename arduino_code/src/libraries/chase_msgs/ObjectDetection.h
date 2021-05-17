#ifndef _ROS_chase_msgs_ObjectDetection_h
#define _ROS_chase_msgs_ObjectDetection_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "ros/time.h"

namespace chase_msgs
{

  class ObjectDetection : public ros::Msg
  {
    public:
      typedef bool _object_found_type;
      _object_found_type object_found;
      typedef int32_t _pos_x_type;
      _pos_x_type pos_x;
      typedef int32_t _pos_y_type;
      _pos_y_type pos_y;
      typedef int32_t _image_x_type;
      _image_x_type image_x;
      typedef int32_t _image_y_type;
      _image_y_type image_y;
      typedef ros::Time _time_stamp_type;
      _time_stamp_type time_stamp;

    ObjectDetection():
      object_found(0),
      pos_x(0),
      pos_y(0),
      image_x(0),
      image_y(0),
      time_stamp()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_object_found;
      u_object_found.real = this->object_found;
      *(outbuffer + offset + 0) = (u_object_found.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->object_found);
      union {
        int32_t real;
        uint32_t base;
      } u_pos_x;
      u_pos_x.real = this->pos_x;
      *(outbuffer + offset + 0) = (u_pos_x.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_pos_x.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_pos_x.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_pos_x.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->pos_x);
      union {
        int32_t real;
        uint32_t base;
      } u_pos_y;
      u_pos_y.real = this->pos_y;
      *(outbuffer + offset + 0) = (u_pos_y.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_pos_y.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_pos_y.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_pos_y.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->pos_y);
      union {
        int32_t real;
        uint32_t base;
      } u_image_x;
      u_image_x.real = this->image_x;
      *(outbuffer + offset + 0) = (u_image_x.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_image_x.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_image_x.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_image_x.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->image_x);
      union {
        int32_t real;
        uint32_t base;
      } u_image_y;
      u_image_y.real = this->image_y;
      *(outbuffer + offset + 0) = (u_image_y.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_image_y.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_image_y.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_image_y.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->image_y);
      *(outbuffer + offset + 0) = (this->time_stamp.sec >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->time_stamp.sec >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->time_stamp.sec >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->time_stamp.sec >> (8 * 3)) & 0xFF;
      offset += sizeof(this->time_stamp.sec);
      *(outbuffer + offset + 0) = (this->time_stamp.nsec >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->time_stamp.nsec >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->time_stamp.nsec >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->time_stamp.nsec >> (8 * 3)) & 0xFF;
      offset += sizeof(this->time_stamp.nsec);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_object_found;
      u_object_found.base = 0;
      u_object_found.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->object_found = u_object_found.real;
      offset += sizeof(this->object_found);
      union {
        int32_t real;
        uint32_t base;
      } u_pos_x;
      u_pos_x.base = 0;
      u_pos_x.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_pos_x.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_pos_x.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_pos_x.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->pos_x = u_pos_x.real;
      offset += sizeof(this->pos_x);
      union {
        int32_t real;
        uint32_t base;
      } u_pos_y;
      u_pos_y.base = 0;
      u_pos_y.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_pos_y.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_pos_y.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_pos_y.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->pos_y = u_pos_y.real;
      offset += sizeof(this->pos_y);
      union {
        int32_t real;
        uint32_t base;
      } u_image_x;
      u_image_x.base = 0;
      u_image_x.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_image_x.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_image_x.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_image_x.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->image_x = u_image_x.real;
      offset += sizeof(this->image_x);
      union {
        int32_t real;
        uint32_t base;
      } u_image_y;
      u_image_y.base = 0;
      u_image_y.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_image_y.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_image_y.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_image_y.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->image_y = u_image_y.real;
      offset += sizeof(this->image_y);
      this->time_stamp.sec =  ((uint32_t) (*(inbuffer + offset)));
      this->time_stamp.sec |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->time_stamp.sec |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->time_stamp.sec |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->time_stamp.sec);
      this->time_stamp.nsec =  ((uint32_t) (*(inbuffer + offset)));
      this->time_stamp.nsec |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->time_stamp.nsec |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->time_stamp.nsec |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->time_stamp.nsec);
     return offset;
    }

    virtual const char * getType() override { return "chase_msgs/ObjectDetection"; };
    virtual const char * getMD5() override { return "c6ddcffc2049fe5484f46687c1dd17db"; };

  };

}
#endif
