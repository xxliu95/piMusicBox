# piMusicBox
## Music box with raspberryPi using RFID cards

Este es un proyecto que hice con <a href="https://github.com/GONZALOCAPILLAPAREDES">Gonzalo</a> en 3º de carrera en una asignatura llamada Sistemas digitales 2.

El sistema detecta tarjetas RFID y dependiendo de la tarjeta reproduce una melodía u otra.
Se ha usado un RaspberryPi con la distribución Raspibian de Linux, con código en C. Con las bibliotecas de wiringPi y softTone.

Esquema general del sistema:

<br/>
<p align="center">
  <img src="https://user-images.githubusercontent.com/28632986/57083518-f505d480-6cf8-11e9-84ab-d97a52ef4a11.png " width="700">
</p>

Para la lectura de las tarjetas se ha utilizado un optoacoplador TCST2103 para la detección y Un lector RFID RC522.

<br/>
<p align="center">
  <img src="https://user-images.githubusercontent.com/28632986/57084028-ce946900-6cf9-11e9-8a44-010aed8a62fd.png " width="350">
  <img src="https://user-images.githubusercontent.com/28632986/57084026-ce946900-6cf9-11e9-89f5-8ce1a839ada1.png " width="350">
</p>

El software consiste en dos máquinas de estados controlados por unos flags. Una máquina se encarga de la lectura de tarjetas y la otra del reproductor de música.

<br/>
<p align="center">
  <img src="https://user-images.githubusercontent.com/28632986/57084114-00a5cb00-6cfa-11e9-8963-d1468f75befb.png " width="700">
  <img src="https://user-images.githubusercontent.com/28632986/57084113-00a5cb00-6cfa-11e9-909e-163bf7e307f7.png " width="700">
</p>
