#include <arpa/inet.h>
#include <errno.h>
#include <netinet/if_ether.h>
#include <netinet/in.h>
#include <pcap.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/prctl.h>
#include <sys/socket.h>

#define PACKET_THRESHOLD 200
#define FILTER_RULES                                                           \
  "dst host www.crunchyroll.com or dst host www.netflix.com or dst host "      \
  "www.hulu.com"

void packetCallback(unsigned char *useless, const struct pcap_pkthdr *pkthdr,
                    const unsigned char *packet) {
  static int count = 1;
  fprintf(stdout, "%d, ", count);

  fprintf(stdout, "Got a package\n");

  if (count >= PACKET_THRESHOLD) {
    fprintf(stdout, "Threshold reached!\n");
    system("pkill chrome");
  }

  fflush(stdout);
  count++;
}

int main(int argc, char **argv) {
  char *dev;
  char errbuf[PCAP_ERRBUF_SIZE];
  pcap_t *descr;
  struct bpf_program filter;
  bpf_u_int32 maskp;
  bpf_u_int32 netp;

  dev = pcap_lookupdev(errbuf);
  if (dev == NULL) {
    printf("%s\n", errbuf);
    exit(1);
  }

  pcap_lookupnet(dev, &netp, &maskp, errbuf);

  descr = pcap_open_live(dev, BUFSIZ, 0, -1, errbuf);
  if (descr == NULL) {
    printf("pcap_open_live(): %s\n", errbuf);
    exit(1);
  }

  if (pcap_compile(descr, &filter, FILTER_RULES, 0, netp) == -1) {
    fprintf(stderr, "Error calling pcap_compile\n");
    exit(1);
  }

  if (pcap_setfilter(descr, &filter) == -1) {
    fprintf(stderr, "Error setting filter\n");
    exit(1);
  }

  pcap_loop(descr, -1, packetCallback, NULL);
  return 0;
}