import sys
from csv import reader as csvreader

results_file = '/home/zefy/trial/PSPOH/usb-driver/results/hiv-test/result0.txt'
# results_file = '/home/zefy/trial/PSPOH/usb-driver/results/Long_Tests/result14.txt'

file = open(results_file, 'r')
#/home/zefy/trial/PSPOH/usb-driver/results/test1/result0.txt

ACCEPTANCE_CRITERIA = 'PSPOH/gui-for-hybrids-testing-on-crate-systems/acceptance_criteria/PSPOH.csv' #To be read from the database
acceptance_criteria_dict = {}


# TO BE FILLED WHEN PROCESSING OUTPUT FILE
SupStep = "0"
SupMin = "0"
SupMax = "12"

hybrid_status = None
scpi_errors = {}

# Read next line and return two values that were separated by ;
def next_line(file):
    while True:
        line = file.readline()
        if line == "":
            return "EOF", "EOF"
        line = line.strip()
        if line == "":
            continue
        #print("{}".format(line))
        key, value = line.split(';')

        if key == "SCPI ERROR":
            err_k, err_v = value.split(',')
            scpi_errors[err_k] = err_v
            continue
        return key.strip(), value.strip()

hybrid = ""
maxLoad = ""
step = ""
minLoad = ""
reading_header = True

print("Setup Parameters:")

# read first line
k, hybrid = next_line(file)
print("{} --> {}".format(k,hybrid))
if k != "Hybrid":
    print("Expected Hybrid got instead {}".format(k))
# read 2nd line
k, maxLoad = next_line(file)
print("{} --> {}".format(k,maxLoad))
if k != "maxLoad":
    print("Expected maxLoad got instead {}".format(k))
# 
k, step = next_line(file)
print("{} --> {}".format(k,step))
if k != "step":
    print("Expected step got instead {}".format(k))

k, minLoad = next_line(file)
print("{} --> {}".format(k,minLoad))
if k != "minLoad":
    print("Expected minLoad got instead {}".format(k))

k, SupStep = next_line(file)
print("{} --> {}".format(k,SupStep))
if k != "SupStep":
    print("Expected SupStep got instead {}".format(k))

k, SupMin = next_line(file)
print("{} --> {}".format(k,SupMin))
if k != "SupMin":
    print("Expected SupMin got instead {}".format(k))

k, SupMax = next_line(file)
print("{} --> {}".format(k,SupMax))
if k != "SupMax":
    print("Expected SupMax got instead {}".format(k))

while reading_header:
    k , v = next_line(file)

    if k == "header-end" and v == "0":
        #print("Full header read")
        reading_header = False

    print("{} --> {}".format(k,v))

           
#print("Setup parameters: hybrid: {}, maxLoad: {}, step: {}".format(hybrid, maxLoad, step))

tests = {}
load = 0
vin = 0
k, v = next_line(file)
if k == "SET:VIN":
    vin = v
else:
    print("Expected VIN got {}".format(k))
    sys.exit(1)
k, v = next_line(file)
if k != "HIV" and v != "ON":
    print("Expected initial HIV;ON, got instead {}={}".format(k, v))
    sys.exit(1)

# Process results until end of file
while True: 
    k, v = next_line(file)
    if k == "EOF" and v == "EOF":
        break
    if k == "Turning off" and v == "0":
        break
    if k == "SET:VIN":
        vin_prev = vin
        vin = v
        #load = 0
        print("Processed vin {}, next voltage {}".format(vin_prev, vin))
        continue
    if k == "SET:LOAD":
        prev_load = load
        load = v
        print("Processed load {}, next cycle load {}".format(prev_load, load))
        load = int( float(load) * 100 )
        # continue
    if k == "HIV:ON":
        continue
    if vin in tests:
        if load in tests[vin]:
            if k in tests[vin][load]:
                print("Duplicate key for test at load {}: {}={}".format(load, k, v))
            tests[vin][load][k] = v
    # END OF PSPOH process output



