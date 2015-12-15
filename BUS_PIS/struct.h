enum device_enum
{
    DDC,
    DISPLAY,
    AMPLIFIER,
    CAMRA,
    MICROPHONE,
    GPS,
    GPRS
};

//#######################################################################################
//			TYPEDEF AVAILABLE IN THE LIBRARY
//#######################################################################################
typedef    unsigned char ubyte;
typedef    char sbyte;
typedef	unsigned short uinteger;
typedef	int sinteger;
typedef	unsigned long uword;
typedef	long int sword;
typedef	const unsigned char urombyte;
typedef	const char srombyte;
typedef	const unsigned short uromint;
typedef	const int sromint;
typedef    urombyte *const uromptr;
typedef    srombyte *const sromptr;
typedef    ubyte *const uramptr;
typedef    sbyte *const sramptr;
typedef    long double lword;

#define	SIZE_GPS_RMC_MSG					(uinteger)96
#define	DIG_STN_CODE						(uinteger)6
#define	DIG_MAX_ROUTE_NUM_LEN				(uinteger)6
#define	DIG_MAX_PATH_DESC_LEN				(uinteger)96
#define	DIG_MAX_PATH_CODE_LEN				(uinteger)6
#define	MAX_DEV_CODE_LEN                    (uinteger)6
#define	MAX_DEV_DESC_LEN                    (uinteger)96
#define   MAX_DEVICES_IN_SYSTEM               (uinteger)20
#define	DIG_BUS_NAME						(uinteger)48
#define	DIG_STN_NAME						(uinteger)96
#define   DIG_STN_TYPE                        (uinteger)96
#define	MAX_STNS_PER_BUS    				(uinteger)96
#define	STX_STR								"STX"
#define	ETX_STR								"ETX"
#define	L_STX								(uinteger)(sizeof(STX_STR)-1)
#define	L_FR_LEN							(uinteger)5
#define	L_DEV_ID							(uinteger)5
#define	L_DEV_PORT							(uinteger)2
#define	L_FUNC_CODE							(uinteger)3
#define	L_DATA								(uinteger)900
#define	L_DATA_BIG							(uinteger)(9*1024)
#define	L_CRC								(uinteger)7
#define	L_ETX								(uinteger)(sizeof(ETX_STR)-1)
#define	L_FRAME_INIT						(uinteger)(L_STX+L_FR_LEN+L_SRC_ID+L_DEST_ID+L_FUNC_CODE)
#define	L_FRAME_LEN(DATA)					(uinteger)(L_STX+L_FR_LEN+L_SRC_ID+L_DEST_ID+L_FUNC_CODE+DATA+L_CRC+L_ETX)
#define	L_DATA_LEN(FRAME)					(uinteger)(FRAME-L_STX-L_FR_LEN-L_SRC_ID-L_DEST_ID-L_FUNC_CODE-L_CRC-L_ETX)
#define   TOTAL_NO_OF_SECTION                 6
#define   TOTAL_NO_OF_PAGES                   10
#define	KNOTS_TO_KMS_FACTOR					(float)1.852

//#######################################################################################
//				 DATABASE RELATED STRUCTURES
//#######################################################################################
struct path_header_struct
{
    ubyte Route[DIG_MAX_ROUTE_NUM_LEN];
    ubyte Description[DIG_MAX_PATH_DESC_LEN];
    ubyte Code[DIG_MAX_PATH_CODE_LEN];
    ubyte Source_Stop[DIG_STN_CODE];
    ubyte Via_stop[DIG_STN_CODE];
    ubyte Destination_Stop[DIG_STN_CODE];
    ubyte no_of_stns;
    float distance;
};
union events_defined_union
{
    struct
    {
        uinteger route_selection:1;
        uinteger journey_start:1;
        uinteger door_open:1;
        uinteger door_close:1;
        uinteger emergency:1;
        uinteger engineboot:1;
        uinteger stoparrival:1;
        uinteger stopapproaching:1;
        uinteger stopdeparture:1;
        uinteger journeyend:1;
        uinteger extras:6;
    }bits;
    uinteger flags;
};
struct stop_info_struct
{
    ubyte Code[DIG_STN_CODE];
    ubyte station_name[DIG_STN_NAME];
    ubyte station_type[DIG_STN_TYPE];
    int reference;
    float latit;
    float longit;
    float heading_info;
    float heading_tolerance;
    float position_tolerance_lat;
    float position_tolerance_long;
    float distance_tolerance;
    float distance_frm_src;
    uinteger entry_peri;
    uinteger exit_peri;
    uinteger approaching_peri;
    float gps_distance_from_curr_loc;
    float gps_distance_from_prev_loc;
    float distance_from_curr_loc;
    float distance_from_prev_loc;
    union events_defined_union events;
};
#define	STOP_INFO_STRUCT						sizeof(struct stop_info_struct)

