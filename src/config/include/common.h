#ifndef CONFIGURE_COMMON_H_
#define CONFIGURE_COMMON_H_

enum NodeFlag{ACTION=1,COMM,CONFIG,DEVICE,SENSOR,UPGRADE};
enum EngineFlag{CHARGE=1,DRIVE,WORK,LOCAL,SERIAL,VERSION};

typedef unsigned char       uint8;
typedef signed char         sint8;
typedef unsigned short      uint16;
typedef signed short        sint16;
typedef unsigned int        uint32;
typedef signed int          sint32;
typedef unsigned long       ulng32;
typedef signed long         slng32;
typedef signed long long    sint64;
typedef unsigned long long  uint64;

#endif
