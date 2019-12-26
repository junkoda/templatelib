import templatelib._templatelib as c


def array(a, x):
    """
    Add float x to all elements to a

    Args:
      a (np.array)
      x (float)
    """

    c._examples_array(a, x)


class Class:
    def __init__(self):
        self._class = c._examples_class_alloc()

    def __repr__(self):
        return "Class()"
