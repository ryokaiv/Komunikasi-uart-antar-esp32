#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Inisialisasi LCD I2C 16x2
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  // Serial2 untuk komunikasi dengan ESP32-1
  Serial2.begin(115200);
  Serial2.setTimeout(5000);

  // Inisialisasi komunikasi I2C
  // SDA = GPIO 21, SCL = GPIO 22
  Wire.begin(21, 22);

  // Inisialisasi LCD
  lcd.init();
  lcd.backlight();

  // Tampilan awal
  lcd.setCursor(0, 0);
  lcd.print("ESP32-2 Siap");

  lcd.setCursor(0, 1);
  lcd.print("Menunggu Data");

  delay(2000);
  lcd.clear();
}

void loop() {
  // Mengecek apakah ada data dari ESP32-1
  if (Serial2.available()) {

    // Membaca data sampai karakter newline
    String data = Serial2.readStringUntil('\n');
    data.trim();

    // Mencari posisi koma
    int separator = data.indexOf(',');

    // Memastikan format data benar
    if (separator != -1) {

      // Mengambil nilai suhu
      String temperature = data.substring(0, separator);

      // Mengambil nilai kelembapan
      String humidity = data.substring(separator + 1);

      // Menghapus tampilan sebelumnya
      lcd.clear();

      // Menampilkan suhu pada baris pertama
      lcd.setCursor(0, 0);
      lcd.print("Suhu: ");
      lcd.print(temperature);
      lcd.print((char)223);
      lcd.print("C");

      // Menampilkan kelembapan pada baris kedua
      lcd.setCursor(0, 1);
      lcd.print("Hum : ");
      lcd.print(humidity);
      lcd.print("%");

      // Menampilkan data pada Serial Monitor
      Serial.println("Data diterima dari ESP32-1:");
      Serial.print("Suhu       : ");
      Serial.print(temperature);
      Serial.println(" °C");

      Serial.print("Kelembapan : ");
      Serial.print(humidity);
      Serial.println(" %");

      Serial.println("-------------------------");

      // Mengirim konfirmasi kembali ke ESP32-1
      Serial2.println(data);
    }
  }
}
