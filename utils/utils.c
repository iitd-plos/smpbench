#include "utils.h"
#include "config.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <assert.h>
#include <sys/time.h>
#include <sys/timeb.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <time.h>
#include <string.h>

//#include "mysyscalls.h"
//#define PROCESSOR_FREQ 2.27e+9

#define MAX_BMARK_LEN 256
#define ASSERT assert

typedef struct profile_struct {
  char bmark[MAX_BMARK_LEN];
  unsigned long long clock_monotonic_usecs, clock_monotonic_coarse_usecs, clock_monotonic_raw_usecs, ntptime_start_usecs, unixtime_start_usecs;
  char const *ntp_server;
} profile_struct;

static double freq = 0;

static long
unix_curtime_usecs(void)
{
  struct timeb tb;
  int rc;

  rc = ftime(&tb);
  ASSERT(rc == 0);

  return tb.time * 1e+6 + (long)tb.millitm * 1e+3;
}

static long
clock_monotonic_curtime_usecs(void)
{
  struct timespec tp;
  int rc;

  rc = clock_gettime(CLOCK_MONOTONIC, &tp);
  ASSERT(rc == 0);

  return tp.tv_sec * 1e+6 + tp.tv_nsec/1e+3;
}

static long
clock_monotonic_coarse_curtime_usecs(void)
{
  struct timespec tp;
  int rc;

  rc = clock_gettime(CLOCK_MONOTONIC_COARSE, &tp);
  ASSERT(rc == 0);

  return tp.tv_sec * 1e+6 + tp.tv_nsec/1e+3;
}

static long
clock_monotonic_raw_curtime_usecs(void)
{
  struct timespec tp;
  int rc;

  rc = clock_gettime(CLOCK_MONOTONIC_RAW, &tp);
  ASSERT(rc == 0);

  return tp.tv_sec * 1e+6 + tp.tv_nsec/1e+3;
}




static long
ntp_curtime_usecs(char const *ntp_server)
{
  int portno=123;     //NTP is port 123
  int maxlen=1024;        //check our buffers
  int i;          // misc var i
  unsigned char msg[48]={010,0,0,0,0,0,0,0,0};    // the packet we send
  unsigned long  buf[maxlen]; // the buffer we get back
  struct protoent *proto;     //
  struct sockaddr_in server_addr;
  int s;  // socket
  unsigned long long tmit;   // the time -- This is a time_t sort of
  
  //use Socket;
  //
  //#we use the system call to open a UDP socket
  //socket(SOCKET, PF_INET, SOCK_DGRAM, getprotobyname("udp")) or die "socket: $!";
  proto=getprotobyname("udp");
  s = socket(PF_INET, SOCK_DGRAM, proto->p_proto);
  perror("socket");
  //
  //#convert hostname to ipaddress if needed
  //$ipaddr   = inet_aton($HOSTNAME);
  memset( &server_addr, 0, sizeof( server_addr ));
  server_addr.sin_family=AF_INET;
  server_addr.sin_addr.s_addr = inet_addr(ntp_server);
  //argv[1] );
  //i   = inet_aton(hostname,&server_addr.sin_addr);
  server_addr.sin_port=htons(portno);
  //printf("ipaddr (in hex): %x\n",server_addr.sin_addr);
  
  /*
   * build a message.  Our message is all zeros except for a one in the
   * protocol version field
   * msg[] in binary is 00 001 000 00000000 
   * it should be a total of 48 bytes long
  */
  
  // send the data
  printf("sending data..\n");
  i=sendto(s,msg,sizeof(msg),0,(struct sockaddr *)&server_addr,sizeof(server_addr));
  perror("sendto");
  // get the data back
  struct sockaddr saddr;
  socklen_t saddr_l = sizeof (saddr);
  i=recvfrom(s,buf,48,0,&saddr,&saddr_l);
  perror("recvfr:");
  
  //We get 12 long words back in Network order
  /*
  for(i=0;i<12;i++) {
      //printf("%d\t%-8x\n",i,ntohl(buf[i]));
      long tmit2=ntohl((time_t)buf[i]);
      std::cout << "Round number " << i << " time is " << ctime(&tmit2)  << std::endl;
  }
  */
  /*
   * The high word of transmit time is the 10th word we get back
   * tmit is the time in seconds not accounting for network delays which
   * should be way less than a second if this is a local NTP server
   */
  
  //tmit=ntohl((time_t)buf[10]);    //# get transmit time
  tmit=ntohl((time_t)buf[4]);    //# get transmit time
  //printf("tmit=%d\n",tmit);
  
  /*
   * Convert time to unix standard time NTP is number of seconds since 0000
   * UT on 1 January 1900 unix time is seconds since 0000 UT on 1 January
   * 1970 There has been a trend to add a 2 leap seconds every 3 years.
   * Leap seconds are only an issue the last second of the month in June and
   * December if you don't try to set the clock then it can be ignored but
   * this is importaint to people who coordinate times with GPS clock sources.
   */
  
  tmit-= 2208988800U; 


  //printf("tmit=%d\n",tmit);
  /* use unix library function to show me the local time (it takes care
   * of timezone issues for both north and south of the equator and places
   * that do Summer time/ Daylight savings time.
   */
  //#compare to system time
  //printf("Time: %s",ctime(&tmit));
  
  //std::cout << "time is " << ctime(&tmit)  << std::endl;
  //i=time(0);
  //printf("%d-%d=%d\n",i,tmit,i-tmit);
  //printf("System time is %d seconds off\n",(i-tmit));
  //std::cout << "System time is " << (i-tmit) << " seconds off" << std::endl;

  return tmit;
}

