
#include "FreeRTOS.h"
#include "list.h"
#include "task.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cpu_utilization_task.h"
#include <queue.h>
#define MONITOR_PRIORITY 3

int delay_period = 5000;
#define MAX_LINE_LENGTH 1024
// Define task stack sizes

#define TASK_STACK_SIZE 5000
// Define file paths for sensor data
#define PATIENT_1_HEARTRATE "/home/anisha/sjtwo-c/projects/x86_freertos/patient1_hr.txt"
#define PATIENT_1_BLOOD_PRESSURE "/home/anisha/sjtwo-c/projects/x86_freertos/patient1_bp.txt"
#define PATIENT_1_SPO2 "/home/anisha/sjtwo-c/projects/x86_freertos/patient1_spo2.txt"
#define PATIENT_2_HEARTRATE "/home/anisha/sjtwo-c/projects/x86_freertos/patient2_hr.txt"
#define PATIENT_2_BLOOD_PRESSURE "/home/anisha/sjtwo-c/projects/x86_freertos/patient2_bp.txt"
#define PATIENT_2_SPO2 "/home/anisha/sjtwo-c/projects/x86_freertos/patient2_spo2.txt"
#define PATIENT_3_HEARTRATE "/home/anisha/sjtwo-c/projects/x86_freertos/patient3_hr.txt"
#define PATIENT_3_BLOOD_PRESSURE "/home/anisha/sjtwo-c/projects/x86_freertos/patient3_bp.txt"
#define PATIENT_3_SPO2 "/home/anisha/sjtwo-c/projects/x86_freertos/patient3_spo2.txt"
#define PATIENT_4_HEARTRATE "/home/anisha/sjtwo-c/projects/x86_freertos/patient4_hr.txt"
#define PATIENT_4_BLOOD_PRESSURE "/home/anisha/sjtwo-c/projects/x86_freertos/patient4_bp.txt"
#define PATIENT_4_SPO2 "/home/anisha/sjtwo-c/projects/x86_freertos/patient4_spo2.txt"
#define PATIENT_5_HEARTRATE "/home/anisha/sjtwo-c/projects/x86_freertos/patient5_hr.txt"
#define PATIENT_5_BLOOD_PRESSURE "/home/anisha/sjtwo-c/projects/x86_freertos/patient5_bp.txt"
#define PATIENT_5_SPO2 "/home/anisha/sjtwo-c/projects/x86_freertos/patient5_spo2.txt"
#define QUEUE_LENGTH 100
#define ITEM_SIZE sizeof(int)
QueueHandle_t taskQueue;
QueueHandle_t nurseQueue;
QueueHandle_t nurseQueue1;
QueueHandle_t nurseQueue2;
QueueHandle_t nurseQueue3;
QueueHandle_t nurseQueue4;
QueueHandle_t doctorQueue;
QueueHandle_t onDemandDoc;
QueueHandle_t onCallDoctorQueue1;
QueueHandle_t onCallDoctorQueue2;

