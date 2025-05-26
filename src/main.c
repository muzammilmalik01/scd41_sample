#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/drivers/i2c.h>

// #if !DT_HAS_COMPAT_STATUS_OKAY(sensirion_svm41)
// #error "No sensirion,svm41 compatible node found in the device tree"
// #endif

void check_i2c_scan(const struct device *i2c_dev)
{
    uint8_t addr;
    int ret;

    printk("Scanning I2C bus...\n");
    
    for (addr = 4; addr <= 0x77; addr++) {
        ret = i2c_write(i2c_dev, NULL, 0, addr);
        if (ret == 0) {
            printk("Device found at 0x%02X\n", addr);
        }
    }
}

int main (void){
        const struct device *scd41 = DEVICE_DT_GET(DT_NODELABEL(scd41));
        // const struct device *scd41 = DEVICE_DT_GET_ANY(sensirion_scd41);
        const struct device *i2c_dev = DEVICE_DT_GET(DT_NODELABEL(i2c0));
        if (!device_is_ready(i2c_dev)) {
                printk("I2C controller not ready\n");
            }
            
            check_i2c_scan(i2c_dev);  // Should show 0x62 for SCD4x
        if (!device_is_ready(scd41)) {
                printk("SCD41 device is not ready\n");
                return 1;
        }
        struct sensor_value co2, temo, humi;
        while(true){
        const struct device *scd41 = DEVICE_DT_GET_ANY(sensirion_scd41);
                sensor_channel_get(scd41, SENSOR_CHAN_CO2, &co2);
                sensor_channel_get(scd41, SENSOR_CHAN_AMBIENT_TEMP, &temo);
                sensor_channel_get(scd41, SENSOR_CHAN_HUMIDITY, &humi);
                printk("CO2: %d.%06d ppm, Temperature: %d.%06d C, Humidity: %d.%06d %%\n",
                       co2.val1, co2.val2, temo.val1, temo.val2, humi.val1, humi.val2);
                k_sleep(K_SECONDS(1000));
        }
        return 0;
}