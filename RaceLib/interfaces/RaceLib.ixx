// RaceLib.ixx

module;

#include <iostream>
#include <string>
#include <vector>
#include <random>
#include "RaceLibExceptions.h"

// DEFINES -----------------------------

#define EXPORT_API __declspec(dllexport)

#define SPEED_HUMPBACK 10
#define SPEED_HUMPBACKFAST 40
#define SPEED_CENTAUR 15
#define SPEED_BOOTS 6

#define SPEED_CARPET 10
#define SPEED_EAGLE 8
#define SPEED_BROOM 20

// -------------------------------------

export module jinx_racegame;

// export __declspec(dllexport) symbol

namespace jinx 
{
    /*
    ������� ����������� ����� Vehicle
    */
    export EXPORT_API class Vehicle // -----------------------------------------------------------------------------------------------
    {
    public:       
    // PUBLIC CODE AREA ----------------------------------------------------------------------------------------------

        virtual void calculate_time_result(int _distance) = 0;

        // ������� ������ ----------------------------

        /*
        ��������� ���������� �������
        */
        void set_time_result(double _resultTime)
        {
            raceResultTime = _resultTime;
        }

        /*
        ���������� ��� ��
        */
        void set_vehicle_name(std::string _vehicleName)
        {
            vehicleName = _vehicleName;
        }

        /*
        ���������� �������� ��
        */
        void set_vehicle_speed(int _speed)
        {
            // RNG GENERATION

            // Random seed
            std::random_device rd;

            // Initialize Mersenne Twister pseudo-random number generator
            std::mt19937 gen(rd());

            // Generate pseudo-random numbers
            // uniformly distributed in range (1, 100)
            std::uniform_int_distribution<> dis(1, 3);
            // int ... = dis(gen);

            // --------------
            int rng_seed = dis(gen);

            std::uniform_int_distribution<> dis2(1, 2);

            if (dis2(gen) == 1)
            {
                rng_seed *= -1;
            }

            speed = _speed + rng_seed;
        }

        // ------------------------------------------

        // ������� ������ ---------------------------

        /*
        ����� ��� ��
        */
        std::string get_vehicle_name()
        {
            return vehicleName;
        }

        /*
        ����� ��� ������
        */
        std::string get_pilot_name()
        {
            return vehiclePilot;
        }

        /*
        ����� ��������
        */
        int get_vehicle_speed()
        {
            return speed;
        }

        /*
        ����� ���������
        */
        double get_race_result()
        {
            return raceResultTime;
        }

        // Overloads

        bool operator<(const Vehicle& Veh) const
        {
            return (raceResultTime < Veh.raceResultTime);
        }

        bool operator>(const Vehicle& Veh) const
        {
            return (raceResultTime > Veh.raceResultTime);
        }

        // Constructors ---------------------------
        Vehicle() = delete;

        Vehicle(std::string _vehiclePilot)
        {
            this->vehiclePilot = _vehiclePilot;
        }

        // Destructor

        // virtual ~Vehicle() = 0;

    protected:    
    // PROTECTED CODE AREA ----------------------------------------------------------------------------------------------

    private:
        
        std::string vehiclePilot;       // ����� ��
        std::string vehicleName;        // �������� ��
        int speed;                      // �������� ��
        double raceResultTime;             // ��������� ����������� ���������� �
       
    }; // END OF class Vehicle

    // ---------------------------

    class VehicleGround : public Vehicle // -----------------------------------------------------------------------------------------------
    {
    public:

        void calculate_time_result(int _distance) override = 0;

        // Constructor removal
        VehicleGround() = delete;

        VehicleGround(std::string _vehiclePilot) : Vehicle(_vehiclePilot)
        {
            vehicleType = 0;
        }

        // Destructor

        // virtual ~VehicleGround() = 0;

    protected:
        
        bool vehicleType;

    private:
        
    }; // END OF class VehicleGround ---------------------------------------------------------------------------------------------

