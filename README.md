# OnePlusLL-impl

## Установка инструменов
## [OpenCilk](https://github.com/OpenCilk/)
* `git clone -b opencilk/v1.0 https://github.com/OpenCilk/infrastructure`
* `infrastructure/tools/get $(pwd)/opencilk`
* `infrastructure/tools/build $(pwd)/opencilk $(pwd)/build`
* `cd $(pwd)/build`
* `cmake -DCMAKE_INSTALL_PREFIX=<путь до папки с проектом>/Tools/OpenCilk -P cmake_install.cmake`

## [Google Tests](https://github.com/google/googletest)
* `git clone https://github.com/google/googletest.git <путь до папки с проектом>/Tools/GoogleTests`

## [PCTL](https://github.com/deepsea-inria/pctl/blob/master/doc/pctl.md)
* `wget https://raw.githubusercontent.com/deepsea-inria/pctl/master/script/get.sh`
* `chmod +x ./get.sh`
* `./get.sh <путь до папки с проектом>/parallel_algorithms-hw/PCTL`

## [PyTorch](https://pytorch.org/tutorials/advanced/cpp_frontend.html)
* `wget https://download.pytorch.org/libtorch/nightly/cpu/libtorch-shared-with-deps-latest.zip`
* `unzip libtorch-shared-with-deps-latest.zip`