void distributeTasks(void *pvParameters) {

  BaseType_t queueNotEmpty;
  char *task = (char *)pvParameters;
  if (strcmp(task, "caretaker") == 0) {
    char taskParam[10];
    char taskParam2[10];
    // puts("in caretaker handler");
    while (1) {
      // puts("Queue contents:");
      // puts("in caretaker handler");
      // Loop through each item in the queue
      while (uxQueueMessagesWaiting(taskQueue) > 0) {
        // Receive the next item from the queue
        if (xQueueReceive(taskQueue, &taskParam, 50) == pdTRUE) {
          int caretakerDecision = rand() % 2;
          if (caretakerDecision == 1) {
            // Caretaker accepted the task
            printf("Caretaker unit accepted the task: %s\n", taskParam);
          } else {
            // Caretaker rejected the task, shift to the next level
            // printf("In else of %s\n", taskParam);
            xQueueSend(nurseQueue, taskParam, portMAX_DELAY);
          }
        }
      }

      if (uxQueueMessagesWaiting(taskQueue) == 0) {
        puts("The caretaker queue is empty");
      }
      vTaskDelay(pdMS_TO_TICKS(1000));
    }
  } else if (strcmp(task, "nurse") == 0) {
    char alert[10];
    char alert2[10];
    // puts("in nurse handler");
    while (1) {
      // puts("in nurse handler");
      while (uxQueueMessagesWaiting(nurseQueue) > 0) {
        if (xQueueReceive(nurseQueue, &alert, 100) == pdTRUE) {
          int nurseDecision1;
          int nurseDecision2;
          int nurseDecision3;
          int nurseDecision4;
          nurseDecision1 = rand() % 2; // Random decision, 1 for accept, 0 for reject
          nurseDecision2 = rand() % 2;
          nurseDecision3 = rand() % 2;
          nurseDecision4 = rand() % 2;
          if (nurseDecision1 == 1) {
            // Caretaker accepted the task
            printf("Nurse 1 accepted the task: %s\n", alert);
            xQueueSend(nurseQueue1, alert, 200);
          } else if (nurseDecision2 == 1) {
            printf("Nurse 2 accepted the task: %s\n", alert);
            xQueueSend(nurseQueue2, alert, 200);
          } else if (nurseDecision3 == 1) {
            printf("Nurse 3 accepted the task: %s\n", alert);
            xQueueSend(nurseQueue3, alert, 200);
          } else if (nurseDecision4 == 1) {
            printf("Nurse 4 accepted the task: %s\n", alert);
            xQueueSend(nurseQueue4, alert, 200);
          } else {
            // Caretaker rejected the task, shift to the next level
            xQueueSend(doctorQueue, alert, 200);
          }
        }
      }

      if (uxQueueMessagesWaiting(nurseQueue1) == 0) {
        puts("The nurse queue 1 is empty");
      }
      if (uxQueueMessagesWaiting(nurseQueue2) == 0) {
        puts("The nurse queue 2 is empty");
      }
      if (uxQueueMessagesWaiting(nurseQueue3) == 0) {
        puts("The nurse queue 3 is empty");
      }
      if (uxQueueMessagesWaiting(nurseQueue4) == 0) {
        puts("The nurse queue 4 is empty");
      }
      vTaskDelay(pdMS_TO_TICKS(2000));
    }

  } else if (strcmp(task, "oncalldoctor") == 0) {
    char alert3[10];
    char alert4[10];
    // puts("in doc handler");
    while (1) {
      // puts("in nurse handler");
      while (uxQueueMessagesWaiting(doctorQueue) > 0) {
        if (xQueueReceive(doctorQueue, &alert3, 200) == pdTRUE) {
          int oncalldoc1, oncalldoc2;
          oncalldoc1 = rand() % 2; // Random decision, 1 for accept, 0 for reject
          oncalldoc2 = rand() % 2;
          if (oncalldoc1 == 1) {
            // Caretaker accepted the task
            printf("On call Doctor 1 accepted the task: %s\n", alert3);
            xQueueSend(onCallDoctorQueue1, alert3, 200);
          } else if (oncalldoc2 == 1) {
            // Caretaker rejected the task, shift to the next level
            printf("On call Doctor 2 accepted the task: %s\n", alert3);
            xQueueSend(onCallDoctorQueue2, alert3, 200);
          } else {
            // printf("On call Doctor 2 accepted the task: %s\n", alert3);
            xQueueSend(onDemandDoc, alert3, 200);
          }
        }
      }
      if (uxQueueMessagesWaiting(doctorQueue) == 0) {
        puts("The doctor queue is empty");
      }
      vTaskDelay(pdMS_TO_TICKS(3000));
    }
  } else if (strcmp(task, "ondemanddoc") == 0) {
    char alert4[10];
    char alert2[10];
    // puts("in on call doc handler");
    while (1) {
      // puts("in nurse handler");
      while (uxQueueMessagesWaiting(onDemandDoc) > 0) {
        if (xQueueReceive(onDemandDoc, &alert4, 200) == pdTRUE) {
          printf("On demand doc accepted the task %s\n", alert4);
        }
      }

      if (uxQueueMessagesWaiting(onDemandDoc) == 0) {
        puts("The on demand doctor queue is empty");
      }

      vTaskDelay(pdMS_TO_TICKS(3000));
    }
  }
}