    // ---------------------------

    class VehicleAir : public Vehicle // -----------------------------------------------------------------------------------------------
    {
    public:   

        void calculate_time_result(int _distance) override = 0;

        // Constructor removal
        VehicleAir() = delete;

        VehicleAir(std::string _vehiclePilot)
            : Vehicle(_vehiclePilot)
        {
            vehicleType = 1;
        }

        // Destructor

        // virtual ~VehicleAir() = 0;

    protected:       
        
        bool vehicleType;

    private:
        
    }; // END OF class VehicleAir ---------------------------------------------------------------------------------------------

    // ---------------------------

    /*
    ����� ������ ��
    */

    // �������

    export EXPORT_API class GV_Humpback : public VehicleGround // -----------------------------------------------------------------------------------------------
    {
    public:

        void calculate_time_result(int _distance)
        {
            // ��������:                     10
            // ����� �������� �� ������:    30
            // ������������ ������: 
            //                              ������ ���: 5
            //                              ��� ����������� ����: 8

            // VARIABLES

            double brutTime = _distance / this->get_vehicle_speed();
            double nettTime = brutTime;
            int restNum = static_cast<int>(brutTime) / 30;
            bool firstRest = true;

            for (int i = 1; i <= restNum; ++i)
            {
                if (firstRest)
                {
                    nettTime += 5;
                    firstRest = false;
                }
                else
                {
                    nettTime += 8;
                }
            }

            this->set_time_result(nettTime);
        }

        // ������������

        GV_Humpback() = delete;

        GV_Humpback(std::string _vehiclePilot)
            : VehicleGround(_vehiclePilot)
        {
            std::string _vehicleName = "�������";
            set_vehicle_name(_vehicleName);
            set_vehicle_speed(SPEED_HUMPBACK);
        }

    protected:

    private:       

    }; // END OF class GV_Humpback ---------------------------------------------------------------------------------------------

    export EXPORT_API class GV_Humpback_Fast : public VehicleGround // -----------------------------------------------------------------------------------------------
    {
    public:

        /*
        ������� ������� ����������� ��������
        ��� ������ GV_Humpback_Fast
        */
        void calculate_time_result(int _distance)
        {
            // ��������:                    40
            // ����� �������� �� ������:    10
            // ������������ ������: 
            //                              ������ ���: 5
            //                              ������ ���: 6.5
            //                              ��� ����������� ����: 8

            // VARIABLES

            double brutTime = _distance / this->get_vehicle_speed();
            double nettTime = brutTime;
            int restNum = static_cast<int>(brutTime) / 10; // TIME UNTIL REST
            bool firstRest = true;
            bool secondRest = true;

            for (int i = 1; i <= restNum; ++i)
            {
                if (firstRest)
                {
                    nettTime += 5;
                    firstRest = false;
                }
                else if (secondRest)
                {
                    nettTime += 6.5;
                    secondRest = false;
                }
                else
                {
                    nettTime += 8;
                }
            }

            this->set_time_result(nettTime);
        } // END OF calculate_time_result(int _distance)

        // ������������

        GV_Humpback_Fast() = delete;

        GV_Humpback_Fast(std::string _vehiclePilot)
            : VehicleGround(_vehiclePilot)
        {
            std::string _vehicleName = "�������-���������";
            set_vehicle_name(_vehicleName);
            set_vehicle_speed(SPEED_HUMPBACKFAST);
        }

    protected:

    private:

    }; // END OF class GV_Humpback_Fast ---------------------------------------------------------------------------------------------

