#include <Arduino.h>

//biblioteca do freertos
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

//mapeamento de pinos
#define LED 2
/**
 *  exemplo para criar task.
 *  esse exemplo exibe como criar tarefas no FreeRTOS
 *  Por: Fernando da Silva. 
*/

//var para armazenamentos do handle das tasks
TaskHandle_t task_1_handle = NULL;
TaskHandle_t task_2_handle = NULL;

//prototipos de tasks
void vTask1(void *pvParameters);
void vTask2(void *pvParameters);

void setup() {
  //init from proccess
Serial.begin(115200);


xTaskCreate(vTask1,"TASK1", configMINIMAL_STACK_SIZE, NULL,1, &task_1_handle);
xTaskCreate(vTask2,"TASK2", configMINIMAL_STACK_SIZE+1024,NULL,2, &task_2_handle);
}

void loop() {
vTaskDelay(3000);
}


void vTask1(void *pvParameters){
  pinMode(LED, OUTPUT);

  while (1)
  {
    /**
     *  digitalWrite(LED, !digitalRead(LED));
     *   digitalWrite == escreve 
     *   LED, var led 
     *   !digitalRead(LED));  leia e inverta a sua leitura passando a var !digitalRead(LED));
     * 
    */
   digitalWrite(LED, !digitalRead(LED));
   vTaskDelay(pdMS_TO_TICKS(200));
  }
  

}
void vTask2(void *pvParameters){
  pinMode(LED, OUTPUT);
  int cont = 0;
  while (1)
  {
       Serial.println("Task2: " + String(cont++));
       vTaskDelay(pdMS_TO_TICKS(1000));

//deletando uma task
       if(cont >= 10){
         Serial.println(" Deletando Task 1");
         vTaskDelete(task_1_handle);
         digitalWrite(LED, LOW);
         delay(2000);
       }
  }
  
}
