#include <Arduino.h>

#define LED_GPIO_PIN  GPIO_NUM_2

#define Timer_1    0
#define Timer_2    1
#define Timer_3    0



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

void goio_ctrl()
{
    static int level = 0;
    level = !level;
    gpio_set_level(LED_GPIO_PIN, level);
}



/***************************************************************************************************/
#if Timer_1

// 定时器回调
void  timer_callback(void* arg) {
    goio_ctrl();
}

esp_timer_handle_t timer_handle = NULL;
void time_init_1()
{
    esp_timer_create_args_t timer_args = {
        .callback = &timer_callback,   // 注册回调
        .name = "my_timer",            
    };
    esp_timer_create(&timer_args, &timer_handle); // 创建esp_timer实例
    esp_timer_start_periodic(timer_handle, 1000 * 1000);  // 每秒触发一次中断
}

void timer_stop(){
    esp_timer_stop(timer_handle);
}

void setup() {
    gpio_init(LED_GPIO_PIN);
    time_init_1();
}
#endif

/***************************************************************************************************/

#if Timer_2
// #include <esp32-hal-timer.h>

void IRAM_ATTR onTimer() {
    // 硬件定时器中断处理函数
    goio_ctrl();
}

void time_init_2()
{
    hw_timer_t *timer = NULL;
    /* 
       其中，第一个参数表示要使用的硬件定时器编号（ESP32 支持多个硬件定时器，编号从 0 开始），
       第二个参数表示定时器预分频器（可选值为 1、2、4、8、16、32、64 或 80），
       第三个参数表示定时器是否自动重载。
       timerBegin() 函数会返回一个指向 hw_timer_t 结构体的指针，表示创建的硬件定时器句柄。
     */
    timer = timerBegin(0, 80, true);  // 创建一个预分频为 80 的硬件定时器


    /* 
      第一个参数是硬件定时器句柄，
      第二个参数是中断回调函数的指针，
      第三个参数表示中断触发模式（true 表示边沿触发，false 表示电平触发）。
     */
    timerAttachInterrupt(timer, &onTimer, true); 

    // 设置硬件定时器的定时周期和重载值
    timerAlarmWrite(timer, 2000000, true); // 设置定时器周期为 1 秒，启用自动重载

    // 启动硬件定时器
    timerAlarmEnable(timer);
}

void setup() {
    gpio_init(LED_GPIO_PIN);
    time_init_2();
}
#endif 


#if Timer_3


// void onTimer(void *arg) {
//     // 定时器中断处理函数
// }


void time_init_3(){

    // timer_config_t config = {
    //     .divider = 80,           // 定时器分频器，80MHz/80=1MHz
    //     .counter_dir = TIMER_COUNT_UP,  // 定时器计数器方向，向上计数
    //     .counter_en = TIMER_PAUSE,      // 定时器计数器初始状态，暂停
    //     .alarm_en = TIMER_ALARM_EN,     // 定时器中断初始状态，禁止
    //     .auto_reload = true,            // 定时器自动重载，即循环计数
    //     .intr_type = TIMER_INTR_LEVEL,  // 定时器中断触发模式，电平触发
    //     .counter_width = TIMER_WIDTH_16_BIT,  // 定时器计数器位宽，16位
    //     .clk_cfg = TIMER_SRC_CLK_APB,   // 定时器时钟源，APB 时钟
    // };


    // timer_isr_register(timer_handle, onTimer, NULL, 0, NULL);


}

void setup() {
    gpio_init(LED_GPIO_PIN);
    // time_init_3();
}
#endif


void loop() {
  // put your main code here, to run repeatedly:
}