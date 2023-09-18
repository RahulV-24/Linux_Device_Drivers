# Compilation
This code can be compiled by following these steps.

### 1. Clone the Repository:
  ``` 
  $ git clone https://github.com/RahulV-24/Linux_Device_Drivers.git
  $ cd Hello_World/
  ```
### 2. Compile the Module:
  ``` 
  $ make
  ```
### 3. Load the Module:
  ``` 
  $ sudo insmod Hello_world.ko
  ```
This command loads the character driver module into the kernel.

### 4. Output:
  ``` 
  $ dmesg
  ```
The output of dmesg contains messages produced by the device drivers.
