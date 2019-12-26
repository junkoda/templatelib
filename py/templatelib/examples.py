import templatelib._templatelib as c


def array(a, x):
    """
    Add float x to all elements to a

    Args:
      a (np.array)
      x (float)
    """

    c._examples_array(a, x)


#
# Wrapping a C++ class
#
class Class:
    """
    A C++ class that contains [1, 3, 5]

      c = Class()  # create an object
      len(c)       # length of the object => 3 
      c[1]         # 1st element => 3
    """
    def __init__(self):
        # Wrapped pointer to a C++ object
        self._class = c._examples_class_alloc()

    def __len__(self):
        return c._examples_class_len(self._class)

    def __getitem__(self, i):
        return c._examples_class_getitem(self._class, i)

    def __repr__(self):
        return "Class(%d)" % (len(self))
