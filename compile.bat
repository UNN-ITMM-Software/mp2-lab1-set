@echo off
echo ===== COMPILING TESTS =====
g++ -I./include -I./gtest -std=c++17 ^
src/tbitfield.cpp ^
src/tset.cpp ^
test/test_main.cpp ^
test/test_tbitfield.cpp ^
test/test_tset.cpp ^
test/test_extra.cpp ^
test/test_simple.cpp ^
gtest/gtest-all.cc ^
-o tests.exe

if errorlevel 1 goto error

echo.
echo ===== RUNNING 51 TESTS =====
tests.exe

echo.
echo ===== COMPILING SIEVE =====
g++ -I./include -std=c++17 src/tbitfield.cpp src/tset.cpp samples/sample_prime_numbers.cpp -o sieve.exe
if errorlevel 1 (
    echo SIEVE: COMPILATION FAILED
) else (
    echo SIEVE: COMPILATION SUCCESS
    echo.
    echo ===== RUNNING SIEVE =====
    sieve.exe
)

goto end

:error
echo TESTS: COMPILATION FAILED
:end
echo.
pause