## Nama dan NIM Anggota Kelompok
1. M. Yudith Aryanta Aditya - 2109106122
2. Muhammad Akbar Fahrezi - 2109106117
3. Sancto Metano Crozart - 2109106112

## Judul Projek Akhir
"Implementasi Sistem IOT untuk Buka dan Tutup Akses Tong Sampah dengan Sensor Jarak"

## Deskripsi
Proyek ini bertujuan untuk membuat tempat sampah pintar yang dapat mendeteksi penuh atau tidaknya tempat sampah menggunakan sensor ultrasonik. Tempat sampah akan mengirimkan status penuh atau tidak penuh ke server MQTT. Selain itu, proyek ini juga menambahkan fitur untuk membuka dan menutup tutup tempat sampah secara otomatis menggunakan servo motor, serta menyalakan LED indikator saat tempat sampah penuh.

## Pembagian Tugas per Individu
1. **M. Yudith Aryanta Aditya (122)**
   - Membuat Rangkaian Publisher (Rangkaian Sensor Jarak SR04).
   - Membuat code untuk Rangkaian Publisher tersebut.
   - Menbuat logika agar data pada rangkaian Publisher bisa masuk ke broker server Platform IOT (MQTTX).
2. **Muhammad Akbar Fahrezi (117)**
   - Membuat Rangkaian Subscriber (Rangkaian Sensor Jarak SR04, Servo, LED).
   - Membuat code untuk Rangkaian Publisher tersebut.
   - Implementasi callback dan logika penerimaan pesan dari server MQTTX atau Rangkaian Publisher.
3. **Sancto Metano Crozart (112)**
   - Membuat Rangkaian Subscriber (Rangkaian Sensor Jarak SR04, Servo, LED).
   - Membuat Manual Book.
   - Menbuat logika agar data pada rangkaian Subcriber bisa masuk ke broker server Platform IOT (MQTTX) untuk dI control.

## Komponen yang Digunakan
- **ESP8266**: Mikrocontroller dengan konektivitas Wi-Fi untuk mengirim dan menerima data dari server MQTT.
- **Ultrasonic Sensor (HC-SR04)**: Sensor untuk mengukur jarak dan mendeteksi penuh atau tidaknya tempat sampah.
- **Servo Motor**: Digunakan untuk membuka dan menutup tutup tempat sampah.
- **LED**: Indikator visual yang menyala saat tempat sampah penuh.
- **Resistor**: Untuk membatasi arus ke LED.
- **Breadboard dan Kabel Jumper**: Untuk menghubungkan komponen-komponen elektronik.
- **Kabel Data**: Untuk menyediakan daya ke ESP8266 dan komponen lainnya.
- **Kabel Jumper**: Untuk mengalirkan data dan daya.


## Cara Menggunakan
1. Hubungkan komponen sesuai dengan skema rangkaian.
2. Unduh dan instal library yang dibutuhkan di Arduino IDE: `ESP8266WiFi`, `PubSubClient`, dan `Servo`.
3. Masukkan informasi jaringan Wi-Fi dan server MQTT ke dalam kode.
4. Upload kode ke ESP8266.
5. Tempat sampah pintar siap digunakan dan akan mengirimkan status penuh atau tidak penuh ke server MQTT secara berkala.
6. Gunakan aplikasi MQTTX client untuk mengirim perintah "buka" atau "tutup" untuk berinteraksi dengan tempat sampah pintar.
7. Gunakan aplikasi MQTTX client juga bisa untuk melihat apakah sampah penuh atau belum.

## Board Schematic
### Publisher Schematic (Rangkaian Sensor Jarak SR04)
![PUBLISHER SKEMATIC](https://github.com/yudthadtyaaa/pa-praktikum-iot-unmul-a3/assets/95072812/3d1bc4b8-3df9-4ae8-92fa-3e49595ecdb7)

### Subscriber Schematic (Rangkaian Sensor Jarak SR04, Servo, dan LED)
![SUBSCRIBER SKEMATIC](https://github.com/yudthadtyaaa/pa-praktikum-iot-unmul-a3/assets/95072812/4d7c7991-306d-46c3-ad0d-552a96d419ef)




