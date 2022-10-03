
template <class T> ndarray<T>::operator Series<T>() const{
  return Series<T>(shape, value);
}
template <class T> ndarray<T>::operator Images<T>() const{
  std::vector<uint16_t> temp_shape = shape;
  if (temp_shape.size() == 1) {
    temp_shape.push_back(shape[0]);
    temp_shape[0] = 1;
  }

  return Images<T>(temp_shape, value);
}