union stop_info_union
{
    struct stop_info_struct info;
    ubyte bytes[STOP_INFO_STRUCT];
};
#define	STOP_INFO_UNION							sizeof(union stop_info_union)
//#######################################################################################
//				ROUTE RELATED STRUCTURES
//#######################################################################################
union route_status_union
{
    struct
    {
        unsigned inside_peri:1;
        unsigned outside_peri:1;
        unsigned approaching_peri:1;
        unsigned station_arrival:1;
        unsigned station_departure:1;
        unsigned station_approaching:1;
        unsigned new_gps_data:1;
        unsigned route_info_avail:1;
        unsigned bus_tracked:1;
        unsigned dist_processed:1;
        unsigned outage_rec:1;
        unsigned right_angle:1;
    }bits;
    uword word;
};

struct path_struct
{
    sinteger Curr_stop;
    sinteger Next_stop;
    sinteger Prev_stop;
    struct path_header_struct Header;
    union stop_info_union Stops[MAX_STNS_PER_BUS];
    union route_status_union status;
};
extern struct path_struct route_path;

//#######################################################################################
//				GPS RELATED STRUCTURES
//#######################################################################################
struct time_struct
{
    ubyte hrs;
    ubyte min;
    ubyte sec;
};
#define	TIME_STRUCT								sizeof(struct time_struct)
struct date_struct
{
    ubyte day ;
    ubyte month;
    ubyte yrs ;
};
#define	DATE_STRUCT								sizeof(struct date_struct)
struct gps_param_struct
{
    float latit;
    float longit;
    float speed;
    float heading;
    struct time_struct time;
    struct date_struct date;
    uinteger junk_for_align;
};
#define	GPS_PARAM_STRUCT						sizeof(struct gps_param_struct)
union gps_status_union
{
    struct
    {
        unsigned rtc_time_avail:1;
        unsigned rtc_updated:1;
        unsigned rtc_timer:1;
        unsigned initialised:1;
        unsigned rx_byte:1;
        unsigned gprmc:1;
        unsigned comp:1;
        unsigned time_out:1;
        unsigned cs_not_ok:1;
        unsigned invalid:1;
        unsigned date_time:1;
        unsigned lat_long:1;
        unsigned to_be_processed:1;
        unsigned date_time_processed:1;
        unsigned lat_long_processed:1;
        unsigned isr_to_cpu:1;
        unsigned data_time_out:1;
        unsigned test_ant:1;
        unsigned onsimulation:1;
    }bits;
    uword word;
};
struct gps_struct
{
    union gps_status_union status;
    struct gps_param_struct cpu;
    struct gps_param_struct isr;
    ubyte rx[SIZE_GPS_RMC_MSG];
    uinteger rtc_timer_count;
    uinteger rtc_data_timer_count;
    uinteger pkt_timer_count;
    uinteger data_timer_count;
    uinteger led_timer_count;
    uinteger rx_ptr;
    ubyte prev_byte;
    ubyte curr_byte;
    ubyte time[8];
    ubyte date[10];
    ubyte speed[5];
};
#define	GPS_STRUCT								sizeof(struct gps_struct)
union gps_union
{
    struct gps_struct data;
    uword word[GPS_STRUCT/4];
};//#######################################################################################
//				STRUCTURES FOR COMMUNICATION
//#######################################################################################
extern union gps_union gps;

extern uinteger act_stn_dist[MAX_STNS_PER_BUS];
extern sinteger mul_factor[MAX_STNS_PER_BUS];

