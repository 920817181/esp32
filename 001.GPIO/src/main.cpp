#include <Arduino.h>

#define LED  GPIO_NUM_2

// 配置为普通GPIO
void gpio_init(gpio_num_t GPIOx) {
    gpio_config_t gpio_cfg;
    gpio_cfg.pin_bit_mask = 1ULL<<GPIOx;                // 选择要配置的GPIO引脚，此处选择GPIO2
    gpio_cfg.mode = GPIO_MODE_OUTPUT;                   // 配置为输出模式
    gpio_cfg.pull_up_en = GPIO_PULLUP_DISABLE;          // 禁用上拉电阻
    gpio_cfg.pull_down_en = GPIO_PULLDOWN_DISABLE;      // 禁用下拉电阻
    gpio_cfg.intr_type = GPIO_INTR_DISABLE;             // 禁用中断
    gpio_config(&gpio_cfg);                             // 应用配置

    gpio_set_level(GPIOx, 1);                           // 设置GPIO2输出高电平
}

// 配置GPIO 为输入输出
void gpio_init_in_out() {
    gpio_config_t gpio_cfg;
    gpio_cfg.pin_bit_mask = (1ULL<<4) | (1ULL<<5);      // 选择要配置的GPIO引脚，此处选择GPIO4和GPIO5
    gpio_cfg.mode = GPIO_MODE_INPUT_OUTPUT;             // 配置为输入输出模式
    gpio_cfg.pull_up_en = GPIO_PULLUP_DISABLE;          // 禁用上拉电阻
    gpio_cfg.pull_down_en = GPIO_PULLDOWN_DISABLE;      // 禁用下拉电阻
    gpio_cfg.intr_type = GPIO_INTR_DISABLE;             // 禁用中断

    gpio_config(&gpio_cfg);                             // 应用配置
}

// 中断处理程序
void IRAM_ATTR gpio_isr_handler(void* arg) {
    uint32_t gpio_num = (uint32_t) arg;
    int value = gpio_get_level((gpio_num_t)gpio_num);
    printf("GPIO %d Input value: %d\n", gpio_num, value);
}

// 配置GPIO
void gpio_isr_init() {
    gpio_config_t gpio_cfg;
    gpio_cfg.pin_bit_mask = 1ULL<<6;     // 选择要配置的GPIO引脚，此处选择GPIO6
    gpio_cfg.mode = GPIO_MODE_INPUT;    // 配置为输入模式
    gpio_cfg.pull_up_en = GPIO_PULLUP_DISABLE;   // 禁用上拉电阻
    gpio_cfg.pull_down_en = GPIO_PULLDOWN_DISABLE;   // 禁用下拉电阻
    gpio_cfg.intr_type = GPIO_INTR_ANYEDGE;     // 配置为任意边缘触发中断
    gpio_config(&gpio_cfg);     // 应用配置
    gpio_install_isr_service(0);    // 安装GPIO中断服务
    gpio_isr_handler_add(GPIO_NUM_6, gpio_isr_handler, (void*) GPIO_NUM_6);    // 设置GPIO6的中断处理程序
}

void setup() {
  // put your setup code here, to run once:
    gpio_init(LED);
    gpio_init_in_out();
}

void loop() {
  // put your main code here, to run repeatedly:
   int value = gpio_get_level(GPIO_NUM_4);
    gpio_set_level(GPIO_NUM_5, value);
}