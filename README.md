# Chase-Chase-

## Windows
**1. Install a C++11 compiler:**  
Visual Studio Community: https://visualstudio.microsoft.com/downloads/ or MinGW https://osdn.net/projects/mingw/releases/

**2. Install Git:**  
	https://git-scm.com/downloads

**3. Install CMake:**  
	https://cmake.org/download

**4. Install OpenAL:**  
	https://www.openal.org/downloads

**5. Open git-bash and type:**  
```console
git clone https://github.com/TohQiQi/Chase-Chase-.git --recursive
cd Chase-Chase- 
mkdir build && cd build
cmake ..
cmake --build . --config Release
./workshop1
```

## Ubuntu
**1. install git cmake and g++**
```console
sudo apt-get -y install cmake git g++ 
```

**2. install additional packets (OpenGL, OpenAL etc)**
```console
sudo apt-get -y install libx11-dev libudev-dev xorg-dev freeglut3-dev libalut-dev libvorbis-dev libflac-dev
```

**3. download chase-chase repo**
```console
git clone https://github.com/TohQiQi/Chase-Chase-.git --recursive
```

**4. build project** 
```console
cd Chase-Chase- 
mkdir build && cd build
cmake ..
cmake --build . --config Release
./workshop1
```

## Mac OS
**1. install xcode:**    
    https://developer.apple.com/xcode/

**2. Install Git:**  
    https://git-scm.com/downloads

**3. Install CMake:**  
    https://cmake.org/download

**4. build project**   
Go to terminal and type:
```console
git clone https://github.com/TohQiQi/Chase-Chase-.git --recursive
cd Chase-Chase- 
mkdir build && cd build
cmake ..
sudo cmake --build . --config Release
./workshop1
```