static void
ntp_start(profile_struct *ps)
{
  ps->ntp_server = getenv("NTPSERVER");

  if (!ps->ntp_server) {
    printf("NTPSERVER not initialized.\n");
    return;
  }
  ps->ntptime_start_usecs = ntp_curtime_usecs(ps->ntp_server);
}

void
profile_init(void)
{
  static char buf[4096];
  char const *cpu_mhz;
  ssize_t num_read;
  int fd;
  fd = open("/proc/cpuinfo", O_RDONLY);
  ASSERT(fd >= 0);

  num_read = read(fd, buf, sizeof buf);
  close(fd);

  buf[sizeof(buf) - 1] = '\0';
  cpu_mhz = strstr(buf, "cpu MHz");
  ASSERT(cpu_mhz);
  freq = atoi(cpu_mhz + 10);
  ASSERT(freq);
  freq *= 1e+6;
  printf("CPU frequency = %f\n", freq);
}

struct profile_struct *
profile_start(char const *bmark)
{
  struct profile_struct *ret;
  char const *p;

  ret = (struct profile_struct *)malloc(sizeof(struct profile_struct));
  ASSERT(ret);
  strncpy(ret->bmark, bmark, MAX_BMARK_LEN);

  ntp_start(ret);
  ret->unixtime_start_usecs = unix_curtime_usecs();
  ret->clock_monotonic_usecs = clock_monotonic_curtime_usecs();
  ret->clock_monotonic_coarse_usecs = clock_monotonic_coarse_curtime_usecs();
  ret->clock_monotonic_raw_usecs = clock_monotonic_raw_curtime_usecs();
  return ret;
}

void
profile_stop(struct profile_struct *ps, int error)
{
  double clock_monotonic_time, clock_monotonic_coarse_time, clock_monotonic_raw_time, ntp_time, unix_time;

  clock_monotonic_time = (clock_monotonic_curtime_usecs() - ps->clock_monotonic_usecs)/1e+6;
  clock_monotonic_coarse_time = (clock_monotonic_coarse_curtime_usecs() - ps->clock_monotonic_coarse_usecs)/1e+6;
  clock_monotonic_raw_time = (clock_monotonic_raw_curtime_usecs() - ps->clock_monotonic_raw_usecs)/1e+6;
  if (ps->ntp_server) {
    ntp_time = (ntp_curtime_usecs(ps->ntp_server) - ps->ntptime_start_usecs)/1e+6;
  }
  unix_time = (unix_curtime_usecs() - ps->unixtime_start_usecs)/1e+6;

  printf("%s: %s:", __func__, ps->bmark);
  printf(" clock_monotonic_time %.4f secs,", clock_monotonic_time);
  printf(" clock_monotonic_coarse_time %.4f secs,", clock_monotonic_coarse_time);
  printf(" clock_monotonic_raw_time %.4f secs,", clock_monotonic_raw_time);
  printf(" unix_time %.4f secs", unix_time);
  if (ps->ntp_server) {
    printf(" ntp_time %.4f secs", ntp_time);
  }
  printf("\n");

  free(ps);
}

uint32_t
str2int(char const *str)
{
  int i;
  uint32_t ret_int;
  int end_reached = 0;
  char *ret = (char *)&ret_int;

  for (i = 0; i < 4; i++) {
    if (!end_reached) {
      ret[i] = str[i];
      if (str[i] == '\0') {
        end_reached = 1;
      }
    } else {
      ret[i] = 0;
    }
  }
  return ret_int;
}

static uint64_t loops_per_usecond = 0;
static void
do_loops(uint64_t loops)
{
  while (loops-- > 0) {
    barrier();
  }
}

pid_t
xfork(char const *path, char *const args[])
{
  pid_t pid;
  int fd;

  pid = fork();

  if (pid) {
    /* parent */
    return pid;
  }
  /* child */
  execv(path, args);
  printf("execv(%s, %s) failed: %s()\n", path, args[0], strerror(errno));
  exit(1);
}
