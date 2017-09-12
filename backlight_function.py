import math
num_vals = 128
'{' + ', '.join(str(int(256.0 / 4.0 * (1 - math.cos(x * math.pi /((num_vals-1)/25.0))) * (1 - math.cos(x * math.pi /((num_vals-1)/2.0))) ) ) for x in range(0,num_vals-1) ) + '}'

a1 = 0.278393
a2 = 0.230389
a3 = 0.000972
a4 = 0.078108
per = 30.0

def term(v,x,p):
    return v * math.pow(x,p)

def frange(start,end,steps):
    step = (end - start) / steps
    count = 0
    while count < steps:
        yield start
        start += step
        count += 1


print '{' + ', '.join(str(math.erf(x)) for x in frange(-1.0,1.0, 1.0/num_vals) ) + '}'
print '{' + ', '.join(str(int(256.0 * (1 - (1 / math.pow(1 + a1 * x/per + a2  * math.pow(x/per,2) + a3 * math.pow(x/per,3) + a4 * math.pow(x/per,4), 4))))) for x in range(0,num_vals-1) ) + '}'
