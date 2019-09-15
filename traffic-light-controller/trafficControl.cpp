/*This code can be compiled in Windows 10 with gcc version 8.1.0*/
/*
This program simulates the traffic light controller between Jeffson Bl and McClintock Av, as well as the pedestrian light,
the output is a graph that brifly describes the light condition. "g" represents green, "y" represents yellow, "r" represents
yellow and a certain number represents the countdown time. 
*/

#include <iostream>
#include <windows.h>

#define WHOLE_TIME 119 //whole durition
#define COUNT_TIME 27  //countdown durition
#define PRE_PED_TIME 1
#define RED_TIME 3
#define YELLOW_TIME 3
#define PED_TIME 8  //pededtrian green durition
#define JEF_TIME 50 //jeffson green durition
#define MCC_TIME 20 //mcclintock green durition

using namespace std;

int mcctimer = WHOLE_TIME - PED_TIME - COUNT_TIME - 1;
int jeftimer = mcctimer - RED_TIME - MCC_TIME - YELLOW_TIME;

//the finite state machine
class state
{
private:
    uint32_t stateQ;
    int timer;

public:
    state();
    uint32_t getState();
    int getTimer();
    void reset();
    void stateUpdate();
};

//light of Jeffson Bl
class Jeffson
{
private:
    bool green;
    bool yellow;
    bool red;

public:
    Jeffson();
    string getValue();
    void setValue(bool g, bool y, bool r);
};

//light of McClintock Av
class McClintock
{
private:
    bool green;
    bool yellow;
    bool red;

public:
    McClintock();
    string getValue();
    void setValue(bool g, bool y, bool r);
};

//light of Pedestrian
class Pedestrian
{
private:
    bool green;
    int countdown;
    bool red;

public:
    Pedestrian();
    string getValue();
    void setValue(bool g, int c, bool r);
};

Pedestrian::Pedestrian()
{
    green = true;
    countdown = -1;
    red = true;
}

string Pedestrian::getValue()
{
    if (this->green)
    {
        return "g";
    }
    else if (this->red)
    {
        return "r";
    }
    else
    {
        return to_string(countdown);
    }
}

void Pedestrian::setValue(bool green, int countdown, bool red)
{
    this->green = green;
    this->countdown = countdown;
    this->red = red;
}

Jeffson::Jeffson()
{
    green = false;
    yellow = false;
    red = true;
}

string Jeffson::getValue()
{
    if (this->green)
    {
        return "g";
    }
    else if (this->red)
    {
        return "r";
    }
    else
    {
        return "y";
    }
}

void Jeffson::setValue(bool green, bool yellow, bool red)
{
    this->green = green;
    this->yellow = yellow;
    this->red = red;
}

McClintock::McClintock()
{
    green = false;
    yellow = false;
    red = true;
}

string McClintock::getValue()
{
    if (this->green)
    {
        return "g";
    }
    else if (this->red)
    {
        return "r";
    }
    else
    {
        return "y";
    }
}

void McClintock::setValue(bool green, bool yellow, bool red)
{
    this->green = green;
    this->yellow = yellow;
    this->red = red;
}

state::state()
{
    stateQ = 0;
    timer = 0;
}

//get the current state
uint32_t state::getState()
{
    return stateQ;
}

// get the current timer
int state::getTimer()
{
    return timer;
}

void state::reset()
{
    stateQ = 0;
    timer = 0;
}

//update light state every 1s
void state::stateUpdate()
{
    if (timer == 0)
    {
        timer = WHOLE_TIME - 1;
    }
    else
    {
        timer--;
    }

    bool pedSignal = (timer == 0) || (timer == WHOLE_TIME - PED_TIME) || (timer == WHOLE_TIME - PED_TIME - COUNT_TIME - 1);
    bool mccSignal = (timer == mcctimer - RED_TIME) || (timer == mcctimer - RED_TIME - MCC_TIME) || (timer == mcctimer - RED_TIME - MCC_TIME - YELLOW_TIME);
    bool jefSignal = (timer == jeftimer - RED_TIME) || (timer == jeftimer - RED_TIME - JEF_TIME) || (timer == jeftimer - RED_TIME - JEF_TIME - YELLOW_TIME);
    if (pedSignal | mccSignal | jefSignal)
    {
        stateQ = (stateQ + 1) % 9;
    }
}

//print the outout in graph
void print(state &state, Jeffson &jeffson, McClintock &mcClintock, Pedestrian &pedestrian)
{
    cout << "timer: " << state.getTimer() << endl;
    for (int i = 0; i < 5; i++)
    {
        cout << "\t\t|\t\t|\n";
    }
    cout << "\t\t|  McClintock   |\n";
    cout << "\t\t" << pedestrian.getValue() << "\t" << mcClintock.getValue() << "\t" << pedestrian.getValue() << "\n";

    cout << "---------------- \t\t ----------------\n";
    cout << "\n\n";
    cout << "\tJeffson\t\t\t  Jeffson\n";
    cout << "\t\t" << jeffson.getValue() << "\t\t" << jeffson.getValue() << "\n";
    cout << "\n\n";

    cout << "---------------- \t\t ----------------\n";
    cout << "\t\t" << pedestrian.getValue() << "\t" << mcClintock.getValue() << "\t" << pedestrian.getValue() << "\n";
    cout << "\t\t|  McClintock   |\n";
    for (int i = 0; i < 5; i++)
    {
        cout << "\t\t|\t\t|\n";
    }
}

//change every St's light based on the state
void lightControl(state &state, Jeffson &jeffson, McClintock &mcClintock, Pedestrian &pedestrian)
{
    int stateQ = state.getState();
    int time = state.getTimer() - 84;
    switch (stateQ)
    {
    case 0:
        jeffson.setValue(false, false, true);
        mcClintock.setValue(false, false, true);
        pedestrian.setValue(true, -1, false);
        break;
    case 1:
        jeffson.setValue(false, false, true);
        mcClintock.setValue(false, false, true);
        pedestrian.setValue(false, time, false);
        break;
    case 2:
        jeffson.setValue(false, false, true);
        mcClintock.setValue(false, false, true);
        pedestrian.setValue(false, -1, true);
        break;
    case 3:
        jeffson.setValue(false, false, true);
        mcClintock.setValue(true, false, false);
        pedestrian.setValue(false, -1, true);
        break;
    case 4:
        jeffson.setValue(false, false, true);
        mcClintock.setValue(false, true, false);
        pedestrian.setValue(false, -1, true);
        break;
    case 5:
        jeffson.setValue(false, false, true);
        mcClintock.setValue(false, false, true);
        pedestrian.setValue(false, -1, true);
        break;
    case 6:
        jeffson.setValue(true, false, false);
        mcClintock.setValue(false, false, true);
        pedestrian.setValue(false, -1, true);
        break;
    case 7:
        jeffson.setValue(false, true, false);
        mcClintock.setValue(false, false, true);
        pedestrian.setValue(false, -1, true);
        break;
    case 8:
        jeffson.setValue(false, false, true);
        mcClintock.setValue(false, false, true);
        pedestrian.setValue(false, -1, true);
        break;
    default:
        break;
    }
    print(state, jeffson, mcClintock, pedestrian);
}

int main()
{
    //initialize
    state traffic;
    Jeffson jeffson;
    Pedestrian pedestrian;
    McClintock mcClintock;

    lightControl(traffic, jeffson, mcClintock, pedestrian);
    while (true)
    {
        Sleep(1000); //refresh time 1s
        traffic.stateUpdate();
        lightControl(traffic, jeffson, mcClintock, pedestrian);
    }
    return 0;
}