def set_acceptance_criteria():
        """
            acceptance_criteria_dict = { <parameter to check> : (<minimum acceptable value>, <maximun acceptable value> ) }
        """
        acceptancereader = csvreader(open(ACCEPTANCE_CRITERIA, 'r'), delimiter=';', skipinitialspace=True) 
        for parameter, load, min, max  in acceptancereader:
            if load == '':
                acceptance_criteria_dict[parameter] = ( float(min) , float(max) )
            else:
                if parameter not in acceptance_criteria_dict:
                    acceptance_criteria_dict[parameter] = {}
                acceptance_criteria_dict[parameter][load] = ( float(min), float(max) )
        print(acceptance_criteria_dict)



def check_range(tests, meas, min, max):
    for vin, loads in tests.items():

        #values is the dict with keys: meas and vals: vals
        for cycle, values in loads.items():
            #check that measuement exists in the dict
            if not meas in values:
                print("Vin {} Cycle {} measurement {} not found".format(vin, cycle, meas))
                continue
            if float(values[meas]) < min or float(values[meas]) > max:
                print("Vin {} Cycle {} Measurement {} out of range expected {} <= {} <= {}".format(vin, cycle, meas, min, values[meas], max))
                return False
            else:
                return True


    # def produce_hybrid_status(self):
    print("Checking ranges of measurements")
    # Redefine for PSPOH -> this should be the part where the data is checked to be inside a range.
    value_correct = True

    #check_range(self.tests, "EFF_%", 0, 55) 

    v_hiv_value = SupMax

    for v_hiv_value in range( int(SupMin), int(SupMax) , int(SupStep) ):

        for parameter in acceptance_criteria_dict:
            accepted_range = acceptance_criteria_dict[parameter]
            if( parameter == "V_HIV" ): #The accepted range for the HIV is given as a percentage of the  
                value_correct &= check_range(parameter, v_hiv_value*accepted_range[0], v_hiv_value*accepted_range[1])
            else:
                if (type(accepted_range) is dict): 
                    for _, load in enumerate(accepted_range):
                        value_correct &= check_range(parameter, accepted_range[load][0], accepted_range[load][1], int(load) )
                else:
                    value_correct &= check_range(parameter, accepted_range[0], accepted_range[1])

            if( parameter == "V_1v_L" ):
                value_correct &= check_range(parameter, v_hiv_value*accepted_range[0], v_hiv_value*accepted_range[1])
            else:
                if (type(accepted_range) is dict): 
                    for _, load in enumerate(accepted_range):
                        value_correct &= check_range(parameter, accepted_range[load][0], accepted_range[load][1], int(load) )
                else:
                    value_correct &= check_range(parameter, accepted_range[0], accepted_range[1])

            
        if value_correct == True:
            hybrid_status = "Good"
        else: 
            hybrid_status = "Bad"
        



# #voltages
# check_range(tests, "V_1v25_R", 0, 1.25)

# #ripples
# check_range(tests, "R_2v55", 0, 1) 
# check_range(tests, "R_1v25", 0, 1)
# check_range(tests, "R_1V", 0, 1)

# #check_range(tests, "EFF_%", 0, 55)
print(tests)
#print(tests[tests.keys]['V_HIV']) #show all eff results
    
    
    
    # #print(tests['12.2'][0]) #show the results of zero load at 12.2 V

# if bool(scpi_errors) : 
#     print(scpi_errors)



# arr = [31.3545,41.404,49.6556,54.3984,58.1776,60.7882,63.033,64.3899,65.5289,66.2423,66.7392,66.9503,66.9153,66.8261,66.5436,66.1927,65.894,65.6317,65.3115,64.9269,64.5853,64.1715,63.7162,63.2505]
# arr_new = str(arr)

# for i in range(0, len(arr) - 1):
#     # avg = (arr[i] + arr[i+1]) / 2 
#     arr_new.append("")
#     # arr_new.append(avg)
# arr_new.append(arr[-1])
# print(arr_new)