#include "ndarray.hpp"

/**
 * @brief Clip values in an array above and below provided values
 *
 * @param min_value min value to clip
 * @param max_value max value to clip
 */
void clip(const T &min_value, const T &max_value)
{

    transform(std::begin(value), std::end(value), std::begin(value),
              [&](const T &v)
              { return clamp(v, min_value, max_value); });
}

/**
 * @brief Applied the supplied function to every element in matrix
 *
 * @param func Unary function
 * @return NDArray<T> Structure with result
 */
void map(T (*func)(T))
{
    transform(std::begin(value), std::end(value), value.begin(), func);
}

/**
 * @brief Applies a function which should evaluate to boolean, along the first axis
 *
 * @param func A function that accepts data of type NDArray<T>
 * @return NDArray<T> Filtered data
 */
NDArray<T> filter(bool (*func)(NDArray<T>))
{
    int count = 0;
    vector<T> output;

    // Cycling through the first dimension
    for (uint16_t i = 0; i < shape[0]; i++)
    {
        NDArray<T> temp = this->getPosition({i});
        if (func(temp))
        {
            for (int j = 0; j < temp.size(); j++)
            {
                output.push_back(temp[j]);
            }
            // output.insert(output.end(), temp.getValue().begin(), temp.getValue().end());
            count++;
        }
    }

    // Generating new shape. Overwrites only first dimension
    vector<uint16_t> new_shape = this->shape;
    if (count == 0)
        new_shape = {0};
    else
        new_shape[0] = count;

    return NDArray(new_shape, output);
}

NDArray<T> filter(NDArray<T> input, bool (*func)(NDArray<T>))
{
    return input.filter(func);
}

NDArray<T> applyFunc(NDArray<T> input, std::function<T(NDArray<T>)> func)
{
    vector<T> output_value;
    vector<uint16_t> output_shape;

    // Single dimension case
    if (input.getShape().size() == 1)
    {
        input.reshape({1, input.getShape()[0]});
    }

    for (uint16_t i = 0; i < input.getShape()[0]; i++)
    {
        // Extract all other dimensions
        NDArray<T> temp = input.getPosition({i});

        if (temp.shape.size() != 1)
            temp.reshape({(uint16_t)(temp.shape[0] * temp.count())});

        // Append maximum along those dimensions
        output_value.push_back(func(temp));
    }
    output_shape = {input.getShape()[0]};

    return NDArray(output_shape, output_value);
}

/**
 * @brief Returns a vector of max values.
 * If matrix is monodimensional returns a single max value, if there is more than a
 * dimension, it cycles through the first returning the maximum along all other dimensions.
 *
 * @return NDArray<T> Structure containing the vector of maximum value(s)
 */
NDArray<T> max()
{
    return applyFunc(*this, [](NDArray<T> a)
                     { return *max_element(a.begin(), a.end()); });
}
static NDArray<T> max(NDArray<T> input)
{
    return input.max();
}

/**
 * @brief Returns a vector of min values.
 * If matrix is monodimensional returns a single min value, if there is more than a
 * dimension, it cycles through the first returning the minimum along all other dimensions.
 *
 * @return NDArray<T> Structure containing the vector of minimum value(s)
 */
NDArray<T> min()
{
    return applyFunc(*this, [](NDArray<T> a)
                     { return *min_element(a.begin(), a.end()); });
}
static NDArray<T> min(NDArray<T> input)
{
    return input.min();
}

/**
 * @brief Returns a vector of sum values.
 * If matrix is monodimensional returns a single sum value, if there is more than a
 * dimension, it cycles through the first returning the sum along all other dimensions.
 *
 * @return NDArray<T> Structure containing the vector of sum value(s)
 */
NDArray<T> sum()
{
    return applyFunc(*this, [](NDArray<T> a)
                     { return accumulate(a.begin(), a.end(), 0.0); });
}
static NDArray<T> sum(NDArray<T> input)
{
    return input.sum();
}

/**
 * @brief Returns a vector of mean values.
 * If matrix is monodimensional returns a single mean value, if there is more than a
 * dimension, it cycles through the first returning the mean along all other dimensions.
 *
 * @return NDArray<T> Structure containing the vector of mean value(s)
 */
NDArray<T> mean()
{
    return applyFunc(*this, [](NDArray<T> a)
                     { return a.sum()[0] / a.count(); });
}
static NDArray<T> mean(NDArray<T> input)
{
    return input.mean();
}

/**
 * @brief Returns a vector of standard deviation values.
 * If matrix is monodimensional returns a single standard deviation value, if there is more than a
 * dimension, it cycles through the first returning the standard deviation along all other dimensions.
 *
 * @return NDArray<T> Structure containing the vector of standard deviation value(s)
 */

NDArray<T> std()
{
    return applyFunc(*this, [](NDArray<T> a)
                     {
            T total = 0;
            for (int i = 0; i < a.count(); i++)
            {
                total += (a[i] - a.mean()[0]) * (a[i] - a.mean()[0]);
            }
            return sqrt(total / a.count()); });
}
static NDArray<T> std(NDArray<T> input)
{
    return input.std();
}

/**
 * @brief Returns a vector of variance values.
 * If matrix is monodimensional returns a single variance value, if there is more than a
 * dimension, it cycles through the first returning the variance along all other dimensions.
 *
 * @return NDArray<T> Structure containing the vector of variance value(s)
 */
NDArray<T> var()
{
    return applyFunc(*this, [](NDArray<T> a)
                     {
            T total = 0;
            for (int i = 0; i < a.count(); i++)
            {
                total += (a[i] - a.mean()[0]) * (a[i] - a.mean()[0]);
            }
            return (total / a.count()); });
}
static NDArray<T> var(NDArray<T> input)
{
    return input.var();
}