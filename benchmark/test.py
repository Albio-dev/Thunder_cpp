import thunder as td
from thunder.images.readers import fromlist, fromarray, frompng, fromtif, frombinary, fromexample
from thunder import series, images
import numpy as np
from random import seed
from random import randint

# seed random number generator
seed(1)


@profile
def read_data_tif():
    for _ in range(10000):
        value = randint(1, 4)
        data = fromtif("./data/" + str(value) + ".tif")

@profile
def read_data_array():
    data = np.random.rand(10, 10)
    for _ in range(10000):
        data = fromarray(data)


@profile
def function_mean():
    for _ in range(10000):
        data = fromtif("./data/1.tif")
        data.mean()

@profile
def function_std():
    for _ in range(10000):
        data = fromtif("./data/1.tif")
        data.std()

@profile
def function_var():
    for _ in range(10000):
        data = fromtif("./data/1.tif")
        data.var()



read_data_tif()
read_data_array()
function_mean()
function_std()
function_var()