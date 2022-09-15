
template <class T> ndarray<T>::operator Series<T>() {
  return Series<T>(shape, value);
}
template <class T> ndarray<T>::operator Images<T>() {
  if (shape.size() == 1) {
    shape.push_back(shape[0]);
    shape[0] = 1;
  }
  return Images<T>(shape, value);
}