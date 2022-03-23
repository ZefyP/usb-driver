import json
from csv import reader as csvreader

# Read next line and return two values that were separated by 
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
        return key.strip(), value.strip()


def set_acceptance_criteria():
    """
        acceptance_criteria_dict = { <parameter to check> : (<minimum acceptable value>, <maximun acceptable value> ) }
    """
    acceptancereader = csvreader(open('/home/zefy/trial/PSPOH/gui-for-hybrids-testing-on-crate-systems/acceptance_criteria/PSPOH.csv', 'r'), delimiter=';', skipinitialspace=True) 
    for parameter, load, min, max  in acceptancereader:
        if load == '':
            acceptance_criteria_dict[parameter] = ( float(min) , float(max) )
        else:
            if parameter not in acceptance_criteria_dict:
                acceptance_criteria_dict[parameter] = {}
            acceptance_criteria_dict[parameter][load] = ( float(min), float(max) )
    print("ACCEPTANCE CRITERIA \n",acceptance_criteria_dict)
    return acceptance_criteria_dict

def check_range(meas, min, max, load=None, vin=None):
    for vin, loads in tests.items():
        #values is the dict with keys: meas and vals: vals
        if load is None:
            for load, values in loads.items():
                #check that measurement exists in the dict
                if not meas in values:
                    print("Vin {} with load {} measurement {} not found".format(vin, load, meas))
                    continue
                if float(values[meas]) < min or float(values[meas]) > max:
                    print("Vin {} with load {}: Measurement {} out of range. Expected {} <= {} <= {}".format(vin, load, meas, min, values[meas], max))
                    # self.test_result_cause = "Vin {} load {}: Measurement {} out of range. Expected {} <= {} <= {}".format(vin, load, meas, min, values[meas], max)
                    return False
                else:
                    print("Vin {} with load {}: Measurement {} within range. Expected {} <= {} <= {}".format(vin, load, meas, min, values[meas], max))
                    return True
        else:
            #check that measurement exists in the dict
            values = loads[load]
            if not meas in values:
                print("Vin {} with load {}  measurement {} not found".format(vin, load, meas))
                continue
            if float(values[meas]) < min or float(values[meas]) > max:
                print("Vin {} with load {} : Measurement {} out of range. Expected {} <= {} <= {}".format(vin, load, meas, min, values[meas], max))
                # self.test_result_cause += "Vin {} with load {}: Measurement {} out of range. Expected {} <= {} <= {}".format(vin, load, meas, min, values[meas], max)
                return False
            else:
                return True


#Redefine for PSPOH. This should be Zefy's script to process the output
#results_file = '/home/zefy/trial/PSPOH/usb-driver/results/11_02_22_Long_Tests_010/result2.txt'
results_file = '/home/zefy/trial/PSPOH/usb-driver/results/temp/result0.txt'

hybrid = ""
maxLoad = ""
step = ""
minLoad = ""
SupStep = ""
SupMin = ""
SupMax = ""

vin = 0
# supply variables are global

acceptance_criteria_dict = {}
acceptance_criteria_dict = set_acceptance_criteria()
hybrid_status = ""
test_result_cause = ""

file = open(results_file, 'r')

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
#
k, minLoad = next_line(file)
print("{} --> {}".format(k,minLoad))
if k != "minLoad":
    print("Expected minLoad got instead {}".format(k))
#
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

    if k == "header-end" and v == "0":
        print("Full header read")
        reading_header = False
    else:
       k , v = next_line(file)
       print("{} --> {}".format(k,v))
       
    print( "sup values", SupMin, SupMax, SupStep)

#print("Setup parameters: hybrid: {}, maxLoad: {}, step: {}".format(hybrid, maxLoad, step))

tests = {}
# load = -int(step)

k, v = next_line(file)
if k == "SET:VIN":
    v = round( float(v), 2) # round to 2 decimal places
    vin = str(v)
    tests[vin] = {}
else:
    print("Expected VIN got {}".format(k))
    # break
    # sys.exit(1)
k, v = next_line(file)
if k != "HIV" and v != "ON":
    print("Expected initial HIV;ON, got instead {}={}".format(k, v))
    # break
    # sys.exit(1)
# Process results until end of file
load = ''
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
        if vin not in tests:
            tests[vin] = {}
        continue
    if k == "SET:LOAD":
        prev_load = load
        v = round( float(v) , 2) # round to 2 decimal places
        load = str(v)
        print("Processed load {}, next cycle load {}".format(prev_load, load))
        load = int( float(load) * 100 )
        if load not in tests[vin]:
            tests[vin][load] = {}
        # continue
    if k == "HIV:ON":
        continue
    
    if vin in tests:
        if load in tests[vin]:
            if k in tests[vin][load]:
                print("Duplicate key for test at load {}: {}={}".format(load, k, v))
            tests[vin][load][k] = v
    # END OF PSPOH process output


#print(json.dumps(tests, sort_keys=False, indent=4))        

print( "sup values", SupMin, SupMax, SupStep)

# -----------------------------------------------------------------------------------------------------------------------------------------
# produce_hybrid_status()
print("Checking ranges of measurements")
# Redefine for PSPOH -> this should be the part where the data is checked to be inside a range.
value_correct = True 

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


        if( parameter == "V_HYB_HIV_OUT" ):  
            check_range(meas, 0, max, 0, 7)
            print ("HELLO WORLD -----------------------------------------------")
            

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

print("Printing results...")
print(json.dumps(tests, sort_keys=False, indent=4))        
print(hybrid_status)
print(test_result_cause)