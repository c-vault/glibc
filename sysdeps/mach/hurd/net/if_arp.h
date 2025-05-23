/* Definitions for Address Resolution Protocol.
   Copyright (C) 1997-2025 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <https://www.gnu.org/licenses/>.  */

/* Based on the 4.4BSD and Linux version of this file.  */

#ifndef _NET_IF_ARP_H

#define _NET_IF_ARP_H 1
#include <sys/cdefs.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <stdint.h>

__BEGIN_DECLS

/* Some internals from deep down in the kernel.  */
#define MAX_ADDR_LEN	7


/* This structure defines an ethernet arp header.  */

/* ARP protocol opcodes. */
#define	ARPOP_REQUEST	1		/* ARP request.  */
#define	ARPOP_REPLY	2		/* ARP reply.  */
#define	ARPOP_RREQUEST	3		/* RARP request.  */
#define	ARPOP_RREPLY	4		/* RARP reply.  */

/* See RFC 826 for protocol description.  ARP packets are variable
   in size; the arphdr structure defines the fixed-length portion.
   Protocol type values are the same as those for 10 Mb/s Ethernet.
   It is followed by the variable-sized fields ar_sha, arp_spa,
   arp_tha and arp_tpa in that order, according to the lengths
   specified.  Field names used correspond to RFC 826.  */

struct arphdr
  {
    unsigned short int ar_hrd;		/* Format of hardware address.  */
    unsigned short int ar_pro;		/* Format of protocol address.  */
    unsigned char ar_hln;		/* Length of hardware address.  */
    unsigned char ar_pln;		/* Length of protocol address.  */
    unsigned short int ar_op;		/* ARP opcode (command).  */
#if 0
    /* Ethernet looks like this : This bit is variable sized
       however...  */
    unsigned char __ar_sha[ETH_ALEN];	/* Sender hardware address.  */
    unsigned char __ar_sip[4];		/* Sender IP address.  */
    unsigned char __ar_tha[ETH_ALEN];	/* Target hardware address.  */
    unsigned char __ar_tip[4];		/* Target IP address.  */
#endif
  };


/* ARP protocol HARDWARE identifiers. */
#define ARPHRD_NETROM	0		/* From KA9Q: NET/ROM pseudo. */
#define ARPHRD_ETHER 	1		/* Ethernet 10Mbps.  */
#define	ARPHRD_EETHER	2		/* Experimental Ethernet.  */
#define	ARPHRD_AX25	3		/* AX.25 Level 2.  */
#define	ARPHRD_PRONET	4		/* PROnet token ring.  */
#define	ARPHRD_CHAOS	5		/* Chaosnet.  */
#define	ARPHRD_IEEE802	6		/* IEEE 802.2 Ethernet/TR/TB.  */
#define	ARPHRD_ARCNET	7		/* ARCnet.  */
#define	ARPHRD_APPLETLK	8		/* APPLEtalk.  */
#define ARPHRD_DLCI	15		/* Frame Relay DLCI.  */
#define ARPHRD_METRICOM	23		/* Metricom STRIP (new IANA id).  */

/* Dummy types for non ARP hardware */
#define ARPHRD_SLIP	256
#define ARPHRD_CSLIP	257
#define ARPHRD_SLIP6	258
#define ARPHRD_CSLIP6	259
#define ARPHRD_RSRVD	260		/* Notional KISS type.  */
#define ARPHRD_ADAPT	264
#define ARPHRD_ROSE	270
#define ARPHRD_X25	271		/* CCITT X.25.  */
#define ARPHRD_PPP	512
#define ARPHRD_HDLC	513		/* (Cisco) HDLC.  */
#define ARPHRD_LAPB	516		/* LAPB.  */

#define ARPHRD_TUNNEL	768		/* IPIP tunnel.  */
#define ARPHRD_TUNNEL6	769		/* IPIP6 tunnel.  */
#define ARPHRD_FRAD	770             /* Frame Relay Access Device.  */
#define ARPHRD_SKIP	771		/* SKIP vif.  */
#define ARPHRD_LOOPBACK	772		/* Loopback device.  */
#define ARPHRD_LOCALTLK 773		/* Localtalk device.  */
#define ARPHRD_FDDI	774		/* Fiber Distributed Data Interface. */
#define ARPHRD_BIF      775             /* AP1000 BIF.  */
#define ARPHRD_SIT	776		/* sit0 device - IPv6-in-IPv4.  */


/* ARP ioctl request.  */
struct arpreq
  {
    struct sockaddr arp_pa;		/* Protocol address.  */
    struct sockaddr arp_ha;		/* Hardware address.  */
    int arp_flags;			/* Flags.  */
    struct sockaddr arp_netmask;	/* Netmask (only for proxy arps).  */
    char arp_dev[16];
  };

/* ARP Flag values.  */
#define ATF_COM		0x02		/* Completed entry (ha valid).  */
#define	ATF_PERM	0x04		/* Permanent entry.  */
#define	ATF_PUBL	0x08		/* Publish entry.  */
#define	ATF_USETRAILERS	0x10		/* Has requested trailers.  */
#define ATF_NETMASK     0x20            /* Want to use a netmask (only
					   for proxy entries).  */
#define ATF_DONTPUB	0x40		/* Don't answer this addresses.  */
#define ATF_MAGIC	0x80		/* Automatically added entry.  */


/* Support for the user space arp daemon, arpd.  */
#define ARPD_UPDATE	0x01
#define ARPD_LOOKUP	0x02
#define ARPD_FLUSH	0x03

struct arpd_request
  {
    unsigned short int req;		/* Request type.  */
    uint32_t ip;			/* IP address of entry.  */
    unsigned long int dev;		/* Device entry is tied to.  */
    unsigned long int stamp;
    unsigned long int updated;
    unsigned char ha[MAX_ADDR_LEN];	/* Hardware address.  */
  };

__END_DECLS

#endif	/* net/if_arp.h */
