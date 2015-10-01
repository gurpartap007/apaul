	
#ifndef _HEADER_H
#define _HEADER_H
#define RS 25
#define EN 26
#define D0 27
#define D1 28
#define D2 29
#define D3 30
 
 struct gpio_descriptor_t {
    char *gpio_dev;
    int gpio_fd;
    int gpio_num;
    unsigned int gpio_flag;
    unsigned char buf[100];
};
struct ascii {
    char d0:1;
    char d1:1;
    char d2:1;
    char d3:1;
    char d4:1;
    char d5:1;
    char d6:1;
    char d7:1;
 
};
union ascii_num {
    struct ascii decimal_val;
    char command_copy;
};
int gpio_set_value(struct gpio_descriptor_t* gpio_desc, unsigned int val);

/* GPIO - SET VALUE */
int gpio_fd_open(struct gpio_descriptor_t *);
int gpio_fd_close(struct gpio_descriptor_t *);
void send_command(struct gpio_descriptor_t *,int);
void send_character(struct gpio_descriptor_t *,int);
 
#endif

