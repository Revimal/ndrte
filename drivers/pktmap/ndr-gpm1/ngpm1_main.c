/******************************************************************************
 Copyright (C) 2018 NDR Opensource Group

 Licensed under the several legal conditions.
 See 'License' in the project root for legal information.
******************************************************************************/

#include <linux/if_ether.h>
#include <net/ip.h>

#include "drv_common.h"
#include "ngpm1_skbhook.h"

#define NGPM1_MODULE_NAME "ndr-gpm1"
#define NGPM1_MODULE_VERSION "1.0.0"
#define NGPM1_MODULE_DESC "NDR IP_PROTO pktmap driver for generic NICs"

NDR_MODULE_COPYRIGHT(NGPM1_MODULE_NAME)
MODULE_VERSION(NGPM1_MODULE_VERSION);
MODULE_DESCRIPTION(NGPM1_MODULE_DESC);

#define NIPQUAD(addr) \
	((unsigned char *)&addr)[0], \
	((unsigned char *)&addr)[1], \
	((unsigned char *)&addr)[2], \
	((unsigned char *)&addr)[3]
#define NIPQUAD_FMT "%u.%u.%u.%u"

static int ngpm1_iphook_callback(NGPM1_SKBHOOK_ARGS)
{
	struct iphdr *iph = NULL;

	if (!skb) {
		goto drop;
	}

	iph = ip_hdr(skb);
	if ( !iph ) {
		goto pktpass;
	}

	DRV_LOG("{"NIPQUAD_FMT"}=>{"NIPQUAD_FMT"} : %s\n",
				NIPQUAD( iph->saddr ),
				NIPQUAD( iph->daddr ),
				iph->protocol == IPPROTO_ICMP ? "ICMP" : "UNKNOWN"
	);

pktpass:
	return ngpm1_skbhook_pktpass(NGPM1_SKBHOOK_ARGFILL);

drop:
	return NET_RX_DROP;
}

static int __init ngpm1_load(void)
{
	int ret = 0;

	ngpm1_skbhook_attach(cpu_to_be16(ETH_P_IP), ngpm1_iphook_callback);

	return ret;
}

static void __exit ngpm1_unload(void)
{
	ngpm1_skbhook_detach(cpu_to_be16(ETH_P_IP));

	return;
}

module_init(ngpm1_load);
module_exit(ngpm1_unload);
