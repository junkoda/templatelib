import numpy as np
import templatelib

print(templatelib.__dict__)

# Read and modify an array
a = np.zeros(4)
templatelib.examples.array(a, 2.0)

print(a)  # => [2.0 2.0 2.0 2.0]

# Wraped C++ class
c = templatelib.Class()
print(c)
for x in c:
    print(x)
