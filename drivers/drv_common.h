/******************************************************************************
 Copyright (C) 2018 NDR Opensource Group

 Licensed under the several legal conditions.
 See 'License' in the project root for legal information.
******************************************************************************/

#ifndef NDR_DRV_COMMON_H
#define NDR_DRV_COMMON_H

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/pci.h>
#include <linux/device.h>

#ifndef KBUILD_MODNAME
#define KBUILD_MODNAME "ndr-drv"
#endif


#define NDR_MODULE_DATE "2018"
#define NDR_MODULE_AUTHOR "NDR Opensource Group"
#define NDR_MODULE_MAIL "<openndr@googlegroups.com>"
#define NDR_MODULE_LICENSE "GPL"
#define NDR_MODULE_COPYRIGHT( modname ) \
	MODULE_AUTHOR(NDR_MODULE_AUTHOR ", " NDR_MODULE_MAIL); \
	MODULE_LICENSE(NDR_MODULE_LICENSE);

#define PREFIX_DRV_LOG KBUILD_MODNAME ": "
#define PREFIX_DRV_EXCEPT PREFIX_DRV_LOG "Exception raised at %s.%u (%s) = "
#define SUFFIX_DRV_EXCEPT __FILE__, __LINE__, __func__

#define PDRV_LOG( lvl, pdev, fmt, ... ) \
	printk( "%s %s: " fmt, lvl, pci_name( pdev ), ##__VA_ARGS__ )

#define DRV_EMERG( fmt, ... ) \
    printk( KERN_EMERG PREFIX_DRV_EXCEPT fmt , SUFFIX_DRV_EXCEPT, ##__VA_ARGS__ )
#define DRV_ALERT( fmt, ... ) \
    printk( KERN_ALERT PREFIX_DRV_EXCEPT fmt , SUFFIX_DRV_EXCEPT, ##__VA_ARGS__ )
#define DRV_CRIT( fmt, ... ) \
    printk( KERN_CRIT PREFIX_DRV_EXCEPT fmt , SUFFIX_DRV_EXCEPT, ##__VA_ARGS__ )
#define DRV_ERR( fmt, ... ) \
    printk( KERN_ERR PREFIX_DRV_EXCEPT fmt , SUFFIX_DRV_EXCEPT, ##__VA_ARGS__ )
#define DRV_WARN( fmt, ... ) \
    printk( KERN_WARNING PREFIX_DRV_EXCEPT fmt , SUFFIX_DRV_EXCEPT, ##__VA_ARGS__ )
#define DRV_NOTICE( fmt, ... ) \
    printk( KERN_NOTICE PREFIX_DRV_LOG fmt , ##__VA_ARGS__ )
#define DRV_LOG( fmt, ... ) \
    printk( KERN_INFO PREFIX_DRV_LOG fmt , ##__VA_ARGS__ )
#define DRV_CONT( fmt, ... ) \
    printk( KERN_CONT PREFIX_DRV_LOG fmt , ##__VA_ARGS__ )

#ifdef pdev_printk
#undef pdev_printk
#define pdev_printk PDRV_LOG
#endif

#ifdef pr_emerg
#undef pr_emerg
#define pr_emerg DRV_EMERG
#endif

#ifdef pr_alert
#undef pr_alert
#define pr_alert DRV_ALERT
#endif

#ifdef pr_crit
#undef pr_crit
#define pr_crit DRV_CRIT
#endif

#ifdef pr_err
#undef pr_err
#define pr_err DRV_ERR
#endif

#ifdef pr_warn
#undef pr_warn
#define pr_warn DRV_WARN
#endif

#ifdef pr_notice
#undef pr_notice
#define pr_notice DRV_NOTICE
#endif

#ifdef pr_info
#undef pr_info
#define pr_info DRV_LOG
#endif

#ifdef pr_cont
#undef pr_cont
#define pr_cont DRV_CONT
#endif

#endif
