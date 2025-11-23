
# Build the project using CMake

in Windows 
```{Windows CMD}
#in MSVC Command Prompt:
cmake -DCMAKE_C_COMPILER=cl -DCMAKE_CXX_COMPILER=cl -S . -B ./build -G Ninja
cmake --build ./build --target learn_itk
```
