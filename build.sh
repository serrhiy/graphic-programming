g++ -std=c++20 -I./headers -o main $(find . -type f -name '*.c' -o -name '*.cpp') -lglfw3 -lGL -lm && ./main && rm main && echo 'Success!'