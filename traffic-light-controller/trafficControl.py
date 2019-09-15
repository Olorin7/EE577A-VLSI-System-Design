# This code can run in Python 3.7.2(x64)
'''
This program simulates the traffic light controller between Jeffson Bl and McClintock Av, as well as the pedestrian light,
the output is a graph that brifly describes the light condition. "g" represents green, "y" represents yellow, "r" represents
yellow and a certain number represents the countdown time.
'''
import time

WHOLE_TIME = 119  # whole durition
COUNT_TIME = 27  # countdown durition
PRE_PED_TIME = 1
RED_TIME = 3
YELLOW_TIME = 3
PED_TIME = 8  # pededtrian green durition
JEF_TIME = 50  # jeffson green durition
MCC_TIME = 20  # mcclintock green durition

mcctimer = WHOLE_TIME - PED_TIME - COUNT_TIME - 1
jeftimer = mcctimer - RED_TIME - MCC_TIME - YELLOW_TIME


class state:
    def __init__(self):
        self.stateQ = 0
        self.timer = 0

    def stateUpdate(self):
        if self.timer == 0:
            self.timer = WHOLE_TIME - 1
        else:
            self.timer -= 1

        pedSignal = (self.timer == 0) or (
            self.timer == WHOLE_TIME - PED_TIME) or (
                self.timer == WHOLE_TIME - PED_TIME - COUNT_TIME - 1)
        mccSignal = (self.timer == mcctimer - RED_TIME) or (
            self.timer == mcctimer - RED_TIME - MCC_TIME) or (
                self.timer == mcctimer - RED_TIME - MCC_TIME - YELLOW_TIME)
        jefSignal = (self.timer == jeftimer - RED_TIME) or (
            self.timer == jeftimer - RED_TIME - JEF_TIME) or (
                self.timer == jeftimer - RED_TIME - JEF_TIME - YELLOW_TIME)
        if (pedSignal or mccSignal or jefSignal):
            self.stateQ = (self.stateQ + 1) % 9


# light of Jeffson Bl
class Jeffson:
    def __init__(self):
        self.light = 'r'

    def setValue(self, light):
        self.light = light


# light of McClintock Av
class McClintock:
    def __init__(self):
        self.light = 'r'

    def setValue(self, light):
        self.light = light


# light of Pedestrian
class Pedestrian:
    def __init__(self):
        self.light = 'g'

    def setValue(self, light):
        self.light = light


# print the outout in graph
def printLight(state, jef, mcc, ped):
    print("timer: " + str(state.timer))
    for i in range(5):
        print("\t\t|\t\t|")

    print("\t\t|  McClintock   |")
    print("\t\t" + ped.light + "\t" + mcc.light + "\t" + ped.light)

    print("---------------- \t\t ----------------")
    print("\n\n")
    print("\tJeffson\t\t\t  Jeffson")
    print("\t\t" + jef.light + "\t\t" + jef.light)
    print("\n\n")

    print("---------------- \t\t ----------------")
    print("\t\t" + ped.light + "\t" + mcc.light + "\t" + ped.light)
    print("\t\t|  McClintock   |")
    for i in range(5):
        print("\t\t|\t\t|")


# change every St's light based on the state
def lightControl(state, jef, mcc, ped):
    curState = state.stateQ
    time = str(state.timer - 84)
    if (curState == 0):
        jef.setValue("r")
        mcc.setValue("r")
        ped.setValue("g")
    elif (curState == 1):
        jef.setValue("r")
        mcc.setValue("r")
        ped.setValue(time)
    elif (curState == 2):
        jef.setValue("r")
        mcc.setValue("r")
        ped.setValue("r")
    elif (curState == 3):
        jef.setValue("r")
        mcc.setValue("g")
        ped.setValue("r")
    elif (curState == 4):
        jef.setValue("r")
        mcc.setValue("y")
        ped.setValue("r")
    elif (curState == 5):
        jef.setValue("r")
        mcc.setValue("r")
        ped.setValue("r")
    elif (curState == 6):
        jef.setValue("g")
        mcc.setValue("r")
        ped.setValue("r")
    elif (curState == 7):
        jef.setValue("y")
        mcc.setValue("r")
        ped.setValue("r")
    else:
        jef.setValue("r")
        mcc.setValue("r")
        ped.setValue("r")

    printLight(state, jef, mcc, ped)


if __name__ == "__main__":

    # initialize
    traffic = state()
    jeffson = Jeffson()
    pedestrian = Pedestrian()
    mcClintock = McClintock()

    lightControl(traffic, jeffson, mcClintock, pedestrian)
    while (True):
        time.sleep(1)  # refresh time 1s
        traffic.stateUpdate()
        lightControl(traffic, jeffson, mcClintock, pedestrian)
