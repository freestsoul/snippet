/**
 * power - Calculate the power of number.
 * @param base: Base value.
 * @param exponent: Exponent value.
 *
 * @return base raised to the power exponent
 **/
double power(double base, int exponent) {
  double result = base;
  int i = 0;

  for (i = 1; i < exponent; ++i) {
    result *= base;
  }

  return result;
}
