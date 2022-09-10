import thunder as td
from thunder.images.readers import fromlist, fromarray, frompng, fromtif, frombinary, fromexample
from thunder import series, images
import numpy as np

data = td.images.fromrandom()
ts = data.median_filter(3).toseries()
frequencies = ts.detrend().fourier(freq=3).toarray()
data = fromtif("./data/1.tif")
# data = frompng("./data/1.png")

a = np.array([211, 12, 5, 6, 3, 4, 17, 18, 9, 10, 1, 1]).reshape((3, 4))


data = series.fromlist(a)

print(data.var().toarray())
