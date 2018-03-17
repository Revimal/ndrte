#ifndef NDR_DRV_COMMON_H
#define NDR_DRV_COMMON_H

#define PREFIX_DRV_EXCEPT "ndr-drv: Exception raised at %s.%u (%s) = "
#define SUFFIX_DRV_EXCEPT __FILE__, __LINE__, __func__
#define PREFIX_DRV_LOG "ndr-drv: "

#define DRV_ERR( fmt, ... ) \
    printk( PREFIX_DRV_EXCEPT fmt , SUFFIX_DRV_EXCEPT, ##__VA_ARGS__ )
#define DRV_WARN( fmt, ... ) \
    printk( PREFIX_DRV_EXCEPT fmt , SUFFIX_DRV_EXCEPT, ##__VA_ARGS__ )
#define DRV_LOG( fmt, ... ) \
    printk( KERN_INFO PREFIX_DRV_LOG fmt , ##__VA_ARGS__ )

#endif
