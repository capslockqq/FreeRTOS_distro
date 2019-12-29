#pragma once
#include "../application_code/components/Component.hpp"
#include "../application_code/communication/transport_layer/I_Serial_Communication.hpp"

#ifdef PC
#include "../application_code/communication/transport_layer/UART_fake.hpp"
#include "../application_code/communication/transport_layer/I2C_fake.hpp"

#elif TARGET
#include "../avr_code/communication/transport_layer/UART.hpp"

#endif
template <class Data_Com_data_type, class IMU_Com_data_type, class Data_Com_impl, class IMU_Com_impl>

class Factory : public Component {
public:
    Factory(const char*, const char*);
    I_Serial_Communication<Data_Com_data_type, Data_Com_impl> get_data_com_to_computer();
    I_Serial_Communication<IMU_Com_data_type, IMU_Com_impl>   get_data_com_to_IMU();

private:
    I_Serial_Communication<Data_Com_data_type, Data_Com_impl> data_com_to_computer;
    I_Serial_Communication<IMU_Com_data_type, IMU_Com_impl>  data_com_to_IMU;

};
template <class Data_Com_data_type, class IMU_Com_data_type, class Data_Com_impl, class IMU_Com_impl>
Factory<Data_Com_data_type, IMU_Com_data_type, Data_Com_impl, IMU_Com_impl>::Factory(const char* name, const char* id) :
Component(static_cast<Component*>(this), name, id)

{
#ifdef PC
data_com_to_computer = UART_fake(this, "Fake UART", "01");
data_com_to_IMU = I2C_fake(this, "Fake I2C", "01");
#elif TARGET
data_com_to_computer = UART(this, "UART", "01");
#endif
}

template <class Data_Com_data_type, class IMU_Com_data_type, class Data_Com_impl, class IMU_Com_impl>
I_Serial_Communication<Data_Com_data_type, Data_Com_impl> Factory<Data_Com_data_type, IMU_Com_data_type, Data_Com_impl, IMU_Com_impl>::get_data_com_to_computer() {
    return data_com_to_computer;
}

template <class Data_Com_data_type, class IMU_Com_data_type, class Data_Com_impl, class IMU_Com_impl>
I_Serial_Communication<IMU_Com_data_type, IMU_Com_impl> Factory<Data_Com_data_type, IMU_Com_data_type, Data_Com_impl, IMU_Com_impl>::get_data_com_to_IMU() {
    return data_com_to_IMU;
}