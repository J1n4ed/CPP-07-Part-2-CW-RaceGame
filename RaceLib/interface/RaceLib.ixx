// RaceLib.ixx

module;

#include <iostream>
#include <string>

#define EXPORT_API __declspec(dllexport)

export module jinx_racegame;

import jinx_exceptions;

// export __declspec(dllexport) symbol

namespace jinx 
{

    class Vehicle
    {
    public:

        std::string get_vehicle_name()
        {
            return this->vehicleName;
        }

        std::string get_vehicle_pilot()
        {
            return this->vehiclePilot;
        }

        int get_vehicle_speed()
        {
            return this->speed;
        }        

        void set_vehicle_speed(int _speed)
        {
            this->speed = _speed;
        }

        // Constructors
        Vehicle() = delete;

        Vehicle(std::string _vehiclePilot)
        {
            this->vehiclePilot = _vehiclePilot;
        }

    protected:

        std::string vehicleName;        // vehicle name
        unsigned short vehicleClass;    // 0 - ground, 1 - air

    private:
        
        std::string vehiclePilot;       // pilot full name
        
        int speed;
       
    }; // END OF class Vehicle

    // ---------------------------

    class VehicleGround : Vehicle
    {
    public:

        // Constructor removal
        VehicleGround() = delete;

        VehicleGround(std::string _vehiclePilot) 
            : Vehicle(_vehiclePilot)
        {
            
        }

    protected:
        int travelDistance;
        int moveUntilRestTime;

        void set_vehicle_name(std::string vehicleName)
        {
            this->vehicleName = vehicleName;
        }

    private:
        
    }; // END OF class VehicleGround

    // ---------------------------

    class VehicleAir : Vehicle
    {
    public:

        // Constructor removal
        VehicleAir() = delete;

        VehicleAir(std::string _vehicleName, std::string _vehiclePilot, unsigned short _vehicleClass, int _travelDistance, unsigned short _speed) 
            : Vehicle(_vehiclePilot)
        {
            this->travelDistance = _travelDistance;
        }

    protected:
        int travelDistance;
        int distanceCutRatio;        
    private:
        
    }; // END OF class VehicleAir

    // ---------------------------

    /*
    Живые классы ТС
    */

    // НАЗЕМКА

    export EXPORT_API class GV_Humpback : VehicleGround
    {
    public:        

        // Конструкторы

        GV_Humpback() = delete;

        GV_Humpback(std::string _vehiclePilot)
            : VehicleGround(_vehiclePilot)
        {
            std::string _vehicleName = "Верблюд";
            this->numberOfRests = 0;
            this->moveUntilRestTime = calc_rest_time();
        }

    protected:

    private:

        int numberOfRests;

        int calc_rest_time()
        {
            // Первый раз: 5
            // Все последующие разы : 8

            int totalRestTime = 0;

            return totalRestTime;
        }

    }; // END OF class GV_Humpback

    export EXPORT_API class GV_Humpback_Fast : VehicleGround
    {
    public:

    protected:

    private:

    }; // END OF class GV_Humpback_Fast

    export EXPORT_API class GV_Centaur : VehicleGround
    {
    public:

    protected:

    private:

    }; // END OF  class GV_Centaur

    export EXPORT_API class GV_AllTBoots : VehicleGround
    {
    public:

    protected:

    private:

    }; // END OF class GV_AllTBoots

    // ВОЗДУХ

    export EXPORT_API class GA_Magic_Carpet : VehicleAir
    {
    public:

    protected:

    private:

    }; // END OF class GA_Magic_Carpet

    export EXPORT_API class GA_Eagle : VehicleAir
    {
    public:

    protected:

    private:

    }; // END OF class GA_Eagle

    export EXPORT_API class GA_Broom : VehicleAir
    {
    public:

    protected:

    private:

    }; // END OF class GA_Broom

    /* ДОП ФУНКЦИИ ---------------------------------------------------------------------- */

    void print_vehicle(Vehicle * vehicle)
    {
        std::cout << "Пилот: " << vehicle->get_vehicle_pilot() << ",  Название: " << vehicle->get_vehicle_name() << ", Скорость: " << vehicle->get_vehicle_speed();
    }

} // END OF NAMESPACE JINX