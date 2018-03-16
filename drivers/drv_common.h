#ifndef NDR_PDRV_COMMON_H
#define NDR_PDRV_COMMON_H

#define PREFIX_PDRV_EXCEPT "ndr-drv: Exception raised at %s.%u (%s) = "
#define SUFFIX_PDRV_EXCEPT __FILE__, __LINE__, __func__
#define PREFIX_PDRV_LOG "ndr-drv: "

#define PDRV_ERR( fmt, ... ) \
    printk( PREFIX_PDRV_EXCEPT fmt , SUFFIX_PDRV_EXCEPT, ##__VA_ARGS__ )
#define PDRV_WARN( fmt, ... ) \
    printk( PREFIX_PDRV_EXCEPT fmt , SUFFIX_PDRV_EXCEPT, ##__VA_ARGS__ )
#define PDRV_LOG( fmt, ... ) \
    printk( KERN_INFO PREFIX_PDRV_LOG fmt , ##__VA_ARGS__ )

#endif