#define	_GET_DISTANCE_BN_STN(CURR_STN_NUM)	get_distance(route_path.Stops[CURR_STN_NUM].info.latit,route_path.Stops[CURR_STN_NUM].info.longit,route_path.Stops[CURR_STN_NUM-1].info.latit,route_path.Stops[CURR_STN_NUM-1].info.longit);
#define	_GET_DISTANCE(CURR_STN_NUM)			get_distance(gps.data.cpu.latit,gps.data.cpu.longit,route_path.Stops[CURR_STN_NUM].info.latit,route_path.Stops[CURR_STN_NUM].info.longit);
#define ACT_DIST

void calc_mul_factor(void);
float get_distance(float x1, float y1, float x2, float y2);

struct outage_dist_struct
{
    float a_b;
    float b_c;
    float x_a;
    float x_b;
    float x_c;
};
extern struct outage_dist_struct out_dist;

//#######################################################################################
//				SYSTEM STRUCTURES
//#######################################################################################
union sys_flags_union
{
    struct
    {
        unsigned route_entered:1;
        unsigned route_missing:1;

        unsigned route_info_enable:1;
        unsigned init_sys_done:1;
        unsigned first_read_done:1;
        unsigned db_available:1;

        unsigned ext_voice:1;
        unsigned disable_gps:1;
        unsigned mode_selected:1;
        unsigned cpu_data_timeout:1;
        unsigned disp_busy:1;
        unsigned master_mode:1;

        unsigned journ_started:1;
        unsigned test_mode:1;
        unsigned usb_gps_simulation:1;
    }bits;
    uword word;
};

struct device_struct
{
    ubyte code[MAX_DEV_CODE_LEN];
    ubyte description[MAX_DEV_DESC_LEN];	//optional
    ubyte port;	//optional
    uinteger baudrate;
    ubyte device_type;
};
struct sys_param_struct
{
    struct device_struct devices[MAX_DEVICES_IN_SYSTEM];
};

struct sys_struct
{
    union sys_flags_union flags;
    struct sys_param_struct param;
};
extern struct sys_struct sys;

//#######################################################################################
//				STRUCTURES FOR COMMUNICATION
//#######################################################################################
//COMMUNICATION BETWEEN CPU AND SLAVES
union comm_flags_union
{
    struct
    {
        unsigned frame_avail:1;
        unsigned timer:1;
        unsigned enable:1;
        unsigned rx_comp:1;
        unsigned rx_stx:1;
    }bits;
    uword word;
};
struct comm_struct
{
    union comm_flags_union flags;
    uinteger rx_cnt;
    uinteger rx_timer_cnt;
    uinteger stx_timer_cnt;
};
#define	COMM_STRUCT								sizeof(struct comm_struct)
extern struct comm_struct cpu_comm;

struct rxtx_frame_struct
{
    ubyte stx[L_STX];
    ubyte length[L_FR_LEN];
    ubyte func_code[L_FUNC_CODE];
    ubyte dev_id[L_DEV_ID];
    ubyte dev_port[L_DEV_PORT];
    ubyte data_crc_bytes[L_DATA];
};
#define	RXTX_FRAME_STRUCT						sizeof(struct rxtx_frame_struct)

union rxtx_frame_union
{
    struct rxtx_frame_struct data;
    uinteger integ[RXTX_FRAME_STRUCT / 2];
    ubyte bytes[RXTX_FRAME_STRUCT];
};
#define	RXTX_FRAME_UNION						sizeof(union rxtx_frame_union)
extern union rxtx_frame_union rx;
extern union rxtx_frame_union tx;

//#######################################################################################
//				STRUCTURES FOR BDU/SCU COMMUNICATION
//#######################################################################################


/*typedef struct page_prop
{

    SECTION cord_section;
    ubyte display_mode;
    ubyte scroll_rate;
    ubyte scroll_direction;
    ubyte flashing;
    uinteger flash_rate;
    ubyte font;
    uinteger bitmap_length;
    uinteger *bitmap_location_in_flash;

 }PAGE_PROP;

 #define SECT_PROP_STRUCT_SIZE  sizeof(PAGE_PROP)

 typedef struct page_struct
 {
   ubyte duration;
   PAGE_PROP section[TOTAL_NO_OF_SECTION];
 }PAGE_STRUCT;

 typedef struct message
 {
   ubyte total_pages;
   PAGE_STRUCT page[TOTAL_NO_OF_PAGES];
 }MESSAGE;

extern MESSAGE msg;*/

