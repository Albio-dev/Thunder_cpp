#cd build
#cmake ..
#make 
lcov --capture --directory . --output-file coverage.info
lcov --extract coverage.info '*/src/*' --output-file ../test/coverage/coverage.info
rm coverage.info
DIR="../doc/coverage"
if [ -d "$DIR" ]; then
  mkdir ../doc/coverage
fi
cd ../doc/coverage
lcov --list coverage.info
genhtml coverage.info
