import numpy as np
import templatelib

# Read and modify an array
a = np.zeros(4)
templatelib.examples.array(a, 2.0)

print(a)  # => [2.0 2.0 2.0 2.0]

# Wraped C++ class
