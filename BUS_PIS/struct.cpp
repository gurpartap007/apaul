#include "struct.h"

//ROUTE RELATED STRUCTURES
struct path_struct route_path;

//GPS RELATED STRUCTURE
union gps_union gps;

//OUTAGE STRUCTURE
struct outage_dist_struct out_dist;

//STRUCTURE USED FOR SYSTEM OPERATION
struct sys_struct sys;
//struct sys_tmr_struct sys_tmr;
//union user_ip_flags_union user_ip;

//COMMUNICATION BETWEEN CPU AND SLAVES
struct comm_struct cpu_comm;
union rxtx_frame_union rx;
union rxtx_frame_union tx;
//struct frames_struct frames;

//COMMUNICATION BETWEEN BDU AND SCU
UNION_BUFF_SYSTEM_INFO sys_info;

//DISPLAY COMMUNICATION
extern MESSAGE msg;

uinteger act_stn_dist[MAX_STNS_PER_BUS];
sinteger mul_factor[MAX_STNS_PER_BUS];
