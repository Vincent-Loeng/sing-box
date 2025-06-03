#include <sys/param.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
#include <sys/sysctl.h>
#include <netinet/in.h>
#include <netinet/in_pcb.h>
#include <netinet/tcp_var.h>
#include <net/if.h>
#include <netinet6/in6_var.h>
#include <sys/file.h>

#include <net/pfvar.h>
#include <net/pfil.h>
#include <net/if_pflog.h>

#include <stdio.h>

#define  offsetof(type, member)   ((long) &((type *)0)->member)

int main()
{
   struct xinpcb *xinpcb_test;
   printf("Hello, World! \n");
   printf("xinpgen/headerSize: %ld\n", sizeof(struct xinpgen));
   printf("xtcpcb/tcpItemSize: %ld\n", sizeof(struct xtcpcb));
   printf("xinpcb/udpItemSize: %ld\n", sizeof(struct xinpcb));
   //printf("xinpcb.inp_vflag: %ld\n", sizeof(xinpcb_test->inp_vflag));
   //printf("xinpcb.inp_vflag addr: %p\n", &xinpcb_test->inp_vflag);
   // 388/392
   printf("\nport\n");
   printf("xinpcb.inp_inc offset: %ld\n", offsetof(struct xinpcb, inp_inc));
   printf("in_conninfo.inc_ie offset: %ld\n", offsetof(struct in_conninfo, inc_ie));
   printf("in_endpoints.ie_lport offset: %ld\n", offsetof(struct in_endpoints, ie_lport));
   printf("in_endpoints.ie_laddr offset: %ld\n", offsetof(struct in_endpoints, ie_laddr));
   printf("in_endpoints.ie6_laddr offset: %ld\n", offsetof(struct in_endpoints, ie6_laddr));
   printf("\n");
   printf("xinpcb.inp_vflag offset: %ld\n", offsetof(struct xinpcb, inp_vflag));
   printf("\nsocket\n");
   printf("xinpcb.xi_socket offset: %ld\n", offsetof(struct xinpcb, xi_socket));
   printf("xsocket.xso_so offset: %ld\n", offsetof(struct xsocket, xso_so));
   printf("\n");
   printf("xfile: %ld\n", sizeof(struct xfile));
   printf("xfile.xf_data offset: %ld\n", offsetof(struct xfile, xf_data));
   printf("xfile.xf_pid offset: %ld\n", offsetof(struct xfile, xf_pid));
   printf("\n");
   printf("PF_IN: %ld\n", PF_IN);
   printf("PF_OUT: %ld\n", PF_OUT);
   printf("DIOCNATLOOK: %x\n", DIOCNATLOOK);
   printf("INADDR_LOOPBACK: %ld\n", INADDR_LOOPBACK);
   printf("sa_family_t: %ld\n", sizeof(sa_family_t));
   printf("pfioc_natlook.af offset: %ld\n", offsetof(struct pfioc_natlook, af));
   printf("pfsync_state_1301: %ld\n", sizeof(struct pfsync_state_1301));
   printf("pfioc_states: %ld\n", sizeof(struct pfioc_states));
   printf("pfioc_states.ps_buf offset: %ld\n", offsetof(struct pfioc_states, ps_buf));
   printf("pfioc_states.ps_states offset: %ld\n", offsetof(struct pfioc_states, ps_states));

   struct in6_aliasreq ifreq6;
   struct sockaddr_in6 ifra_addr;
   printf("in6_aliasreq: %ld\n", sizeof(ifreq6));
   printf("sockaddr_in6: %ld\n", sizeof(ifra_addr));

   return 0;
}