// Task to monitor heart rate
void monitorData(void *task_parameter) {
  float u_l, l_l;
  int *point;

  char *task = (char *)task_parameter;
  FILE *file;
  const char *file_path;
  if (strcmp(task, "Heart_P1") == 0) {
    file_path = PATIENT_1_HEARTRATE;
    printf("Patient 1 hr");
    l_l = 55;
    u_l = 85;
  } else if (strcmp(task, "Heart_P2") == 0) {
    file_path = PATIENT_2_HEARTRATE;
    printf("Patient 2 hr");
    l_l = 55;
    u_l = 85;

  } else if (strcmp(task, "Heart_P3") == 0) {
    file_path = PATIENT_3_HEARTRATE;
    printf("Patient 3 hr");
    l_l = 55;
    u_l = 85;
  } else if (strcmp(task, "Heart_P4") == 0) {
    file_path = PATIENT_4_HEARTRATE;
    printf("Patient 4 hr");
    l_l = 55;
    u_l = 85;

  } else if (strcmp(task, "Heart_P5") == 0) {
    file_path = PATIENT_5_HEARTRATE;
    printf("Patient 5 hr");
    l_l = 55;
    u_l = 85;
  }

  else if (strcmp(task, "SP_P1") == 0) {
    file_path = PATIENT_1_SPO2;
    l_l = 92;

  } else if (strcmp(task, "SP_P2") == 0) {
    file_path = PATIENT_2_SPO2;
    l_l = 92;

  } else if (strcmp(task, "SP_P3") == 0) {
    file_path = PATIENT_3_SPO2;
    l_l = 92;

  } else if (strcmp(task, "SP_P4") == 0) {
    file_path = PATIENT_4_SPO2;
    l_l = 92;

  } else if (strcmp(task, "SP_P5") == 0) {
    file_path = PATIENT_5_SPO2;
    l_l = 92;
  }

  else if (strcmp(task, "BP_P1") == 0) {
    file_path = PATIENT_1_BLOOD_PRESSURE;
    l_l = 75;
    u_l = 120;
  }

  else if (strcmp(task, "BP_P2") == 0) {
    file_path = PATIENT_2_BLOOD_PRESSURE;
    l_l = 75;
    u_l = 120;
  } else if (strcmp(task, "BP_P3") == 0) {
    file_path = PATIENT_3_BLOOD_PRESSURE;
    l_l = 75;
    u_l = 120;
  } else if (strcmp(task, "BP_P4") == 0) {
    file_path = PATIENT_4_BLOOD_PRESSURE;
    l_l = 75;
    u_l = 120;
  } else if (strcmp(task, "BP_P5") == 0) {
    file_path = PATIENT_5_BLOOD_PRESSURE;
    l_l = 75;
    u_l = 120;
  }

  else {
    printf("Invalid task parameter: %s\n", task);
    vTaskDelete(NULL); // Terminate the task if invalid task parameter
    return;
  }

  file = fopen(file_path, "r");
  if (file == NULL) {
    printf("Error opening file: %s\n", file_path);
    vTaskDelete(NULL); // Terminate the task if unable to open the file
    return;
  }

  char line[MAX_LINE_LENGTH];
  int count = 0;

  // Read and print 5 entries at a time
  while (fgets(line, sizeof(line), file) != NULL) {
    int values[10];
    if ((strcmp(task, "SP_P1") == 0) || (strcmp(task, "SP_P2") == 0) || (strcmp(task, "SP_P3") == 0) ||
        (strcmp(task, "SP_P4") == 0) || (strcmp(task, "SP_P5") == 0) || (strcmp(task, "Heart_P1") == 0) ||
        (strcmp(task, "Heart_P2") == 0) || (strcmp(task, "Heart_P3") == 0) || (strcmp(task, "Heart_P4") == 0) ||
        (strcmp(task, "Heart_P5") == 0)) {

      sscanf(line, "%d", &values[0]);

    } else {
      sscanf(line, "%d %d", &values[0], &values[1]);
    }

    for (int i = 0; i < 2; i++) {
      if ((strcmp(task, "SP_P1") == 0) || (strcmp(task, "SP_P2") == 0) || (strcmp(task, "SP_P3") == 0) ||
          (strcmp(task, "SP_P4") == 0) || (strcmp(task, "SP_P5") == 0) && ((values[0] < l_l))) {
        char task_param[13];
        char tp[13];
        delay_period = 15000;
        sprintf(task_param, "s%c(%d)", task[4], values[0]);
        xQueueSend(taskQueue, task_param, 1);
      }

      if (((strcmp(task, "Heart_P1") == 0) || (strcmp(task, "Heart_P2") == 0) || (strcmp(task, "Heart_P3") == 0) ||
           (strcmp(task, "Heart_P4") == 0) || (strcmp(task, "Heart_P5") == 0)) &&
          ((values[0] > u_l) || (values[0] < l_l))) {
        char task_param2[13];
        delay_period = 5000;
        sprintf(task_param2, "h%c(%d)", task[7], values[0]);
        xQueueSend(taskQueue, task_param2, 2);
      }

      //-----------------------------------------------------------

      if ((strcmp(task, "BP_P1") == 0) || (strcmp(task, "BP_P2") == 0) || (strcmp(task, "BP_P3") == 0) ||
          (strcmp(task, "BP_P4") == 0) || (strcmp(task, "BP_P5") == 0) && ((values[i] > u_l) || (values[i] < l_l))) {
        char task_param3[13];
        delay_period = 10000;
        sprintf(task_param3, "b%c(%d)", task[4], values[i]);

        xQueueSend(taskQueue, task_param3, 3);
      }

      //_______________________________________________________________
    }

    count++;
    if (count >= 1) {
      vTaskDelay(pdMS_TO_TICKS(3000)); // Delay for 1 second after printing 5 entries
      count = 0;                       // Reset the count
    }
  }

  vTaskDelay(pdMS_TO_TICKS(delay_period));
  fclose(file);
  vTaskDelete(NULL); // Terminate the task after completiondisplayQueue
}