#define BUFF_SIZE 64

    typedef union
    {
        struct
        {
            unsigned display_one:1;
            unsigned display_two:1;
            unsigned display_three:1;
            unsigned display_four:1;
        }data;
        uword value;
    }DISPLAY_STATUS;

   typedef union
    {
        struct
        {
            ubyte hrs;
            ubyte min;
            ubyte sec;
        }data ;
        uword value;
    }TIME;

    typedef union
    {
        struct
        {
            ubyte day;
            ubyte month;
            ubyte yrs;
        }data ;
        uword value;
    }DATE;

   typedef  union
   {
        struct inputs
        {
            ubyte input_1;
            ubyte input_2;
            ubyte input_3;
            ubyte input_4;
        }data;
        ubyte bytes[4];
        uword value;
    }DEVICE_INPUTS;


typedef struct
{
    ubyte cmd[3];
    ubyte IR_key;
    ubyte keypad_key;
    float odometer;
    DEVICE_INPUTS device_input;
    DATE date;
    TIME time;
    //DISPLAY_STATUS display;
    float latitude;
    float longitude;
    ubyte heading[5];
}STRUCT_SYSTEM_PHERI_INFO;

#define STRUCT_SIZE_SYSTEM_INFO sizeof(STRUCT_SYSTEM_PHERI_INFO)

typedef union  system_pheri_info
{
    STRUCT_SYSTEM_PHERI_INFO data;
    ubyte bytes[BUFF_SIZE];
}UNION_SYSTEM_PHERI_INFO;

typedef struct
{
    ubyte output_1;
    ubyte output_2;
}DEVICE_OUTPUT ;

typedef  struct
{
    ubyte cmd[3];
    ubyte buz_state;
    sword buz_frequency;
    ubyte volume ;
    DEVICE_OUTPUT  device_output;
}STRUCT_SYSTEM_INFO;

#define STRUCT_SIZE_SYSTEM_INFO sizeof(STRUCT_SYSTEM_PHERI_INFO)

typedef union  system_info
{
    STRUCT_SYSTEM_INFO data;
    ubyte bytes[BUFF_SIZE];
}UNION_SYSTEM_INFO;


typedef union
{
    STRUCT_SYSTEM_INFO          set_info;
    STRUCT_SYSTEM_PHERI_INFO    get_info;
    ubyte bytes[128];
}HID_BUFF;

typedef struct
{
    UNION_SYSTEM_PHERI_INFO pheri_info;
    UNION_SYSTEM_INFO setting;
}STRUCT_BUFF_SYSTEM_INFO;

typedef union
{
    STRUCT_BUFF_SYSTEM_INFO data;
    ubyte bytes[128];
}UNION_BUFF_SYSTEM_INFO;

extern UNION_BUFF_SYSTEM_INFO sys_info;

void send_display_response_to_mcu(void);
void send_mcu_pkt_to_display(void);
void display_Port_byte_Processing(ubyte recieved_byte);
void Serial_Port_byte_Processing(ubyte recieved_byte);

//#######################################################################################
//				STRUCTURES FOR DISPLAY COMMUNICATION
//#######################################################################################

typedef struct section
{
    ubyte x1;
    ubyte y1;
    ubyte x2;
    ubyte y2;
}SECTION;

typedef struct page_prop
{
    SECTION cord_section;
    ubyte display_mode;
    ubyte scroll_rate;
    ubyte scroll_direction;
    ubyte flashing;
    uinteger flash_rate;
    ubyte font;
    uinteger bitmap_length;
    uinteger *bitmap_location_in_flash;
 }PAGE_PROP;

 #define SECT_PROP_STRUCT_SIZE  sizeof(PAGE_PROP)

 typedef struct page_struct
 {
   ubyte duration;
   PAGE_PROP section[TOTAL_NO_OF_SECTION];
 }PAGE_STRUCT;

 typedef struct message
 {
   ubyte total_pages;
   PAGE_STRUCT page[TOTAL_NO_OF_PAGES];
 }MESSAGE;

extern MESSAGE msg;
