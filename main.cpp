#include <iostream>
#include <thread>
#include <map>
#include <mutex>


std::mutex station_access;
int count = 0;


void station (int time, std::string name )
{

    std::this_thread::sleep_for(std::chrono::seconds(time));
    if (count == 1)
    {
    std::cout << name << " waiting for free space " << std::endl;

    }
    station_access.lock();
    count += 1;
    std::string command;

    std::cout  << name << " arrival at the train station "  << std::endl;
    std::cout  << "Enter command depart "  << std::endl;
    std::cin >> command;
    while (command != "depart")
    {
        std::cout  << "Error command. Enter command depart "  << std::endl;
        std::cin >> command;
    }
    if (command == "depart")
    {
        count = 0;
        std::cout << "departure from the train station" << std::endl;

    }

    station_access.unlock();

}


int main()
{


    std::thread train1(station,5, "Train A");
    std::thread train2(station, 10, "Train B");
    std::thread train3(station,15, "Train C");


    train1.join();
    train2.join();
    train3.join();


    return 0;
}

