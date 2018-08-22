/******************************************************************************
 Copyright (C) 2018 NDR Opensource Group

 Licensed under the several legal conditions.
 See 'License' in the project root for legal information.
******************************************************************************/

#ifndef NDR_GPM1_SKBHOOK_H
#define NDR_GPM1_SKBHOOK_H

#include <linux/types.h>
#include <linux/netdevice.h>

#define NGPM1_SKBHOOK_ARGS \
	struct sk_buff *skb, struct net_device *dev, struct packet_type *pt, struct net_device *orig_dev

#define NGPM1_SKBHOOK_ARGFILL \
	skb, dev, pt, orig_dev

int ngpm1_skbhook_attach(uint16_t type, int (*ptr_hook_func)(NGPM1_SKBHOOK_ARGS));
int ngpm1_skbhook_detach(uint16_t type);
int ngpm1_skbhook_pktpass(NGPM1_SKBHOOK_ARGS);

#endif