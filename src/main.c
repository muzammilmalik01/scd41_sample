#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/device.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/sensor.h>

#include "sensor/scd4x/scd4x.h"


#if !DT_HAS_COMPAT_STATUS_OKAY(sensirion_scd41)
#error "No sensirion,scd4x compatible node found in the device tree"
#endif


const struct device *scd41 = DEVICE_DT_GET_ANY(sensirion_scd41);

int main (void){
       
        if (!device_is_ready(scd41)) {
                printk("SCD41 device is not ready\n");
                return 1;
        }
        struct sensor_value co2, temo, humi;
        while(true){

                sensor_sample_fetch(scd41);
                sensor_channel_get(scd41, SENSOR_CHAN_CO2, &co2);
                sensor_channel_get(scd41, SENSOR_CHAN_AMBIENT_TEMP, &temo);
                sensor_channel_get(scd41, SENSOR_CHAN_HUMIDITY, &humi);
                printk("CO2: %d.%06d ppm, Temperature: %d.%06d C, Humidity: %d.%06d %%\n",
                       co2.val1, co2.val2, temo.val1, temo.val2, humi.val1, humi.val2);
                k_sleep(K_SECONDS(10));
        }
        return 0;
}