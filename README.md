# VrepControllerPs3
Control de Quadricopter con C++<br />
Instalar el Paquete ps3joy<br />
http://wiki.ros.org/ps3joy<br />

En una nueva terminal emparejar el control Ps3<br />
```
$ sudo bash
$ rosrun ps3joy sixpair
```
Precionar Ctrl-D para salir<br />

En una nueva terminal iniciar roscore<br />
$ roscore<br />

En una nueva terminal<br />
$ sudo bash<br />
$ rosrun ps3joy ps3joy_node.py<br />

Precionar el boton de emparejamiento del control Ps3
debe vibrar la palanca y debe aparecer esto<br />

Waiting for connection. Disconnect your PS3 joystick from USB and press the pairing button.
Connection activated<br />

Dar permisos al joystick<br />

$ ls -l /dev/input/js0<br />

Se muestra algo a esto<br />

crw-rw---- 1 root input 13, 0 mar  1 12:30 /dev/input/js0<br />

Con el siguiente comando otorgas permisos, puedes comprobar si se realizaron con $ ls -l /dev/input/js0<br />

$ sudo chmod a+rw /dev/input/js0<br />

Ahora iniciar el roslaunch<br />

$ roslaunch control_vrep_ps3joy quadricopter_ps3joy.launch<br />

Comprobar el funcionamiento con <br />

$ rostopic echo /cmd_vel_in/controlPS3<br />

Precionar los botones L2 y R2 del control Ps3<br />
