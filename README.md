# VrepControllerPs3
Control de Quadricopter con C++
Instalar el Paquete ps3joy
http://wiki.ros.org/ps3joy

En una nueva terminal emparejar el control Ps3
$ sudo bash
$ rosrun ps3joy sixpair
Precionar Ctrl-D para salir

En una nueva terminal iniciar roscore
$ roscore

En una nueva terminal iniciar roscore
$ sudo bash
$ rosrun ps3joy ps3joy_node.py

Precionar el boton de emparejamiento del control Ps3
debe vibrar la palanca y debe aparecer esto

Waiting for connection. Disconnect your PS3 joystick from USB and press the pairing button.
Connection activated

Dar permisos al joystick

$ ls -l /dev/input/js0

Debes ver algo a esto

crw-rw---- 1 root input 13, 0 mar  1 12:30 /dev/input/js0

Con el siguiente comando otorgas permisos, puedes comprobar si se realizaron con $ ls -l /dev/input/js0

$ sudo chmod a+rw /dev/input/js0

Ahora iniciar el roslaunch

$ roslaunch control_vrep_ps3joy quadricopter_ps3joy.launch

Comprobar el funcionamiento con 

$ rostopic echo /cmd_vel_in/controlPS3

Precionar los botones L2 y R2 del control Ps3
