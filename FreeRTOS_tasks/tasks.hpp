#pragma once
#include "../../component_framework/components/Component.hpp"
#include "../../component_framework/components/Binds.hpp"
#include "application_code.hpp"
#define SAMPLE_FREQUENCY 100 // Hz

#ifdef PC
#define SLEEP_TIME_MS 0.0001f
#include "../FreeRTOS_Linux/include/FreeRTOS.h"
#include "../FreeRTOS_Linux/include/task.h"
#include "../FreeRTOS_Linux/include/queue.h"
#include "../FreeRTOS_Linux/include/semphr.h"
#include "../../component_framework/components/Singleton.hpp"
#include "../../component_framework/components/OutputObserver.hpp"
#include "../../component_framework/components/type_name.hpp"
#include "../../component_framework/components/ParameterWrite.hpp"
#include "../../quadcopter/simulation/quadcopter_model/quadcopter_simulation.hpp"

#endif

#ifdef TARGET
#define SLEEP_TIME_MS (1000 / SAMPLE_FREQUENCY)
#include "../FreeRTOS_avr/include/FreeRTOS.h"
#include "../FreeRTOS_avr/include/task.h"

#endif

// Component *Application = new Component(0, "Application", "01");
class Tasks : public Component {
public:
Tasks();
    ~Tasks();
    void SetUp_Tasks(Tasks &task);
    Application_code application;

    #ifdef PC
    static float m_simulation_time_seconds;
    quadcopter_model quadcopter;
    #endif
private:
    void ControlSenderTask(void *param);
    static void ControlTask(void *param);
    static void IMUReceiverTask(void *param);
    static void UpdateOutputs();
    static void UpdateParameters();
    #ifdef PC
    static void BindSystem(Tasks &task);
    static void UpdateOutputLog();
    static int ticks;
    #endif
};

