#include "tasks.hpp"

#ifdef PC
Tasks::Tasks(I_application_code *app, I_application_simulation *sim) :
Component(this, "Tasks", "Tsk")
// ,com_to_computer(this, "Com to PC", "ComPC")
// ,com_to_imu(this, "Com to IMU", "02")
// ,drone_controller("Drone controller", "DRONE")
,application(app)
,simulation_model(sim)
{
} 
#endif
#ifdef TARGET
Tasks::Tasks(I_application_code *app) :
Component(this, "Tasks", "Tsk")
// ,com_to_computer(this, "Com to PC", "ComPC")
// ,com_to_imu(this, "Com to IMU", "02")
// ,drone_controller("Drone controller", "DRONE")
,application(app)
{
} 
#endif
Tasks::~Tasks() {
    
}

void Tasks::ControlSenderTask(void *param) {
    
}

#ifdef PC
float Tasks::m_simulation_time_seconds;
int Tasks::ticks = 0;

#endif
void Tasks::ControlTask(void *param) {

  Tasks* task = (Tasks*)param;
  
  double i = 1;
  double result = 0;
  while (1)
  { 
    vTaskDelay(SLEEP_TIME_MS);
    #ifdef PC
    task->simulation_model->Update();
    #endif
    ParameterWrite *paramwrite = ParameterWrite::GetInstance();
    for (int i = 0; i < paramwrite->bool_index; i++) {
         Parameter<bool>*tmp = (Parameter<bool>*)paramwrite->bool_params[i]; 
         tmp->SetValue(false);
    }
    task->UpdateOutputs();
    #ifdef PC
    task->UpdateParameters();
    task->UpdateOutputLog();
    #endif
    #ifdef PC 
    
    ticks++;
     if (ticks >= SAMPLE_FREQUENCY*m_simulation_time_seconds) {
       std::cout << "-----------------------Ending simulation-----------------------" << std::endl;
       std::cout << "Ticks: " << ticks << std::endl;
       std::cout << "Simulation time: " << ticks/SAMPLE_FREQUENCY << std::endl;
       std::cout << "---------------------------------------------------------------" << std::endl;
       std::cout << "Number of parameters: " << paramwrite->get_number_of_param()<< std::endl;
       vTaskEndScheduler();
       return;
     }
    #endif

  }
}

void Tasks::IMUReceiverTask(void *param) {
    
}

void Tasks::UpdateOutputs() {

}
#ifdef PC
void Tasks::UpdateParameters() {
  ParameterWrite *paramwrite = ParameterWrite::GetInstance();
  auto all_ids = Component::get_all_unique_ids_as_map();
  for (auto param : paramwrite->simlation_param_write) {
    if (std::get<0>(param.second)*SAMPLE_FREQUENCY == ticks) {
      if (paramwrite->simulation_bool_params.count(param.first)) {
        tuple sim_param_tuple = paramwrite->simulation_bool_params[param.first];
        std::cout << "Changing bool value from: "  << std::get<0>(sim_param_tuple)->GetValue() << " to: " << std::get<2>(sim_param_tuple) << std::endl;
        std::get<0>(sim_param_tuple)->SetValue(std::get<2>(sim_param_tuple));
      }
      else if(paramwrite->simulation_float_params.count(param.first)) {
        tuple sim_param_tuple = paramwrite->simulation_float_params[param.first];
        std::cout << "Changing float value from: "  << std::get<0>(sim_param_tuple)->GetValue() << " to: " << std::get<2>(sim_param_tuple) << std::endl;
        std::get<0>(sim_param_tuple)->SetValue(std::get<2>(sim_param_tuple));
      }

      else if(paramwrite->simulation_double_params.count(param.first)) {
        tuple sim_param_tuple = paramwrite->simulation_double_params[param.first];
        std::cout << "Changing double value from: "  << std::get<0>(sim_param_tuple)->GetValue() << " to: " << std::get<2>(sim_param_tuple) << std::endl;
        std::get<0>(sim_param_tuple)->SetValue(std::get<2>(sim_param_tuple));
      }
      else if(paramwrite->simulation_int_params.count(param.first)) {
        tuple sim_param_tuple = paramwrite->simulation_int_params[param.first];
        std::cout << "Changing int value from: "  << std::get<0>(sim_param_tuple)->GetValue() << " to: " << std::get<2>(sim_param_tuple) << std::endl;
        std::get<0>(sim_param_tuple)->SetValue(std::get<2>(sim_param_tuple));
      }
      
    }
  }
}


void Tasks::UpdateOutputLog() {
  OutputObserver *L = OutputObserver::GetInstance();
  auto list = L->GetUpdate();
  for (auto i : list) {
    if (std::get<1>(i) == "bool") {
      Output<bool>*tmp = (Output<bool>*)std::get<0>(i); 
      tmp->Update_Log();
    }
      
    else if (std::get<1>(i) == "float") {
      Output<float>*tmp = (Output<float>*)std::get<0>(i); 
      tmp->Update_Log();
    }
    else if (std::get<1>(i) == "double") {
      Output<double>*tmp = (Output<double>*)std::get<0>(i); 
      tmp->Update_Log();
    }
    else if (std::get<1>(i) == "int") {
      Output<int>*tmp = (Output<int>*)std::get<0>(i); 
      tmp->Update_Log();
    }
    else if (std::get<1>(i) == "char const*") {
      Output<int>*tmp = (Output<int>*)std::get<0>(i); 
      tmp->Update_Log();
    }
    else std:cout << std::get<1>(i) << std::endl;
    
  }
}

void Tasks::BindSystem(Tasks &task) {
}
#endif

void Tasks::SetUp_Tasks(Tasks &task) {
  #ifdef PC
  BindSystem(task);
  #endif
  xTaskCreate(this->ControlTask, "Controller",    configMINIMAL_STACK_SIZE, this, 7, NULL);
  // START SCHELUDER
  vTaskStartScheduler();
  vTaskEndScheduler();  
}



