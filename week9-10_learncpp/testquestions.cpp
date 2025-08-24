/*2. Faulty Sensor Detection

Suppose you have a stream of temperature readings from a sensor. Sometimes, the sensor 
glitches and produces values that are far outside the normal range.

Write a function that takes a vector of readings and returns the indices of likely 
faulty readings, where a faulty reading is one that differs from the rolling average 
of the last 5 samples by more than 10°C.*/

#include <vector>

class Readings
{
    private:

    double sum;
    std::vector<double> data;
    int index;
    
    public:

    Readings() :
        sum{0},
        index{0},
        data([0;0;0;0;0])
        {}

    std::vector<int> faultyReadings()
    {
        if (index < 4)
        {
            data[index] = sample;
            sum += sample;
            ++index;
            return -1;
        }

        sum -= data[index];
        sum += sample;
        data[index] = sample;

        if (sample > (sum / 5.0) + 10.0) return index;
        
        index = (index+1)%5;
    }
};