/**
 * This POSIX based FreeRTOS simulator is based on:
 * https://github.com/linvis/FreeRTOS-Sim(strcmp(task, "BP") == 0)
 *
 * Do not use for production!
 * There may be issues that need full validation of this project to make it production intent.
 * This is a great teaching tool though :)
 */

int main(void) {

  taskQueue = xQueueCreate(100, sizeof(TaskHandle_t)); 
  nurseQueue = xQueueCreate(100, sizeof(TaskHandle_t));
  nurseQueue1 = xQueueCreate(100, sizeof(TaskHandle_t));
  nurseQueue2 = xQueueCreate(100, sizeof(TaskHandle_t));
  nurseQueue3 = xQueueCreate(100, sizeof(TaskHandle_t));
  nurseQueue4 = xQueueCreate(100, sizeof(TaskHandle_t));

  doctorQueue = xQueueCreate(100, sizeof(TaskHandle_t));
  onCallDoctorQueue1 = xQueueCreate(100, sizeof(TaskHandle_t));
  onCallDoctorQueue2 = xQueueCreate(100, sizeof(TaskHandle_t));
  onDemandDoc = xQueueCreate(100, sizeof(TaskHandle_t));

  xTaskCreate(monitorData, "BPTask", TASK_STACK_SIZE, "BP_P1", 1, NULL);
  xTaskCreate(monitorData, "BPTask", TASK_STACK_SIZE, "BP_P2", 2, NULL);
  xTaskCreate(monitorData, "BPTask", TASK_STACK_SIZE, "BP_P3", 1, NULL);
  xTaskCreate(monitorData, "BPTask", TASK_STACK_SIZE, "BP_P4", 1, NULL);
  xTaskCreate(monitorData, "BPTask", TASK_STACK_SIZE, "BP_P5", 1, NULL);

  xTaskCreate(monitorData, "HeartRateTask", TASK_STACK_SIZE, "Heart_P1", 3, NULL);
  xTaskCreate(monitorData, "HeartRateTask", TASK_STACK_SIZE, "Heart_P2", 3, NULL);
  xTaskCreate(monitorData, "HeartRateTask", TASK_STACK_SIZE, "Heart_P3", 3, NULL);
  xTaskCreate(monitorData, "HeartRateTask", TASK_STACK_SIZE, "Heart_P4", 3, NULL);
  xTaskCreate(monitorData, "HeartRateTask", TASK_STACK_SIZE, "Heart_P5", 3, NULL);

  xTaskCreate(monitorData, "SPTask", TASK_STACK_SIZE, "SP_P1", 2, NULL);
  xTaskCreate(monitorData, "SPTask", TASK_STACK_SIZE, "SP_P2", 2, NULL);
  xTaskCreate(monitorData, "SPTask", TASK_STACK_SIZE, "SP_P3", 2, NULL);
  xTaskCreate(monitorData, "SPTask", TASK_STACK_SIZE, "SP_P4", 2, NULL);
  xTaskCreate(monitorData, "SPTask", TASK_STACK_SIZE, "SP_P5", 2, NULL);

  xTaskCreate(distributeTasks, "QueueDisplayTask", TASK_STACK_SIZE, "caretaker", 7, NULL);
  xTaskCreate(distributeTasks, "NurseQueueTask", TASK_STACK_SIZE, "nurse", 6, NULL);
  xTaskCreate(distributeTasks, "DoctorDisplayTask", TASK_STACK_SIZE, "oncalldoctor", 5, NULL);
  xTaskCreate(distributeTasks, "OnCallDocDisplayTask", TASK_STACK_SIZE, "ondemanddoc", 4, NULL);
  puts("Starting FreeRTOS Scheduler ..... \r\n");
  vTaskStartScheduler();

  return 0;
}