    export EXPORT_API class GV_Centaur : public VehicleGround // -----------------------------------------------------------------------------------------------
    {
    public:        

        void calculate_time_result(int _distance)
        {
            // ��������:                    15
            // ����� �������� �� ������:    8
            // ������������ ������: 
            //                              ������: 2

            // VARIABLES

            double brutTime = _distance / this->get_vehicle_speed();
            double nettTime = brutTime;
            int restNum = static_cast<int>(brutTime) / 8; // TIME UNTIL REST

            for (int i = 1; i <= restNum; ++i)
            {
                nettTime += 2;
            }

            this->set_time_result(nettTime);
        }

        // ������������

        GV_Centaur() = delete;

        GV_Centaur(std::string _vehiclePilot)
            : VehicleGround(_vehiclePilot)
        {
            std::string _vehicleName = "�������";
            set_vehicle_name(_vehicleName);
            set_vehicle_speed(SPEED_CENTAUR);
        }

    protected:

    private:

    }; // END OF  class GV_Centaur ---------------------------------------------------------------------------------------------

    export EXPORT_API class GV_AllTBoots : public VehicleGround // -----------------------------------------------------------------------------------------------
    {
    public:        

        /*
        ������� ������� ����������� ��������
        ��� ������ GV_AllTBoots
        */
        void calculate_time_result(int _distance)
        {
            // ��������:                    6
            // ����� �������� �� ������:    60
            // ������������ ������: 
            //                              ������ ���: 10
            //                              ������ ���: 5

            // VARIABLES

            double brutTime = _distance / this->get_vehicle_speed();
            double nettTime = brutTime;
            int restNum = static_cast<int>(brutTime) / 60; // TIME UNTIL REST
            bool firstRest = true;

            for (int i = 1; i <= restNum; ++i)
            {
                if (firstRest)
                {
                    nettTime += 10;
                    firstRest = false;
                }                
                else
                {
                    nettTime += 5;
                }
            }

            this->set_time_result(nettTime);
        } // END OF calculate_time_result(int _distance)

        // ������������

        GV_AllTBoots() = delete;

        GV_AllTBoots(std::string _vehiclePilot)
            : VehicleGround(_vehiclePilot)
        {
            std::string _vehicleName = "�������-���������";
            set_vehicle_name(_vehicleName);
            set_vehicle_speed(SPEED_BOOTS);
        }

        // todo

    protected:

    private:

    }; // END OF class GV_AllTBoots ---------------------------------------------------------------------------------------------



    // ������ ########################################################################################################################



    export EXPORT_API class AV_Magic_Carpet : public VehicleAir // -----------------------------------------------------------------------------------------------
    {
    public:        

        // ������������

        AV_Magic_Carpet() = delete;

        AV_Magic_Carpet(std::string _vehiclePilot)
            : VehicleAir(_vehiclePilot)
        {
            std::string _vehicleName = "����-������";
            set_vehicle_name(_vehicleName);
            set_vehicle_speed(SPEED_CARPET);
        }

    protected:

    private:

    }; // END OF class AV_Magic_Carpet ---------------------------------------------------------------------------------------------

    export EXPORT_API class AV_Eagle : public VehicleAir // -----------------------------------------------------------------------------------------------
    {
    public:

        // ������������

        AV_Eagle() = delete;

        AV_Eagle(std::string _vehiclePilot)
            : VehicleAir(_vehiclePilot)
        {
            std::string _vehicleName = "���";
            set_vehicle_name(_vehicleName);
            set_vehicle_speed(SPEED_EAGLE);
        }

    protected:

    private:

    }; // END OF class AV_Eagle ---------------------------------------------------------------------------------------------

    export EXPORT_API class AV_Broom : public VehicleAir // -----------------------------------------------------------------------------------------------
    {
    public:        

        // ������������

        AV_Broom() = delete;

        AV_Broom(std::string _vehiclePilot)
            : VehicleAir(_vehiclePilot)
        {
            std::string _vehicleName = "�����";
            set_vehicle_name(_vehicleName);
            set_vehicle_speed(SPEED_BROOM);
        }

    protected:

    private:

    }; // END OF class AV_Broom ---------------------------------------------------------------------------------------------    

} // END OF NAMESPACE JINX