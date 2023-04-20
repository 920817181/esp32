#include <Arduino.h>


#define  PWM_1  0
#define  PWM_2  1


#define  LED_PIN    2
#define  freq       5000    // 频率, 单位Hz
#define  resolution 10      // 位宽,占空比的设置与这有直接关系
#define  channel    0       // 通道


//!  占空比 =  设定值duty/2^resolution

#if PWM_1 /***************************************************************************************************/
void PWM_init() {

    // 配置 LED 引脚为输出模式
    pinMode(LED_PIN, OUTPUT);

    // 配置PWM通道0，频率为5 kHz，分辨率为8位
    ledcSetup(channel, freq, resolution); // Configure PWM channel 0 with a frequency of 5 kHz and 8-bit resolution

    // 将PWM通道0连接到引脚2
    ledcAttachPin(LED_PIN, channel); // Attach PWM channel 0 to pin 2
}
void setup() {
    // put your setup code here, to run once:
    PWM_init();

    // 设置PWM通道0占空比为50%
    ledcWrite(channel, 512); // Set the duty cycle of PWM channel 0 to 50%
}

void loop() {
  // put your main code here, to run repeatedly:
    static uint16_t i = 0, j = 0;
    i++;
    if (i>=500) {
        i = 0;

        ledcWrite(channel, j); // Set the duty cycle of PWM channel 0 to 50%
        j+=50;
        if (j>=250)
            j = 0;
    }
}

#elif PWM_2 /***************************************************************************************************/




void PWM_init()
{
    // 配置 LED 引脚为输出模式
    pinMode(LED_PIN, OUTPUT);

    ledcSetup(channel, freq, resolution);

    ledcAttachPin(LED_PIN, channel);
    ledcWrite(channel, ((1<<resolution)/2));
}

// 停止 PWM 输出
void PWM_Stop()
{
    ledcDetachPin(LED_PIN);
}


void setup() {
    // put your setup code here, to run once:
    PWM_init();
}

void loop() {
    // put your main code here, to run repeatedly:
    
    // 呼吸灯效果
    for (int duty = 0; duty <= 1023; duty++) {
        ledcWrite(channel, duty);
        delay(2);
    }
    for (int duty = 1023; duty >= 0; duty--) {
        ledcWrite(channel, duty);
        delay(2);
    }
}


#elif PWM_3 /***************************************************************************************************/

void setup() {
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
}


#else

void setup() {
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
}

#endif/***************************************************************************************************/