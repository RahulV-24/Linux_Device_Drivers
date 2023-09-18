# About
This contains character driver code for Linux version 6.2.0.

A Character ('c') Device is one with which the Driver communicates by sending and receiving single characters (bytes, octets).

# Compilation
This code can be compiled by following these steps.

### 1. Clone the Repository:
  ``` 
  $ git clone https://github.com/RahulV-24/Linux_Device_Drivers.git
  $ cd character_driver
  ```
### 2. Compile the Module:
  ``` 
  $ make
  ```
### 3. Load the Module:
  ``` 
  $ sudo insmod char_drv.ko
  ```
This command loads the character driver module into the kernel.

# Usage

### 1. check for the Major number:
  ``` 
  $ dmesg
  ```
The output contains messages produced by the device drivers.
### 2. Create a Device File:
  ``` 
  $ sudo mknod /dev/char_drv c 238 0

  ```
Here major no. is 238.

### 3.Write Data to the Device:

You can write data to the device file using standard file operations. For example:
```
$ echo "Hello, Character Driver!" > /dev/char_drv
```
### 4.Read Data to the Device:

You can Read data to the device file using standard file operations. For example:
```
$ cat /dev/char_drv
```


